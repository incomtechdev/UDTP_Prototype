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

	QDir curDir;

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

	QDir GetCurrentDir();
	void SetCurrentDir(QDir newDir);
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
	SOCKET GetSock();
signals:
	void writeLog(const QString &message);
	void setFTPServerStatus(bool status);

public slots:
	void AbortServer();

private:
	void run();
	ClientBase *Accept_new_Client();
	int FTPServerRunning();

	int ExecCommandOperation(ClientBase *curClient);
	int ExecFileOperation(ClientBase *curClient);

};





#endif