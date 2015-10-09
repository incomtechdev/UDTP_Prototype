#include "FTP_server_thread.h"
#include "UI.h"

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

ClientBase::ClientBase()
{}
ClientBase::ClientBase(sockaddr_in _clientAddr, SOCKET _clientSock)
{
	clientAddr = _clientAddr;
	clientSock = _clientSock;
}
ClientBase::~ClientBase()
{}
void ClientBase::SetClientData(sockaddr_in _clientAddr, SOCKET _clientSock)
{
	clientAddr = _clientAddr;
	clientSock = _clientSock;
}
sockaddr_in ClientBase::GetAddr(){ return clientAddr; }

SOCKET ClientBase::GetSock(){ return clientSock; }

void ClientBase::AddClient(ClientBase *newClient)
{
	if (base == 0)
		newClient->firstClient = this;
}
void ClientBase::DeleteClient(ClientBase *delClient)
{}
ClientBase *ClientBase::FindClientBySock(SOCKET sock)
{}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
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

	FTPServerRunning();

}

void FTPServer::AbortServer()
{
	WSACleanup();
	if (serverSock > 0)
		closesocket(serverSock);
	emit writeLog("Server Aborted");
	emit setFTPServerStatus(false);
}

int FTPServer::FTPServerRunning()
{
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000;

	int err;

	fd_set read;
	fd_set write;

	char *fbuffer = 0;
	uint32 fbuffSize;
	uint32 bitrate;
	unsigned int i = 0;
	Client *curClient = 0;
	FName f;
	int actionID = 0;
	bool rdyState = false;
	ofstream os;
	char uploadDir[FILENAME_LENGTH * 2] = "../Uploads/";
	clock_t tclock;
	bool isOK;
	ios::openmode m = ios::out | ios::app | ios::binary;

	while (data->runner)
	{

		FD_ZERO(&read);
		FD_ZERO(&write);
		curClient = 0;

		// Always look for connection attempts
		FD_SET(data->info.getChannel(CHANNELTYPE::data).sock, &read);
		for (i = 0; i < data->set.fd_count; i += 1)
		{
			FD_SET(data->set.fd_array[i], &read);
		}

		if ((err = select(0, &read, &write, NULL, NULL)) == SOCKET_ERROR)
		{
			printf("select() returned with error %d\n", WSAGetLastError());
			return 1;
		}
		else
			printf("server recieve action:");

		///   accept new client
		if (FD_ISSET(data->info.getChannel(CHANNELTYPE::data).sock, &read))
		{
			err = Accept_new_Client();
			if (!err)
				printf(" new client connection failed\n");
			continue;
		}
		// read data
		tclock = clock();
		for (i = 0; i < read.fd_count; i += 1)
		{
			curClient = getClientBySocket(read.fd_array[i]);
			if (!curClient)
				break;

			char *buf = 0;

			buf = udtp_recv(curClient->info.getChannel(CHANNELTYPE::data), MODE::command);

			if (!buf)
			{
				disconnectClient(curClient);
				break;
			}

			string bufStr(buf);
			int tab = bufStr.find(" ");
			string command = bufStr.substr(0, tab);
			string commandDir = bufStr.substr(tab + 1);
			string changeDir(curClient->currentDir);
			bool accessAccept = true;
			bool dirNoChanged = false;
			if (command == "dir")
			{
				printf("server recieve command: %s\n", buf);
				if (commandDir == "..")
				{
					changeDir = changeDir.substr(0, changeDir.find_last_of("\\"));
					if (changeDir.find(AccessDir) == string::npos)
					{
						accessAccept = false;
						changeDir = AccessDir;
					}

				}
				else if (commandDir == ".")
					dirNoChanged = true;
				else
					changeDir = changeDir + "\\" + commandDir;

				char *flist = 0;

				if (dirNoChanged)
				{
					flist = new char[2];
					flist[0] = 2;
					flist[1] = '\0';
				}
				if ((flist = getDirFiles(changeDir.c_str())) == 0)
				{
					changeDir.assign(curClient->currentDir);
					flist = new char[2];
					flist[0] = 1;
					flist[1] = '\0';
				}

				if (!accessAccept)
				{
					delete[] flist;
					flist = new char[2];
					flist[0] = 0;
					flist[1] = '\0';
				}

				dbug = udtp_send(curClient->info.getChannel(CHANNELTYPE::data), MODE::stream, flist, strlen(flist) + 1);
				if (dbug == SOCKET_ERROR)
				{
					disconnectClient(curClient);
					break;
				}

				if (flist)
					delete[] flist;
				strcpy(curClient->currentDir, changeDir.c_str());
			}

			delete[] buf;
			/*			else if (curClient->status == 1)
			{
			// header is reading
			rdyState = false;
			dbug = recv(curClient->info.sourceAddr.sock, (char*)&f, sizeof(FName), 0);
			if (dbug <= 0)
			{
			disconnectClient(curClient);
			break;
			}
			cout << f.getFullPath() << endl;

			strcpy(curClient->file.dirPath, f.dirPath);
			strcpy(curClient->file.fileName, f.fileName);

			curClient->file.setDir(uploadDir);
			rdyState = true;
			//	char * rdyState = "download";
			dbug = send(curClient->info.sourceAddr.sock, (char*)&rdyState, sizeof(rdyState), 0);
			if (dbug <= 0)
			{
			disconnectClient(curClient);
			break;
			}
			if (file_exists(curClient->file.getFullPath()))
			m = ios::out | ios::trunc | ios::binary;
			else
			m = ios::out | ios::app | ios::binary;
			curClient->status = 2; // client is ready for download
			printf(" file name send\n");

			}
			else if (curClient->status == 2)
			{
			// ready for download
			if (!os.is_open())
			os.close();

			os.open(curClient->file.getFullPath(), m);

			fbuffSize = sizeof(char)*curClient->info.bit + sizeof(transportData);
			fbuffer = (char*)malloc(fbuffSize);
			dbug = recv(curClient->info.sourceAddr.sock, fbuffer, fbuffSize, 0);
			if (dbug <= 0)
			{
			os.close();
			disconnectClient(curClient);
			free(fbuffer);
			break;
			}

			bitrate = curClient->info.bit;
			if (fbuffer[0] != 0)
			{
			bitrate = 0;
			for (i = 0; i < sizeof(uint32); i++)
			bitrate = (bitrate >> 8) + fbuffer[i+1];
			}
			os.write(fbuffer+sizeof(transportData), bitrate);

			printf(" %d bytes transfer\n", bitrate);

			if (bitrate < curClient->info.bit)
			{
			isOK = true;
			printf(" End transfer\n");
			dbug = send(curClient->info.sourceAddr.sock, (char*)&isOK, sizeof(bool), 0);
			isOK = false;
			curClient->status = 0;
			}
			os.close();
			m = ios::out | ios::app | ios::binary;
			free(fbuffer);
			}
			else
			printf(" action failed\n");*/
		}
		tclock = clock() - tclock;
		Sleep(1000 - ((float)tclock) / CLOCKS_PER_SEC);

	}

	return 0;
}

Client *FtpServer::getClientBySocket(SOCKET sock)
{
	Client *curCli = data->nextCli;

	while (curCli)
	{
		if (curCli->info.getChannel(CHANNELTYPE::data).sock == sock
			|| curCli->info.getChannel(CHANNELTYPE::control).sock == sock
			|| curCli->info.getChannel(CHANNELTYPE::error).sock == sock
			|| curCli->info.getChannel(CHANNELTYPE::status).sock == sock)
			return curCli;
		curCli = curCli->nextCli;
	}
	return 0;
}

int FtpServer::Accept_new_Client()
{
	///accept new client
	Client *newClient = (Client *)malloc(sizeof(Client));
	newClient->init();

	NETID *newClientData = udtp_accept(0, &data->info, 0, 0, 0, 0, 0);

	if (newClientData == 0)
	{
		free(newClient);
		return 0;
	}

	newClient->info = *newClientData;
	free(newClientData);

	newClient->conn = true;
	newClient->runner = true;
	strcpy(newClient->currentDir, AccessDir.c_str());
	updateStatus(CLIENT_CONN);

	if (data->nextCli)
		data->nextCli->prevCli = newClient;
	newClient->nextCli = data->nextCli;
	newClient->prevCli = data;
	data->nextCli = newClient;
	FD_SET(newClient->info.getChannel(CHANNELTYPE::data).sock, &data->set);
	FD_SET(newClient->info.getChannel(CHANNELTYPE::control).sock, &data->set);
	FD_SET(newClient->info.getChannel(CHANNELTYPE::error).sock, &data->set);
	FD_SET(newClient->info.getChannel(CHANNELTYPE::status).sock, &data->set);

	return 1;
}