#include <QApplication>
#include "QUdtpSocket.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	int argc = 0;
	QApplication app(argc, 0);

	QUdtpSocket newServ(0);
	newServ.createServerSocket();
	QUdtpSocket newCli(1);

	SocketData servAddr;
	servAddr.addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.addr.sin_port = htons(10000);

	newCli.createClientSocket(&servAddr);

	newCli.connectSocket();

	int a = 0;

    return app.exec();

}