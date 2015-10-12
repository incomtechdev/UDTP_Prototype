#ifndef _FTP_CLIENT_START_DIALOG_
#define _FTP_CLIENT_START_DIALOG_

#include "FTP_client_server_classes.h"
#include "ui_FTP_client_connection.h"

#pragma comment(lib,"Ws2_32.lib")
#include <winsock2.h>
#include <windows.h>

using namespace std;

class UI;

int _connect(
	_In_ SOCKET                *s,
	_In_ const struct sockaddr *name,
	_In_ int                   namelen
	);

struct FTPClient
{
	QString dir;
	sockaddr_in addr;
	SOCKET sock;
	qint64 bitrate;
};

class FTP_Client_Start_dialog :public QDialog
{
	Q_OBJECT

private:
	Ui::FTP_connect_Dialog ui;
	UI *mainWnd;

public:
	FTP_Client_Start_dialog(UI *_mainWnd);

public slots:
	void SetLogPathAuth(bool checked);
	void SetIDAuth(bool checked);
	void onCancel();
	void onConnect();
};




#endif
