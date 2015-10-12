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

	FTPClient *client = new FTPClient;
	client->dir = mainWnd->getConfig()->getDataValue("ServerHomeDir");
	client->addr.sin_family = AF_INET;

	client->addr.sin_port = htons(ui.port_lineEdit->text().toShort());
	client->addr.sin_addr.s_addr = inet_addr(ui.IP_lineEdit->text().toUtf8().constData());
	client->sock = INVALID_SOCKET;
	if (mainWnd->getConfig()->getDataValue("ClientBitrateAccept").toInt() == 1)
		client->bitrate = mainWnd->getConfig()->getDataValue("ClientBitrate").toLong();
	else
		client->bitrate = 0;

	mainWnd->setFTPData(client);
	this->accept();
}


void UI::FTP_Client_Running()
{
	FTPClientRun = true;

	QString errStr;

	// create socket
	clientData->sock = socket(clientData->addr.sin_family, SOCK_STREAM, IPPROTO_TCP);

	if (clientData->sock == INVALID_SOCKET)
	{
		WriteLogMessage("Invalid Server Socket. Error " + errStr.setNum(WSAGetLastError()));
		AbortClient();
		return;
	}
	else if (clientData->sock == SOCKET_ERROR)
	{
		WriteLogMessage("Socket Server Error. Error " + errStr.setNum(WSAGetLastError()));
		AbortClient();
		return;
	}
	else
		WriteLogMessage("Client socket created succesfully");

	FTPClientRun = true;

	setsockopt(clientData->sock, SOL_SOCKET, SO_REUSEADDR, (char *)(1), sizeof (1));

//// coonect to server
	if (_connect(&clientData->sock, (sockaddr*)(&clientData->addr), sizeof(clientData->addr)) == SOCKET_ERROR)
	{
		WriteLogMessage("Socket Creating Error");
		AbortClient();
		return;
	}

	ftpPanel = fromToPanel[0];

	char isOK = 0;
	if (recv(clientData->sock, &isOK, 1, 0) == SOCKET_ERROR)
	{
		AbortClient();
		return;
	}

	ExecFTPCommand("dir .");

}

void UI::AbortClient()
{
	if (FTPClientRun)
	{
		UI::PANELS pID = ftpPanel;
		ftpPanel = UI::inactiveP;
		WriteLogMessage("Client Disconnected");
		closesocket(clientData->sock);

		ShowDirFiles(pID);
	}

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