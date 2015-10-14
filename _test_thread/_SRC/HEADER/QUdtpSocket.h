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
	void lockClientConnection(bool isLock);

public slots:
	void setRunning(bool run);

};

class QUdtpSocket: public QObject
{
	Q_OBJECT

private:

	WSADATA data;

	SocketData *server;
	SocketData *client;

	Udtp_thread *eventThread;

	bool isClientLock;
public:
	QWaitCondition cond;

	QUdtpSocket(int threadID);
	~QUdtpSocket();
	int createServerSocket(SocketData *data);
	int closeServerSocket();
	int createClientSocket(SocketData *data);

	int connectSocket();

	SocketData *getServer();
	SocketData *getClient();
signals:
	void setRunning(bool run);

public slots:
	void deleteUdtp_thread();
	int acceptClient(SocketData *data);
	void lockClientConnection(bool isLock);
};

class serverThread :public QThread
{
	Q_OBJECT

public:
	QUdtpSocket serv;

	serverThread(int ind) :serv(ind){}

	void run()
	{
		SocketData servAddr;
		servAddr.addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		servAddr.addr.sin_port = htons(10000);

		serv.createServerSocket(&servAddr);

		this->exec();
	}
};

/*
class ClientBase
{
public:
	short port;
	sockaddr_in addr;
	SOCKET sock;
	ClientBase *nextClient;
	ClientBase *prevClient;

	ClientBase();
	ClientBase(short port, sockaddr_in _addr, SOCKET _sock);
	~ClientBase();

	void SetRealPort(short _port);
	short getRealPort();

	void SetAddr(sockaddr_in _addr);
	sockaddr_in GetAddr();

	void SetSock(SOCKET _sock);
	SOCKET GetSock();

};

class serverThread : public QThread
{
	Q_OBJECT

private:
	UI *parentThread;

	ClientBase serverData;
	ClientBase *clientData;

	fd_set serverSet;			//used to check if there is data in the socket

	bool running;

	void AddClient(ClientBase *newClient);
	void DeleteClient(ClientBase *delClient);
	ClientBase *FindClientBySock(SOCKET sock);

public:
	serverThread(UI *_parent);
	~serverThread();

	ClientBase *GetServerData();
	fd_set *GetSet();


signals:

public slots :
	void CreateServerSocket(ClientBase *_data);

private:
	void run();

};
*/




#endif