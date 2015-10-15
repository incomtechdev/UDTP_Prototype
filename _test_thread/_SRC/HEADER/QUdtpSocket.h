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

int _connect(
	_In_ SOCKET                *s,
	_In_ const struct sockaddr *name,
	_In_ int                   namelen
	);

class QUdtpSocket;

class SocketData
{
public:
	sockaddr_in addr;
	SOCKET sock;
};

class Udtp_thread :public QThread
{
	Q_OBJECT

public:
	int threadID;

	QMutex mutex;
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
	int getStringFromServer(char *buf, int len);

	void lockClientConnection(bool isLock);

public slots:
	void setRunning(bool run);

};

class QUdtpSocket: public QObject
{
	Q_OBJECT

private:

	WSADATA data;

	QString str;

	SocketData *server;
	SocketData *client;

	bool isClientLock;
public:
	QWaitCondition cond;
	Udtp_thread *eventThread;

	QUdtpSocket(int threadID);
	~QUdtpSocket();
	int createServerSocket(SocketData *data);
	int closeServerSocket();
	int createClientSocket(SocketData *data);

	int connectToServer();
	int sendToServer(char *str, int len);
	int recvFromServer(char *str, int len);

	SocketData *getServer();
	SocketData *getClient();
signals:
	void setRunning(bool run);

public slots:
	void deleteUdtp_thread();
	int acceptClient(SocketData *data);
	int fillServerData(char *buf, int len);
	int getStringFromServer(char *buf, int len);

	void lockClientConnection(bool isLock);
};

class serverThread :public QThread
{
	Q_OBJECT

public:
	QUdtpSocket serv;

	serverThread(SocketData *addr) :serv(0)
	{
		serv.createServerSocket(addr);
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