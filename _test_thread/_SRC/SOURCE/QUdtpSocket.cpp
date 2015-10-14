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

	int a = 0;


	FD_ZERO(&read);
	FD_ZERO(&write);
	FD_ZERO(&err);

	while (isRunning)
	{
		memcpy(&read, &set, sizeof(fd_set));
//		memcpy(&write, &set, sizeof(fd_set));
//		memcpy(&err, &set, sizeof(fd_set));

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
				FD_SET(data.sock, &set);
				char ch = 1;
				send(data.sock, &ch, 1, 0);
			}
			else
			{

			}
 		}
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

int QUdtpSocket::connectSocket()
{
	fd_set read, err;
	memcpy(&read, &eventThread->set, sizeof(fd_set));
	memcpy(&err, &eventThread->set, sizeof(fd_set));
	_connect(&client->sock, (sockaddr*)(&client->addr), sizeof(sockaddr_in));

	select(0, &read, 0, &err, 0);



	return 0;
}

void QUdtpSocket::lockClientConnection(bool isLock)
{
	isClientLock = isLock;
}

/*
class ClientBase
{
sockaddr_in clientAddr;
SOCKET clientSock;
ClientBase *nextClient;

public:
ClientBase();
ClientBase(sockaddr_in clientAddr, SOCKET clientSock);
~ClientBase();

void SetClientData(sockaddr_in clientAddr, SOCKET clientSock);
sockaddr_in GetAddr();
SOCKET GetSock();
void AddClient(ClientBase *newClient);
void DeleteClient(ClientBase *delClient);
ClientBase *FindClientBySock(SOCKET sock);
};
*/
/*
ClientBase::ClientBase() : nextClient(0), prevClient(0)
{
	clientSock = INVALID_SOCKET;
}
ClientBase::ClientBase(sockaddr_in _clientAddr,
	SOCKET _clientSock) :
	nextClient(0),
	prevClient(0)
{
	clientAddr = _clientAddr;
	clientSock = _clientSock;
}
ClientBase::~ClientBase()
{
	if (nextClient)
	{
		delete nextClient;
		nextClient = 0;
	}

}

void ClientBase::SetClientData(sockaddr_in _clientAddr, SOCKET _clientSock)
{
	clientAddr = _clientAddr;
	clientSock = _clientSock;

}
sockaddr_in ClientBase::GetAddr(){ return clientAddr; }

SOCKET ClientBase::GetSock(){ return clientSock; }

ClientBase *ClientBase::FindClientBySock(SOCKET sock)
{
	ClientBase *curClient = this;
	while (curClient != 0)
	{
		if (curClient->GetSock() == sock)
			return curClient;
		curClient = curClient->nextClient;
	}
	return 0;
}


QDir ClientBase::GetCurrentDir(){ return curDir; }
void ClientBase::SetCurrentDir(QDir newDir){ curDir = newDir; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
FTPServer::FTPServer(UI *_main_thread,
	QString _serverHomeDir,
	int _serverPort,
	qint64 _serverBitrate) :
	main_thread(_main_thread),
	serverHomeDir(_serverHomeDir),
	serverPort(_serverPort),
	serverBitrate(_serverBitrate),
	clients(0),
	isRunning(false)
{
	serverSock = INVALID_SOCKET;

	connect(this, SIGNAL(writeLog(const QString &)), main_thread, SLOT(WriteLogMessage(const QString &)));
	connect(this, SIGNAL(setFTPServerStatus(bool)), main_thread, SLOT(SetFTPServerStatus(bool)));
	connect(main_thread, SIGNAL(abortServer()), this, SLOT(AbortServer()));

	FD_ZERO(&serverSet);
}

FTPServer::~FTPServer()
{
}

void FTPServer::run()
{
	QString errStr;

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

	setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, (char *)(1), sizeof(1));

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

	ulong a = 0;
	ioctlsocket(serverSock, FIONBIO, &a);

	QString port;
	port.setNum(serverPort);
	errStr = "Set server port: ";
	errStr += port + ", server root dir: " + serverHomeDir.absolutePath();
	emit writeLog(errStr);

	emit setFTPServerStatus(true);

	isRunning = true;

	FTPServerRunning();


	emit setFTPServerStatus(false);
}

void FTPServer::AbortServer()
{
	if (serverSock > 0)
		closesocket(serverSock);

	ClientBase *cli = clients;
	while (cli != 0)
	{
		if (cli->clientSock > 0)
			closesocket(cli->clientSock);
		cli = cli->nextClient;
	}
	delete clients;
	clients = 0;

	emit writeLog("Server Aborted");
	isRunning = false;
}

int FTPServer::FTPServerRunning()
{
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000;

	int i = 0, err;

	fd_set read;
	fd_set write;

	ClientBase *curClient = 0;
	QString errStr;

	while (isRunning)
	{

		FD_ZERO(&read);
		FD_ZERO(&write);
		curClient = 0;

		// Always look for connection attempts
		FD_SET(serverSock, &read);
		for (i = 0; i < serverSet.fd_count; i += 1)
			FD_SET(serverSet.fd_array[i], &read);

		if ((err = select(0, &read, &write, NULL, NULL)) == SOCKET_ERROR)
		{
			isRunning = false;
			continue;
		}

		// read data
		//		tclock = clock();
		for (i = 0; i < read.fd_count; i += 1)
		{
			if (read.fd_array[i] == serverSock)
			{
				ulong a = 0;
				ioctlsocket(serverSock, FIONBIO, &a);

				curClient = Accept_new_Client();
				if (curClient)
				{
					emit writeLog("Successfully connected to server");
					errStr = inet_ntoa(curClient->GetAddr().sin_addr);
					emit writeLog("Client connect to " + errStr);
				}
			}
			else
			{
				curClient = clients->FindClientBySock(read.fd_array[i]);
				if (!curClient)
					continue;

				char streamType;

				if (recv(curClient->GetSock(), &streamType, 1, 0) == SOCKET_ERROR)
				{
					DeleteClient(curClient);
					continue;
				}

				if (send(curClient->GetSock(), &streamType, 1, 0) == SOCKET_ERROR)
				{
					DeleteClient(curClient);
					continue;
				}


				switch (streamType)
				{
				case 1:				/////  COMMAND
					if (ExecCommandOperation(curClient) == SOCKET_ERROR)
					{
						DeleteClient(curClient);
					}
					break;

				case 2:				/////  FILE
					emit writeLog("Server recieve file action");
					if (ExecFileOperation(curClient) == SOCKET_ERROR)
					{
						DeleteClient(curClient);
					}
					break;

				default:
					break;
				}
			}
		}
		//		tclock = clock() - tclock;
		//		Sleep(1000 - ((float)tclock) / CLOCKS_PER_SEC);

	}

	return 0;
}

/*
ClientBase *FTPServer::Accept_new_Client()
{
sockaddr_in newAddr;
int addrLength;
SOCKET newSock = accept(serverSock, (sockaddr*)&newAddr, &addrLength);
if (newSock == INVALID_SOCKET)
return 0;

char isOK = 1;
if (send(newSock, &isOK, 1, 0) == SOCKET_ERROR)
return 0 ;

///accept new client
ClientBase *newClient = new ClientBase(newAddr, newSock);
newClient->SetCurrentDir(serverHomeDir);

AddClient(newClient);

FD_SET(newClient->GetSock(), &serverSet);

return newClient;
}

int FTPServer::ExecCommandOperation(ClientBase *curClient)
{

char isOK = 1;
const int commandLength = 1000;
string strFSeq;
char *fileSequence = 0;
int fileSequenceLength = 1;
int i = 0;
ulong lFileSize;
char command[commandLength];
memset(command, 0, 1000);

if (recv(curClient->GetSock(), command, commandLength, 0) == SOCKET_ERROR)
return SOCKET_ERROR;

if (send(curClient->GetSock(), &isOK, 1, 0) == SOCKET_ERROR)
return SOCKET_ERROR;

QString cmdStr(command);
QStringList cmdStrList = cmdStr.split(" ");
QString cmd(cmdStrList[0]);
QString cmdArgs(cmdStrList[1]);
QDir chDir = curClient->GetCurrentDir();
QFileInfo checkFile;
QString strSequence;

bool accessAccept = true;
bool dirNoChanged = false;
if (cmd == "dir")
{
emit writeLog("Server recieve command action: " + cmdStr);
if (cmdArgs == "..")
{
if (serverHomeDir == curClient->GetCurrentDir())
{
emit writeLog("Can't change dir up to home dir. Access denied");
fileSequenceLength = 0;
}
else
{
chDir.cdUp();
curClient->SetCurrentDir(chDir);
}
}
else if (cmdArgs == ".")
fileSequenceLength = 1;
else
{
if(chDir.cd(cmdArgs))
curClient->SetCurrentDir(chDir);
else
fileSequenceLength = 0;
}

string sDir(chDir.absolutePath().toUtf8().constData());
if (send(curClient->GetSock(), (char*)(sDir.c_str()), MAX_PATH, 0) == SOCKET_ERROR)
return SOCKET_ERROR;

if (recv(curClient->GetSock(), &isOK, 1, 0) == SOCKET_ERROR)
return SOCKET_ERROR;

if (fileSequenceLength == 0)
{
strFSeq = "\0";
fileSequenceLength = 1;
}
else
{
cmdStrList = chDir.entryList();
QString sFSize;

for (i = 0; i < cmdStrList.size(); i++)
{
sFSize.clear();
checkFile.setFile(chDir, cmdStrList[i]);
if (cmdStrList[i] == ".")
{
strSequence += "0:";
sFSize = "DIR";
}
else if (cmdStrList[i] == "..")
{
strSequence += "1:";
sFSize = "DIR";
}
else if (checkFile.isDir())
{
strSequence += "2:";
sFSize = "DIR";
}
else if (checkFile.isFile())
{
strSequence += "3:";
lFileSize = checkFile.size();
sFSize.setNum(lFileSize);
}
else
{
strSequence += "4:";
sFSize = "UNKNOWN";
}

strSequence += cmdStrList[i] + ":" + sFSize + "\"";
}
fileSequenceLength = strSequence.size();
strFSeq.assign(strSequence.toUtf8().constData());
}

char sfileSequenceLength[4];
memcpy(sfileSequenceLength, &fileSequenceLength, 4);

if (send(curClient->GetSock(), sfileSequenceLength, 4, 0) == SOCKET_ERROR)
{
emit writeLog("Operation aborted due to socket error");
return SOCKET_ERROR;
}

if (recv(curClient->GetSock(), &isOK, 1, 0) == SOCKET_ERROR)
{
emit writeLog("Operation aborted due to socket error");
return SOCKET_ERROR;
}

fileSequence = (char*)strFSeq.c_str();
if (send(curClient->GetSock(), fileSequence, fileSequenceLength, 0) == SOCKET_ERROR)
return SOCKET_ERROR;

if (recv(curClient->GetSock(), &isOK, 1, 0) == SOCKET_ERROR)
return SOCKET_ERROR;

emit writeLog("Command executed successfully");
}

return 0;
}


int FTPServer::ExecFileOperation(ClientBase *curClient)
{
return SOCKET_ERROR;
}


SOCKET FTPServer::GetSock()
{
	return serverSock;
}

fd_set *FTPServer::GetSet()
{
	return &serverSet;
}

void FTPServer::AddClient(ClientBase *newClient) // add to 2nd position
{
	ClientBase *secondClient = clients;

	if (clients)
		secondClient->prevClient = newClient;
	clients = newClient;
	newClient->nextClient = secondClient;

	ulong a = 0;
	ioctlsocket(newClient->clientSock, FIONBIO, &a);
}

void FTPServer::DeleteClient(ClientBase *delClient)
{
	ClientBase *curClient = clients;
	ClientBase *next = 0, *prev = 0;
	while (curClient != 0)
	{
		if (curClient == delClient)
		{
			FD_CLR(delClient->clientSock, &serverSet);
			if (delClient->clientSock > 0)
				closesocket(delClient->clientSock);
			next = curClient->nextClient;
			prev = curClient->prevClient;
			if (next)
				next->prevClient = prev;
			if (prev)
				prev->nextClient = next;

			if (curClient == clients)
				clients = next;
			else
				curClient = next;

			delete delClient;
			delClient = 0;
			break;
		}
		curClient = curClient->nextClient;
	}
}*/