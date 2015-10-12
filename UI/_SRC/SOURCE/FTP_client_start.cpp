#include "FTP_client_start.h"
#include "UI.h"

int _connect(
	_In_ SOCKET                *s,
	_In_ const struct sockaddr *name,
	_In_ int                   namelen
	)
{
	return connect(*s, name, namelen);
}


FTP_Client_Start_dialog::FTP_Client_Start_dialog(UI *_mainWnd) :QDialog(_mainWnd), mainWnd(_mainWnd)
{
	ui.setupUi(this);
	UI_config *conf = mainWnd->getConfig();

	ui.IP_lineEdit->setText(conf->getDataValue("ServerIP"));
	ui.port_lineEdit->setText(conf->getDataValue("ClientPort"));
	ui.loginpass_radioButton->setCheckable(true);

	connect(ui.loginpass_radioButton, SIGNAL(toggled(bool)), this, SLOT(SetLogPathAuth(bool)));
	connect(ui.authID_radioButton, SIGNAL(toggled(bool)), this, SLOT(SetIDAuth(bool)));
	connect(ui.cancel_pushButton, SIGNAL(clicked()), this, SLOT(onCancel()));
	connect(ui.clientConnect_pushButton, SIGNAL(clicked()), this, SLOT(onConnect()));

	ui.loginpass_radioButton->setChecked(true);
}

void FTP_Client_Start_dialog::SetLogPathAuth(bool checked)
{
	if (checked)
	{
		ui.login_lineEdit->setEnabled(true);
		ui.password_lineEdit->setEnabled(true);
		ui.authID_lineEdit->setEnabled(false);
	}
}

void FTP_Client_Start_dialog::SetIDAuth(bool checked)
{
	if (checked)
	{
		ui.login_lineEdit->setEnabled(false);
		ui.password_lineEdit->setEnabled(false);
		ui.authID_lineEdit->setEnabled(true);
	}
}

void FTP_Client_Start_dialog::onCancel()
{
	this->reject();
}

void FTP_Client_Start_dialog::onConnect()
{
	this->accept();
	FTPClient *client = new FTPClient;
	client->ftpDir = mainWnd->getConfig()->getDataValue("ServerHomeDir");
	client->serverAddr.sin_family = AF_INET;

	client->serverAddr.sin_port = htons(ui.port_lineEdit->text().toShort());
	client->serverAddr.sin_addr.s_addr = inet_addr(ui.IP_lineEdit->text().toStdString().c_str());
	client->serverSock = INVALID_SOCKET;
	if (mainWnd->getConfig()->getDataValue("ClientBitrateAccept").toInt() == 1)
		client->serverBitrate = mainWnd->getConfig()->getDataValue("ClientBitrate").toLong();
	else
		client->serverBitrate = 0;

	mainWnd->setFTPData(client);
}


void UI::FTP_Client_Running()
{
	FTPClientRun = true;

	QString errStr;
	// Initialize WinSock
	if (WSAStartup(0x0202, &clientData->wsaData) != 0)
	{
		WriteLogMessage("Error in starting WSAStartup()");
		AbortClient();
	}

	// create socket
	clientData->serverSock = socket(clientData->serverAddr.sin_family, SOCK_STREAM, IPPROTO_TCP);

	if (clientData->serverSock == INVALID_SOCKET)
	{
		WriteLogMessage("Invalid Server Socket. Error " + errStr.setNum(WSAGetLastError()));
		AbortClient();
		return;
	}
	else if (clientData->serverSock == SOCKET_ERROR)
	{
		WriteLogMessage("Socket Server Error. Error " + errStr.setNum(WSAGetLastError()));
		AbortClient();
		return;
	}
	else
		WriteLogMessage("Client socket created succesfully");

	u_long iMode = 0;
	ioctlsocket(clientData->serverSock, FIONBIO, &iMode);

	FTPClientRun = true;

//	setsockopt(clientData->serverSock, SOL_SOCKET, SO_REUSEADDR, (char *)(1), sizeof (1));

//// coonect to server
	if (_connect(&clientData->serverSock, (sockaddr*)(&clientData->serverAddr), sizeof(clientData->serverAddr)) == SOCKET_ERROR)
	{
		WriteLogMessage("Socket Creating Error");
		AbortClient();
		return;
	}

	ftpPanel = fromToPanel[0];

	char isOK = 0;
	if (recv(clientData->serverSock, &isOK, 1, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return;
	}
/*	if (recv(clientData->serverSock, &isOK, 1, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return;
	}*/

	ExecFTPCommand("dir .");

}

void UI::AbortClient()
{
	if (FTPClientRun)
	{
		UI::PANELS pID = ftpPanel;
		ftpPanel = UI::inactiveP;
		WriteLogMessage("Client Disconnected");
		closesocket(clientData->serverSock);

		ShowDirFiles(pID);
	}

	WSACleanup();

	if (clientData)
	{
		delete clientData;
		clientData = 0;
	}

	FTPClientRun = false;
}

int UI::ExecFTPCommand(const QString &command)
{
	char isOK = 1;
	const char commandMark = 1;
	char sfileSequenceLength[4];

	if (send(clientData->serverSock, &commandMark, 1, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	if (recv(clientData->serverSock, &isOK, 1, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	string cmd(command.toStdString());
	if (send(clientData->serverSock, (char*)(cmd.c_str()), cmd.size(), 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	if (recv(clientData->serverSock, &isOK, 1, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	char cftpDir[MAX_PATH];
	if (recv(clientData->serverSock, cftpDir, MAX_PATH, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	if (send(clientData->serverSock, &isOK, 1, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}
	clientData->ftpDir = cftpDir;


	if (recv(clientData->serverSock, sfileSequenceLength, 4, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	if (send(clientData->serverSock, &isOK, 1, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return SOCKET_ERROR;
	}

	ulong fileSequenceLength = *((ulong*)&sfileSequenceLength);
	char *fileSequence = new char[fileSequenceLength];

	if (recv(clientData->serverSock, fileSequence, fileSequenceLength, 0) == SOCKET_ERROR)
	{
		delete fileSequence;
		AbortClient();
		return SOCKET_ERROR;
	}

	if (send(clientData->serverSock, &isOK, 1, 0) == SOCKET_ERROR)
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