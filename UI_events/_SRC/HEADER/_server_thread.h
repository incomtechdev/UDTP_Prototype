#ifndef _SERVER_THREAD_
#define _SERVER_THREAD_

#pragma comment(lib,"Ws2_32.lib")
#include <QThread>
#include <QFile>
#include <QDir>
#include <winsock2.h>
#include <windows.h>

class UI;
class serverThread;

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





#endif