#ifndef _SERVER_THREAD_
#define _SERVER_THREAD_

#pragma comment(lib,"Ws2_32.lib")
#include <QThread>
#include <QFile>
#include <QMutex>
#include <QWaitCondition>
#include <QDir>
#include <winsock2.h>
#include <windows.h>

using namespace std;

#define DESCRIPTOR_LENGTH 5

int _connect(
	_In_ SOCKET                *s,
	_In_ const struct sockaddr *name,
	_In_ int                   namelen
	);

class QUdtpSocket;

class SocketData
{
public:
	SOCKET sock;
	sockaddr_in addr;
	int bitrate;
	bool isReadDescriptor;
	int bytessend;
	int bytesrest;
	int direction;
};

class Udtp_thread :public QThread
{
	Q_OBJECT

public:
	fd_set read, write, err;

	int threadID;

	QUdtpSocket *parent;
	bool isRunning;

	fd_set set;

public:
	Udtp_thread(QUdtpSocket *_parent, int ID);
	~Udtp_thread();

	void run();

signals:
	void deleteUdtp_thread();
	int acceptClient(SocketData *data);
	int fillServerData(char *buf, int len);
	int execSocketActivity(fd_set *read, fd_set *write, fd_set *err);
	void lockClientConnection(bool isLock);

public slots:
	void setRunning(bool run);
	int waitForSocketActivity();

};

class QUdtpSocket: public QObject
{
	Q_OBJECT

private:

	QString str;

	SocketData *server;
	SocketData *client;

	bool isClientLock;
	int maxBitrate;
public:
	Udtp_thread *eventThread;

	QUdtpSocket(int threadID);
	~QUdtpSocket();
	int createServerSocket(SocketData *data, int bitrate);
	int closeServerSocket();
	int createClientSocket(SocketData *data);

	int connectToServer();
	int sendToServer(char *str, int len);
	int recvFromServer(char *str, int len);
	int getBitrate();
	int manageDescriptor(SocketData *cli, char *bytes);
	int	manageBytesTransfer(SocketData *cli, char *bytes, int byteslen);

	SocketData *getServer();
	SocketData *getClient();
	SocketData * getClientBySocket(SOCKET sock);
	int getStringFromServer(SocketData *cli, char *buf);

signals:
	void setRunning(bool run);
	int waitForSocketActivity();

public slots:
	void deleteUdtp_thread();
	int acceptClient(SocketData *data);
	int fillServerData(char *buf, int len);
	int execSocketActivity(fd_set *read, fd_set *write, fd_set *err);

	void lockClientConnection(bool isLock);
};

class serverThread :public QThread
{
	Q_OBJECT

public:
	QUdtpSocket serv;

	serverThread(SocketData *addr, int bitrate) :serv(0)
	{
		serv.createServerSocket(addr, bitrate);
	}

	void run()
	{
		this->exec();
	}
};

class clientThread :public QThread
{
	Q_OBJECT

public:
	QUdtpSocket cli;

	clientThread(SocketData *addr) :cli(0)
	{
		cli.createClientSocket(addr);
	}

	void run();
};


#endif