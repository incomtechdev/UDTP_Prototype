#pragma comment(lib,"Ws2_32.lib")
#include "FTP_server_thread.h"
#include "FTP_client_start.h"
#include "UI.h"
#include "udtp.h"

int _connect(
	_In_ SOCKET                *s,
	_In_ const struct sockaddr *name,
	_In_ int                   namelen
	)
{
	return connect(*s, name, namelen);
}

/*
uint32 udtp_BitRate(PUDTP_CONNECTION *conn);			//задать значение скорости передачи;
uint32 udtp_Delay(PUDTP_CONNECTION *conn);			//задать тип контрол€ значени€ задержки;
uint32 udtp_ControlBitRate(PUDTP_CONNECTION *conn);	//контроль скорости передачи;
//”правление сетевым идентификатором;
//** ѕока не используетс€ и не реализован
int udtp_NetID_Init();		//«агрузить NetID на сетевое устройство;
int udtp_NetID_Del();		//”далить NetID с сетевого устройства;
int udtp_NetID_Authen();	//ѕодтвердить достоверность NetID;
int udtp_NetID_Acct();		//«адать NetID получател€;
int udtp_NetID_Contact();	//ќбратитьс€ к NetID получател€;
//”правление переносом данных;
uint32 udtp_Chanel(UDTP_CHANEL *ch, sockaddr_in addr);	//создать канал св€зи;
//uint32 udtp_Open(UDTP_CHANEL *ch);	//открыть канал;
//uint32 udtp_Take(UDTP_CHANEL *ch);	//прин€ть канал;
uint32 udtp_ShutChanel(UDTP_CHANEL *ch);	//закрыть канал;
//uint32 udtp_Restore(UDTP_CHANEL *ch);	//восстановить канал;
uint32 udtp_Connect(UDTP_CHANEL *ch);	//установить соединение;
uint32 udtp_Accept(UDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//прин€ть соединение;
uint32 udtp_Close(PUDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//освободить соединение;
uint32 udtp_Send(PUDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//передать данные по соединению;
uint32 udtp_Receive(PUDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//прин€ть данные из соединени€;
uint32 udtp_Repeat(PUDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//повторить данные по соединению;
uint32 udtp_Crypto(PUDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//включить / отключить шифрование передаваемых данных;
uint32 udtp_FecDec(PUDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//включить / отключить помехозащитное кодирование данные.
*/

typedef uint32(__stdcall *UDTP_CONTROL)(PUDTP_CONNECTION *);
typedef int(__stdcall *UDTP_INIT)();
typedef uint32(__stdcall *UDTP_OPERATION)(PUDTP_CHANEL*, PUDTP_CONNECTION*);


////////////////////////////   FTP_SERVER /////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
ClientBase *FTPServer::Accept_new_Client()
{
	sockaddr_in newAddr;
	int addrLength;
	SOCKET newSock = 0;

	PUDTP_CHANEL *ch = 0;
	PUDTP_CONNECTION *conn = 0;

	bool isDLLFindFunc = false;
	if (main_thread->GetDLLHandle() != NULL)
	{
		UDTP_OPERATION udtp_Accept = (UDTP_OPERATION)GetProcAddress(main_thread->GetDLLHandle(), "udtp_Accept");

		if (isDLLFindFunc = (udtp_Accept != NULL))
		{
			if (udtp_Accept(ch, conn) == SOCKET_ERROR)
				return 0;
		}
	}

	if (!isDLLFindFunc)
	{
		newSock = accept(serverSock, (sockaddr*)&newAddr, &addrLength);
		if (newSock == INVALID_SOCKET)
			return 0;

		char isOK = 1;
		if (send(newSock, &isOK, 1, 0) == SOCKET_ERROR)
			return 0;
	}

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
			if (chDir.cd(cmdArgs))
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

/////////////////////////   END FTP  SERVER   ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

/////////////////////////    CLIENT   ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
int UI::Connect_Client()
{

	if (_connect(&clientData->sock, (sockaddr*)(&clientData->addr), sizeof(clientData->addr)) == SOCKET_ERROR)
		return SOCKET_ERROR;

	char isOK = 0;
	if (recv(clientData->sock, &isOK, 1, 0) == SOCKET_ERROR)
		return SOCKET_ERROR;

	return 0;
}


int UI::ExecFTPCommand(const QString &command)
{
	char isOK = 1;
	const char commandMark = 1;
	char sfileSequenceLength[4];

	ulong a = 0;
	ioctlsocket(clientData->sock, FIONBIO, &a);

	if (send(clientData->sock, &commandMark, 1, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	if (recv(clientData->sock, &isOK, 1, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	string cmd(command.toUtf8().constData());
	if (send(clientData->sock, (char*)(cmd.c_str()), cmd.size(), 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	if (recv(clientData->sock, &isOK, 1, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	char cftpDir[MAX_PATH];
	if (recv(clientData->sock, cftpDir, MAX_PATH, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	if (send(clientData->sock, &isOK, 1, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}
	clientData->dir = cftpDir;


	if (recv(clientData->sock, sfileSequenceLength, 4, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	if (send(clientData->sock, &isOK, 1, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	ulong fileSequenceLength = *((ulong*)&sfileSequenceLength);
	char *fileSequence = new char[fileSequenceLength];

	if (recv(clientData->sock, fileSequence, fileSequenceLength, 0) == SOCKET_ERROR)
	{
		delete fileSequence;
		AbortClient();
		return SOCKET_ERROR;
	}

	if (send(clientData->sock, &isOK, 1, 0) == SOCKET_ERROR)
	{
		delete fileSequence;
		AbortClient();
		return SOCKET_ERROR;
	}

	if (fileSequenceLength == 1)
		return 0;

	QString sFileSequence(fileSequence);
	QStringList fileList = sFileSequence.split("\"");
	fileList.sort();

	ShowDirFiles(ftpPanel, &fileList);

	return 0;
}

///////////////////////////   END  CLIENT                             //////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////