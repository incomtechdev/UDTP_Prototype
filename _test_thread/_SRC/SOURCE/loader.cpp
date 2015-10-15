#include <QApplication>
#include "QUdtpSocket.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{

	SocketData servAddr;
	servAddr.addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.addr.sin_port = htons(10000);

	int argc = 0;
	QApplication app(argc, 0);

	serverThread *newserver = new serverThread(&servAddr);
	newserver->start();

	clientThread *newclient = new clientThread(&servAddr);
	newclient->start();

    return app.exec();

}

void clientThread::run()
{
	//		serv.eventThread->connect(serv.eventThread, SIGNAL(acceptClient(SocketData *)), &serv, SLOT(acceptClient(SocketData *)));

	cli.connectToServer();

	int a = 0;

	char *str1 = "this is a test";
	cli.sendToServer(str1, 10);
	cli.sendToServer(str1 + 5, 6);
	char str[20];
	cli.recvFromServer(str, 20);
	this->exec();
}

int QUdtpSocket::fillServerData(char *buf, int len)
{
	str.append(buf);
	str.append(" :: ");

	cond.wakeAll();

	return 0;
}

int QUdtpSocket::getStringFromServer(char *buf, int len)
{
	memset(buf, 0, len);
	string bstr(str.toUtf8().constData());
	int size = bstr.size();
	if (size < len)
		len = size;
	memcpy(buf, bstr.c_str(), len);

	cond.wakeAll();

	return 0;
}