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
	connect(this, SIGNAL(acceptClient(SocketData *)), parent, SLOT(acceptClient(SocketData *)));
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
	isRunning = run;
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

QUdtpSocket::QUdtpSocket(int threadID) : server(0), client(0), isClientLock(false), maxBitrate(0)
{
	eventThread = new Udtp_thread(this, threadID);
}

QUdtpSocket::~QUdtpSocket()
{
	if (eventThread)
		delete eventThread;

	if (server)
	{
		closesocket(client->sock);
		delete server;
	}
	if (client)
	{
		closesocket(client->sock);
		delete client;
	}

	WSACleanup();
}

int QUdtpSocket::execSocketActivity(fd_set *read, fd_set *write, fd_set *err)
{
	int i;
	char ch;
	SocketData *curClient = 0;

	for (i = 0; i < read->fd_count; i += 1)
	{
		if (read->fd_array[i] == server->sock)
		{
			SocketData data;
			int len=1;
			data.sock = accept(server->sock, (sockaddr*)(&data.addr), &len);
//			int a = WSAGetLastError();
//////////////////////////          функция выренесена в load.cpp        ////////////////////
			acceptClient(&data);
/////////////////////////////////////////////////////////////////////////////////////////////
			FD_SET(client->sock, &eventThread->set);

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

		char *bytes = new char[curClient->bitrate];
//////////////////////////          функция выренесена в load.cpp        ////////////////////
		getStringFromServer(curClient, bytes);
/////////////////////////////////////////////////////////////////////////////////////////////

		send(client->sock, bytes, curClient->bitrate, 0);
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

	if (bytes[0] == 0)		//// descriptor for write data
	{
		cli->direction = 1;
	}
	else if (bytes[0] == 1)		// descriptor for read data
	{
		cli->direction = 2;
		ch = 50;
		send(cli->sock, &ch, 1, 0);
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
		ch = 20;
		send(cli->sock, &ch, 1, 0);
		cli->isReadDescriptor = false;
		cli->direction = 0;
	}
	else
	{
		if (cli->bitrate > cli->bytesrest)
			cli->bitrate = cli->bytesrest;

		if (cli->direction == 2)
		{
			FD_SET(cli->sock, &eventThread->write);
		}
	}

	return 0;
}

int QUdtpSocket::createServerSocket(SocketData *data, int bitrate)
{
	maxBitrate = bitrate;

	QString errStr;
	server = new SocketData;
	// fill sockaddr_in structure
	server->addr.sin_family = AF_INET;
	server->addr.sin_addr.s_addr = data->addr.sin_addr.s_addr;
	server->addr.sin_port = data->addr.sin_port;
	server->bitrate = 0;
	server->bytesrest = 0;
	server->bytessend = 0;
	server->direction = 0;
	server->isReadDescriptor = false;

	// create socket
	server->sock = socket(server->addr.sin_family, SOCK_STREAM, IPPROTO_TCP);

	int ioptVal = 1;
	setsockopt(server->sock, SOL_SOCKET, SO_REUSEADDR, (char *)(&ioptVal), sizeof(1));

	// bind and listen socket
	bind(server->sock, (sockaddr *)&server->addr, sizeof(sockaddr_in));

	//Successfull bind, listen for Server requests.
	listen(server->sock, 1);

	FD_SET(server->sock, &eventThread->set);

	emit setRunning(true);

	return 0;
}

int QUdtpSocket::createClientSocket(SocketData *data)
{
	QString errStr;
	client = new SocketData;
	// fill sockaddr_in structure
	client->addr.sin_family = AF_INET;
	client->addr.sin_addr.s_addr = data->addr.sin_addr.s_addr;
	client->addr.sin_port = data->addr.sin_port;

	// create socket
	client->sock = socket(client->addr.sin_family, SOCK_STREAM, IPPROTO_TCP);

	FD_SET(client->sock, &eventThread->set);

	return 0;
}

int QUdtpSocket::closeServerSocket()
{
	if (server)
	{
		emit setRunning(false);
		if (server->sock > 0)
			closesocket(server->sock);
	}
	delete server;
	server = 0;
	
	return 0;
}

void QUdtpSocket::deleteUdtp_thread()
{
	if (eventThread)
		delete eventThread;

	eventThread = 0;
}

SocketData *QUdtpSocket::getServer()
{
	return server;
}

SocketData *QUdtpSocket::getClient()
{
	return client;
}

int QUdtpSocket::connectToServer()
{
	char ch = 0;

	::connect(client->sock, (sockaddr*)(&client->addr), sizeof(sockaddr));

	recv(client->sock, &ch, 1, 0);

	return 0;
}

int QUdtpSocket::sendToServer(char *str, int len)
{
// form descriptor (1st byte = 0)
	char *buff = new char [len+DESCRIPTOR_LENGTH];
	buff[0] = 0;
	memcpy(buff + 1, &len, 4);
	memset(buff + DESCRIPTOR_LENGTH, 0, len);


	strncpy(buff + DESCRIPTOR_LENGTH, str, len);
	len += DESCRIPTOR_LENGTH;
	// send bytes

	send(client->sock, buff, len, 0);

	char ch = 0;
	recv(client->sock, &ch, 1, 0);

	return 0;
}

int QUdtpSocket::recvFromServer(char *str, int len)
{
	char ch = 0;

// send bytes length for server (1st byte = 1)
	char buff[DESCRIPTOR_LENGTH];
	buff[0] = 1;
	memcpy(buff + 1, &len, 4);

	send(client->sock, buff, DESCRIPTOR_LENGTH, 0);

/// verify ready for recv
	ch = 0;
	recv(client->sock, &ch, 1, 0);

// recv bytes
	recv(client->sock, str, len, 0);

	ch = 100;
	send(client->sock, &ch, 1, 0);

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
	if (sock == client->sock)
		return client;

	return 0;
}