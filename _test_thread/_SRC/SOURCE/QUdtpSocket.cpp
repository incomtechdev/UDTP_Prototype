#include "QUdtpSocket.h"

int _connect(
	_In_ SOCKET                *s,
	_In_ const struct sockaddr *name,
	_In_ int                   namelen
	)
{
	return connect(*s, name, namelen);
}

/*
class SocketData
{
public:
	sockaddr_in addr;
	SOCKET sock;
};

class Udtp_thread :public QThread
{
	QUdtpSocket *parent;

public:
	Udtp_thread(QUdtpSocket *_parent);
	~Udtp_thread;

	void run();
};

class QUdtpSocket
{
	WSADATA data;
	fd_set set;

	SocketData server;
	SocketData client;

	Udtp_thread *eventThread;

public:
	QUdtpSocket();
	~QUdtpSocket();
	createSocket(SocketData *data);
};*/

Udtp_thread::Udtp_thread(QUdtpSocket *_parent, int ID) : parent(_parent), isRunning(false), threadID(ID)
{
	FD_ZERO(&set);

	connect(parent, SIGNAL(setRunning(bool)), this, SLOT(setRunning(bool)));
	connect(this, SIGNAL(deleteUdtp_thread()), parent, SLOT(deleteUdtp_thread()));
	connect(this, SIGNAL(acceptClient(SocketData *)), parent, SLOT(acceptClient(SocketData *)));
	connect(this, SIGNAL(lockClientConnection(bool)), parent, SLOT(lockClientConnection(bool)));
	connect(this, SIGNAL(fillServerData(char *, int)), parent, SLOT(fillServerData(char *, int)));
	connect(this, SIGNAL(getStringFromServer(char *, int)), parent, SLOT(getStringFromServer(char *, int)));
	
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

void Udtp_thread::run()
{ 
	int i;
	fd_set read, write, err;
	char ch;

	FD_ZERO(&read);
	FD_ZERO(&write);
	FD_ZERO(&err);

	while (isRunning)
	{
		memcpy(&read, &set, sizeof(fd_set));
//		memcpy(&write, &set, sizeof(fd_set));
		memcpy(&err, &set, sizeof(fd_set));

		if (select(0, &read, &write, &err, NULL) == SOCKET_ERROR)
		{
			continue;
		}

		for (i = 0; i < read.fd_count; i += 1)
		{
			if (read.fd_array[i] == parent->getServer()->sock)
			{
				SocketData data;
				int len;
				data.sock = accept(read.fd_array[i], (sockaddr*)(&data.addr), &len);
				emit acceptClient(&data);
				mutex.lock();
				parent->cond.wait(&mutex);
				mutex.unlock();
				FD_SET(data.sock, &set);
				ch = 10;
				send(data.sock, &ch, 1, 0);
			}
			else
			{
				SOCKET reads = read.fd_array[i];
				char bytes[5];
				int len;
				recv(reads, bytes, 5, 0);
				memcpy(&len, bytes+1, 4);
				ch = 20;
				send(reads, &ch, 1, 0);

				if (bytes[0] == 0)
				{
					char *buf = new char[len];
					recv(reads, buf, len, 0);
					ch = 20;
					send(reads, &ch, 1, 0);
					emit fillServerData(buf, len);
					mutex.lock();
					parent->cond.wait(&mutex);
					mutex.unlock();
					delete buf;
				}
				else if (bytes[0] == 1)
				{
					char *buf = new char[len];
					memset(buf, 0, len);
					emit getStringFromServer(buf, len);
					mutex.lock();
					parent->cond.wait(&mutex);
					send(reads, buf, len, 0);
					ch = 0;
					recv(reads, &ch, 1, 0);
					delete buf;
				}
			}
 		}
/*
		for (i = 0; i < write.fd_count; i += 1)
		{
			char ch = 30;
			send(write.fd_array[i], &ch, 1, 0);
		}
*/
	}

	emit deleteUdtp_thread();
}

QUdtpSocket::QUdtpSocket(int threadID) : server(0), client(0), isClientLock(false)
{
	eventThread = new Udtp_thread(this, threadID);
	if (WSAStartup(0x0202, &data) != 0)
		WSACleanup();
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

int QUdtpSocket::createServerSocket(SocketData *data)
{
	QString errStr;
	server = new SocketData;
	// fill sockaddr_in structure
	server->addr.sin_family = AF_INET;
	server->addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server->addr.sin_port = data->addr.sin_port;

	// create socket
	server->sock = socket(server->addr.sin_family, SOCK_STREAM, IPPROTO_TCP);
	setsockopt(server->sock, SOL_SOCKET, SO_REUSEADDR, (char *)(1), sizeof(1));

	// bind and listen socket
	bind(server->sock, (sockaddr *)&server->addr, sizeof(server->addr));

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

//	emit setRunning(true);

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

int QUdtpSocket::acceptClient(SocketData *data)
{
	client = new SocketData;
	client->addr.sin_family = data->addr.sin_family;
	client->addr.sin_addr.s_addr = data->addr.sin_addr.s_addr;
	client->addr.sin_port = data->addr.sin_port;
	client->sock = data->sock;

	cond.wakeAll();

	return 0;
}

int QUdtpSocket::connectToServer()
{
	fd_set read, write, err;
	memcpy(&read, &eventThread->set, sizeof(fd_set));
	memcpy(&err, &eventThread->set, sizeof(fd_set));
	char ch = 0;

	_connect(&client->sock, (sockaddr*)(&client->addr), sizeof(sockaddr_in));

	select(0, &read, 0, &err, 0);

	recv(client->sock, &ch, 1, 0);

	return 0;
}

int QUdtpSocket::sendToServer(char *str, int len)
{
	fd_set read, err;
	memcpy(&read, &eventThread->set, sizeof(fd_set));
	memcpy(&err, &eventThread->set, sizeof(fd_set));
	char ch = 0;

// send bytes length for server (1st byte = 0)
	char *buff = new char[5];
	buff[0] = 0;
	memcpy(buff + 1, &len, 4);

	send(client->sock, buff, 5, 0);
	select(0, &read, 0, &err, 0);
	ch = 0;
	recv(client->sock, &ch, 1, 0);

	delete buff;

	memcpy(&read, &eventThread->set, sizeof(fd_set));
	memcpy(&err, &eventThread->set, sizeof(fd_set));

	// send bytes

	send(client->sock, str, len, 0);
	select(0, &read, 0, &err, 0);
	ch = 0;
	recv(client->sock, &ch, 1, 0);

	return 0;
}

int QUdtpSocket::recvFromServer(char *str, int len)
{
	fd_set read, write, err;
	memcpy(&read, &eventThread->set, sizeof(fd_set));
	memcpy(&write, &eventThread->set, sizeof(fd_set));
	memcpy(&err, &eventThread->set, sizeof(fd_set));

	char ch = 0;

// send bytes length for server (1st byte = 1)
	char *buff = new char[5];
	buff[0] = 1;
	memcpy(buff + 1, &len, 4);

	send(client->sock, buff, 5, 0);
	select(0, &read, 0, &err, 0);
	ch = 0;
	recv(client->sock, &ch, 1, 0);

	delete buff;

	memcpy(&write, &eventThread->set, sizeof(fd_set));
	memcpy(&err, &eventThread->set, sizeof(fd_set));

// recv bytes
	recv(client->sock, str, len, 0);
	select(0, 0, &write, &err, 0);
	ch = 30;
	send(client->sock, &ch, 1, 0);

	return 0;
}

void QUdtpSocket::lockClientConnection(bool isLock)
{
	isClientLock = isLock;
}
