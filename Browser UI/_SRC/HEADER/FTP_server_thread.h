#ifndef _FTP_SERVER_THREAD_
#define _FTP_SERVER_THREAD_

#pragma comment(lib,"Ws2_32.lib")
#include <QThread>
#include <QFile>
#include <QDir>
#include <winsock2.h>
#include <windows.h>

class UI;

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

public:
	FTPServer(	UI *_main_thread,
				QString serverHomeDir,
				int serverPort,
				qint64 serverBitrate);
signals:
	void writeLog(const QString &message);
	void setFTPServerStatus(bool status);

public slots:
	void AbortServer();

private:
	void run();
};





#endif