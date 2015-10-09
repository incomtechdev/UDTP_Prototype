#ifndef _FTP_SERVER_THREAD_
#define _FTP_SERVER_THREAD_

#pragma comment(lib,"Ws2_32.lib")
#include <QThread>
#include <QFile>
#include <QDir>
#include <winsock2.h>
#include <windows.h>

class UI;

class ClientBase
{
	sockaddr_in clientAddr;
	SOCKET clientSock;
	ClientBase *nextClient;
	ClientBase *prevClient;

	ClientBase *firstClient;

public:
	ClientBase();
	ClientBase(sockaddr_in _clientAddr, SOCKET _clientSock);
	~ClientBase();

	void SetClientData(sockaddr_in _clientAddr, SOCKET _clientSock);
	sockaddr_in GetAddr();
	SOCKET GetSock();
	void AddClient(ClientBase *newClient);
	void DeleteClient(ClientBase *delClient);
	ClientBase *FindClientBySock(SOCKET sock);
};

class FTPServer : public QThread
{
	Q_OBJECT

private:
	UI *main_thread;
	QFile serverFile;
	QDir serverDir;
	QString serverHomeDir;
	int serverPort;
	qint64 serverBitrate;

	WSADATA wsaData;
	sockaddr_in serverAddr;
	SOCKET serverSock;

	ClientBase *clients;
	fd_set serverSet;			//used to check if there is data in the socket

public:
	FTPServer(	UI *_main_thread,
				QString serverHomeDir,
				int serverPort,
				qint64 serverBitrate);
signals:
	void writeLog(const QString &message);
	void setFTPServerStatus(bool status);
	int FTPServerRunning();

public slots:
	void AbortServer();

private:
	void run();
};





#endif