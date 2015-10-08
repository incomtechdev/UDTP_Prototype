#include "FTP_server_thread.h"
#include "UI.h"

FTPServer::FTPServer(	UI *_main_thread,
						QString _serverHomeDir,
						int _serverPort,
						qint64 _serverBitrate):
						main_thread(_main_thread),
						serverHomeDir(_serverHomeDir),
						serverPort(_serverPort),
						serverBitrate(_serverBitrate)
{
	serverSock = INVALID_SOCKET;

	connect(this, SIGNAL(writeLog(const QString &)), main_thread, SLOT(WriteLogMessage(const QString &)));
	connect(this, SIGNAL(setFTPServerStatus(bool)), main_thread, SLOT(SetFTPServerStatus(bool)));
	connect(main_thread, SIGNAL(abortServer()), this, SLOT(AbortServer()));
}

void FTPServer::run()
{
	QString errStr;
	// Initialize WinSock
	if (WSAStartup(0x0202, &wsaData) != 0)
	{
		emit writeLog("Error in starting WSAStartup()");
		AbortServer();
	}

	// fill sockaddr_in structure
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons((unsigned short)serverPort);

	// create socket
	serverSock = socket(serverAddr.sin_family, SOCK_STREAM, IPPROTO_TCP);

	if (serverSock == INVALID_SOCKET)
	{
		emit writeLog("Invalid Server Socket. Error " + errStr.setNum(WSAGetLastError()));
		AbortServer();
	}
	else if (serverSock == SOCKET_ERROR)
	{
		emit writeLog("Socket Server Error. Error " + errStr.setNum(WSAGetLastError()));
		AbortServer();
	}
	else
		emit writeLog("Server socket created succesfully");

	setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, (char *)(1), sizeof (1));

	// bind and listen socket
	if (bind(serverSock, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		emit writeLog("Server binding failed. Error " + errStr.setNum(WSAGetLastError()));
		AbortServer();
	}
	else
		emit writeLog("Success server binding");

	//Successfull bind, listen for Server requests.
	if (listen(serverSock, 1) == SOCKET_ERROR)
	{
		emit writeLog("Server listening error");
		AbortServer();
	}
	else
		emit writeLog("Success server listening");

	QString port;
	port.setNum(serverPort);
	errStr = "Set server port: ";
	errStr += port + ", server root dir: " + serverHomeDir;
	emit writeLog(errStr);

	emit setFTPServerStatus(true);

	while (1)
	{
		sleep(2);
		emit writeLog("waiting...");
	}

}

void FTPServer::AbortServer()
{
	WSACleanup();
	if (serverSock > 0)
		closesocket(serverSock);
	emit writeLog("Server Aborted");
	emit setFTPServerStatus(false);
}