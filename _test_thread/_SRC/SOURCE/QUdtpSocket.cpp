#include "QUdtpSocket.h"

int _connect(
	_In_ SOCKET                *s,
	_In_ const struct sockaddr *name,
	_In_ int                   namelen
	)
{
	return connect(*s, name, namelen);
}

Udtp_thread::Udtp_thread(QUdtpSocket *_parent, int ID) : parent(_parent), isRunning(false), threadID(ID)
{
	FD_ZERO(&set);
	FD_ZERO(&read);
	FD_ZERO(&write);
	FD_ZERO(&err);

	connect(parent, SIGNAL(setRunning(bool)), this, SLOT(setRunning(bool)));
	connect(this, SIGNAL(deleteUdtp_thread()), parent, SLOT(deleteUdtp_thread()));
	connect(this, SIGNAL(lockClientConnection(bool)), parent, SLOT(lockClientConnection(bool)));
	connect(this, SIGNAL(fillServerData(char *, int)), parent, SLOT(fillServerData(char *, int)));

	connect(parent, SIGNAL(waitForSocketActivity()), this, SLOT(waitForSocketActivity()));
	connect(this,
			SIGNAL(execSocketActivity(fd_set *, fd_set *, fd_set *)),
			parent,
			SLOT(execSocketActivity(fd_set *, fd_set *, fd_set *)));


}

Udtp_thread::~Udtp_thread()
{

}

void Udtp_thread::setRunning(bool run)
{
	if (run)
		start();
}

int Udtp_thread::waitForSocketActivity()
{
	memcpy(&read, &set, sizeof(fd_set));
	memcpy(&err, &set, sizeof(fd_set));

 	if (select(0, &read, &write, &err, NULL) == SOCKET_ERROR)
		return -1;

	emit execSocketActivity(&read, &write, &err);

	return 0;
}

void Udtp_thread::run()
{
	waitForSocketActivity();
	this->exec();
}

QUdtpSocket::QUdtpSocket(int threadID) : isClientLock(false), maxBitrate(0)
{
	if (WSAStartup(0x0202, &data) != 0)
		WSACleanup();
	eventThread = new Udtp_thread(this, threadID);
}

QUdtpSocket::~QUdtpSocket()
{

	if (eventThread)
		delete eventThread;

	for (int i = 0; i < servers.size(); i++)
	{
		SocketData *data = servers[i];
		if (data->sock >0)
			closesocket(data->sock);
		delete data;

	}
	for (int i = 0; i < clients.size(); i++)
	{
		SocketData *data = clients[i];
		if (data->sock >0)
			closesocket(data->sock);
		delete data;

	}

	clients.clear();

	WSACleanup();
}

int QUdtpSocket::execSocketActivity(fd_set *read, fd_set *write, fd_set *err)
{
	int i;
	char ch;
	SocketData *curClient = 0;

	for (i = 0; i < read->fd_count; i += 1)
	{
		curClient = getServerBySocket(read->fd_array[i]);
		if (curClient)
		{
			SocketData data;
			int len=16;
			data.sock = accept(read->fd_array[i], (sockaddr*)(&data.addr), &len);
//			int a = WSAGetLastError();
//////////////////////////          функция выренесена в load.cpp        ////////////////////
			acceptClient(&data);
/////////////////////////////////////////////////////////////////////////////////////////////
			FD_SET(data.sock, &eventThread->set);

			send(data.sock, &ch, 1, 0);
		}

		else
		{
			curClient = getClientBySocket(read->fd_array[i]);
			if (!curClient->isReadDescriptor)
			{
				char bytes[DESCRIPTOR_LENGTH];
				int len = DESCRIPTOR_LENGTH;
				recv(curClient->sock, bytes, len, 0);
				manageDescriptor(curClient, bytes);
			}
			else
			{
				char *bytes = new char[curClient->bitrate];
				recv(curClient->sock, bytes, curClient->bitrate, 0);
//////////////////////////          функция выренесена в load.cpp        ////////////////////
				fillServerData(bytes, curClient->bitrate);
/////////////////////////////////////////////////////////////////////////////////////////////
				manageBytesTransfer(curClient, bytes, curClient->bitrate);
				delete [] bytes;
			}
		}
	}

	fd_set _write;
	memcpy(&_write, write, sizeof(fd_set));
	FD_ZERO(write);
	for (i = 0; i < _write.fd_count; i += 1)
	{
		curClient = getClientBySocket(_write.fd_array[i]);

		char *bytes = new char[curClient->bitrate + DESCRIPTOR_LENGTH];
//////////////////////////          функция выренесена в load.cpp        ////////////////////
		getStringFromServer(curClient, bytes);
/////////////////////////////////////////////////////////////////////////////////////////////

		send(curClient->sock, bytes, curClient->bitrate + DESCRIPTOR_LENGTH, 0);
		manageBytesTransfer(curClient, bytes, curClient->bitrate);
		delete[] bytes;

	}


	emit waitForSocketActivity();
	return 0;
}

int QUdtpSocket::manageDescriptor(SocketData *cli, char *bytes)
{
	int len;
	char ch;
	memcpy(&len, bytes + 1, 4);

	if (len < maxBitrate)
		cli->bitrate = len;
	else
		cli->bitrate = maxBitrate;

	cli->bytesrest = len;
	cli->bytessend = 0;

	cli->isReadDescriptor = true;

	ch = 50;
	send(cli->sock, &ch, 1, 0);

	if (bytes[0] == 0)		//// descriptor for write data
	{
		cli->direction = 1;
		char bytesD[DESCRIPTOR_LENGTH];
		memcpy(bytesD + 1, &cli->bitrate, 4);
		send(cli->sock, bytesD, DESCRIPTOR_LENGTH, 0);
	}
	else if (bytes[0] == 1)		// descriptor for read data
	{
		cli->direction = 2;
		FD_SET(cli->sock, &eventThread->write);
	}

	return 0;
}

int	QUdtpSocket::manageBytesTransfer(SocketData *cli, char *bytes, int byteslen)
{
	char ch;

	cli->bytesrest -= byteslen;
	cli->bytessend += byteslen;

	if (cli->bytesrest <= 0)
	{
		////   end of transfer
		if (cli->direction == 1)
		{
			ch = 20;
			send(cli->sock, &ch, 1, 0);
		}
		else if (cli->direction == 2)
		{
			ch = 0;
			recv(cli->sock, &ch, 1, 0);
		}

		ch = 20;
		send(cli->sock, &ch, 1, 0);
		cli->isReadDescriptor = false;
		cli->direction = 0;
	}
	else
	{
		if (cli->bitrate > cli->bytesrest)
			cli->bitrate = cli->bytesrest;

		if (cli->direction == 1)
		{
			ch = 20;
			send(cli->sock, &ch, 1, 0);
			char bytesD[DESCRIPTOR_LENGTH];
			memcpy(bytesD + 1, &cli->bitrate, 4);
			send(cli->sock, bytesD, DESCRIPTOR_LENGTH, 0);
		}
		if (cli->direction == 2)
		{
			ch = 0;
			recv(cli->sock, &ch, 1, 0);
			FD_SET(cli->sock, &eventThread->write);
		}
	}

	return 0;
}

int QUdtpSocket::createServerSocket(SocketData *data, int bitrate, int sockets)
{
	SocketData *socketData;
	maxBitrate = bitrate;

	QString errStr;
	if (sockets == 0)
		sockets = 1;

	for (int i = 0; i < sockets; i++)
	{

		socketData = new SocketData;
		// fill sockaddr_in structure
		socketData->addr.sin_family = AF_INET;
		socketData->addr.sin_addr.s_addr = data->addr.sin_addr.s_addr;

		if (i == 0)
			socketData->addr.sin_port = data->addr.sin_port;
		else
			socketData->addr.sin_port = htons(SERVER_CHANNELS_BEGIN + i - 1);

		socketData->isReadDescriptor = false;

		// create socket
		socketData->sock = socket(socketData->addr.sin_family, SOCK_STREAM, IPPROTO_TCP);

		int ioptVal = 1;
		setsockopt(socketData->sock, SOL_SOCKET, SO_REUSEADDR, (char *)(&ioptVal), sizeof(1));

		// bind and listen socket
		int err = 0, err2 = 0;
		err = bind(socketData->sock, (sockaddr *)(&socketData->addr), sizeof(sockaddr_in));

		//Successfull bind, listen for Server requests.
		err2 = listen(socketData->sock, 1);

		FD_SET(socketData->sock, &eventThread->set);
		clientBasePair serverPair(socketData->sock, socketData);
		servers.insert(serverPair);
	}
	emit setRunning(true);

	return 0;

}

int QUdtpSocket::createClientSocket(SocketData *data)
{
	QString errStr;
	SocketData *socketData;

	socketData = new SocketData;
	// fill sockaddr_in structure
	socketData->addr.sin_family = AF_INET;
	socketData->addr.sin_addr.s_addr = data->addr.sin_addr.s_addr;
	socketData->addr.sin_port = data->addr.sin_port;

	// create socket
	socketData->sock = socket(socketData->addr.sin_family, SOCK_STREAM, IPPROTO_TCP);

	FD_SET(socketData->sock, &eventThread->set);

	clientBasePair serverPair(socketData->sock, socketData);
	servers.insert(serverPair);

	return 0;
}

int QUdtpSocket::closeServerSocket(SOCKET sock)
{
	SocketData *socketData = getServerBySocket(sock);
	if (socketData)
	{
		if (socketData->sock > 0)
			closesocket(socketData->sock);
		servers.erase(servers.find(sock));
		
		delete socketData;
		socketData = 0;
	}
	
	return 0;
}

void QUdtpSocket::deleteUdtp_thread()
{
	if (eventThread)
	{
		eventThread->quit();
		delete eventThread;
	}

	eventThread = 0;
}

int QUdtpSocket::connectToServer()
{
	char ch = 0;
	SocketData *client = servers.begin()->second;
	::connect(client->sock, (sockaddr*)(&client->addr), sizeof(sockaddr_in));

	recv(client->sock, &ch, 1, 0);

	return 0;
}

int QUdtpSocket::sendToServer(char *str, int len)
{
	char ch = 0;
	SocketData *client = servers.begin()->second;
// form descriptor 
// send bytes length for server (1st byte = 1)
	char buff[DESCRIPTOR_LENGTH];
	buff[0] = 0;
	memcpy(buff + 1, &len, 4);

	send(client->sock, buff, DESCRIPTOR_LENGTH, 0);

	/// verify ready for send
	ch = 0;
	recv(client->sock, &ch, 1, 0);
	// send bytes

//	send(client->sock, str, len, 0);

	client->bytesrest = 0;
	bool isrecv = true;
	while (isrecv)
	{
		recv(client->sock, buff, DESCRIPTOR_LENGTH, 0);
		memcpy(&client->bytessend, buff + 1, 4);
		char *buffstr = new char[client->bytessend];
		memcpy(buffstr, str + client->bytesrest, client->bytessend);
		send(client->sock, buffstr, client->bytessend, 0);

		ch = 0;
		recv(client->sock, &ch, 1, 0);
		client->bytesrest += client->bytessend;
		if (client->bytesrest >= len)
			isrecv = false;

		delete[] buffstr;
	}

	ch = 0;
	recv(client->sock, &ch, 1, 0);

	return 0;
}

int QUdtpSocket::recvFromServer(char *str, int len)
{
	char ch = 0;
	SocketData *client = servers.begin()->second;
// send bytes length for server (1st byte = 1)
	char buff[DESCRIPTOR_LENGTH];
	buff[0] = 1;
	memcpy(buff + 1, &len, 4);

	send(client->sock, buff, DESCRIPTOR_LENGTH, 0);

/// verify ready for recv
	ch = 0;
	recv(client->sock, &ch, 1, 0);

// recv bytes
	memset(str, 0, len);
	client->bytesrest = 0;
	bool isrecv = true;
	while (isrecv)
	{
		recv(client->sock, buff, DESCRIPTOR_LENGTH, 0);
		memcpy(&client->bytessend, buff + 1, 4);
		char *buffstr = new char[client->bytessend];
		recv(client->sock, buffstr, client->bytessend, 0);
		memcpy(str + client->bytesrest, buffstr, client->bytessend);

		ch = 50;
		send(client->sock, &ch, 1, 0);
		client->bytesrest += client->bytessend;
		if (client->bytesrest >= len)
			isrecv = false;

		delete[] buffstr;
	}

	ch = 50;
	recv(client->sock, &ch, 1, 0);

	return 0;
}

void QUdtpSocket::lockClientConnection(bool isLock)
{
	isClientLock = isLock;
}

int QUdtpSocket::getBitrate()
{
	return maxBitrate;
}

SocketData *QUdtpSocket::getClientBySocket(SOCKET sock)
{
	clientBase::iterator clientIter = clients.find(sock);
	if (clientIter != clients.end())
		return clientIter->second;

	return 0;
}

SocketData *QUdtpSocket::getServerBySocket(SOCKET sock)
{
	clientBase::iterator serverIter = servers.find(sock);
	if (serverIter != servers.end())
		return serverIter->second;

	return 0;
}
