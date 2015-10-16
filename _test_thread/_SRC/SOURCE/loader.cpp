#include <QApplication>
#include "QUdtpSocket.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	WSADATA data;
	if (WSAStartup(0x0202, &data) != 0)
		WSACleanup();

	SocketData servAddr;
	servAddr.addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.addr.sin_port = htons(10000);

	int argc = 0;
	QApplication app(argc, 0);

	const int MAX_BITRATE = 100;
	serverThread *newserver = new serverThread(&servAddr, MAX_BITRATE);
	newserver->start();

	clientThread *newclient = new clientThread(&servAddr);
	newclient->start();

    return app.exec();

}

void clientThread::run()
{
	//		serv.eventThread->connect(serv.eventThread, SIGNAL(acceptClient(SocketData *)), &serv, SLOT(acceptClient(SocketData *)));

	cli.connectToServer();

	Sleep(2000);
	int a = 0;

	char *str1 = "this is a test: rwerwerqwefddfghrtgrtggef  erferterfefwerwetregefvfdseferfr fgegegerferfefergergegtgtg htyhyhrthrtgrgererthgfhg efgetgrtyrtgfgdfewrer hrthrtyrgdfgdrgergrthrht df    12345";
	cli.sendToServer(str1, strlen(str1)+1);

	char str[20];
	cli.recvFromServer(str, 20);
	this->exec();
}

int QUdtpSocket::acceptClient(SocketData *data)
{

	client = new SocketData;

	client->sock = data->sock;
	client->addr.sin_family = data->addr.sin_family;
	client->addr.sin_port = data->addr.sin_port;
	client->addr.sin_addr.s_addr = data->addr.sin_addr.s_addr;


	client->bitrate = DESCRIPTOR_LENGTH;
	client->isReadDescriptor = false;

	return 0;
}


int QUdtpSocket::fillServerData(char *buf, int len)
{
	char *cStr = new char[len + 1];
	cStr[len] = '\0';
	strncpy(cStr, buf, len);
	str.append(cStr);
	str.append(" :: ");

	delete cStr;
	return 0;
}

int QUdtpSocket::getStringFromServer(SocketData *cli, char *buf)
{
	memset(buf, 0, cli->bitrate);
	string bstr(str.toUtf8().constData());
	int size = bstr.size();

	memcpy(buf, bstr.c_str() + cli->bytessend, cli->bitrate);

	return 0;
}