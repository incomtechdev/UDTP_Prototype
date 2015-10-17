#include <QApplication>
#include "QUdtpSocket.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	SocketData servAddr;
	servAddr.addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.addr.sin_port = htons(10000);

	int argc = 0;
	QApplication app(argc, 0);

	const int serverSocketsNumber = 30;
	const int minSocketsNumber = 1;

	const int MAX_BITRATE = 100;
	serverThread *newserver = new serverThread(&servAddr, MAX_BITRATE, serverSocketsNumber);
	newserver->start();


	clientThread *newclient = new clientThread(&servAddr);
	newclient->start();


// STRESS TEST
	int i = 0;

	if (serverSocketsNumber > 1)
	{
		clientThread *newclient2[serverSocketsNumber - 1];

		for (i = 0; i < serverSocketsNumber - 1; i++)
		{
			servAddr.addr.sin_port = htons(SERVER_CHANNELS_BEGIN + i);
			newclient2[i] = new clientThread(&servAddr);
			newclient2[i]->start();
		}
	}

    return app.exec();
///////////   END STRESS TEST
}

void clientThread::run()
{
	//		serv.eventThread->connect(serv.eventThread, SIGNAL(acceptClient(SocketData *)), &serv, SLOT(acceptClient(SocketData *)));

	cli.connectToServer();

	char *str1 = "this is a test: rwerwerqwefddfghrtgrtggef  erferterfefwerwetregefvfdseferfr fgegegerferfefergergegtgtg htyhyhrthrtgrgererthgfhg efgetgrtyrtgfgdfewrer hrthrtyrgdfgdrgergrthrht df    12345";
	cli.sendToServer(str1, strlen(str1)+1);

	char str[120];
	cli.recvFromServer(str, 120);
	this->exec();
}

int QUdtpSocket::acceptClient(SocketData *data)
{
	clientBasePair curClient(data->sock, new SocketData);

	curClient.second->sock = data->sock;
	curClient.second->addr.sin_family = data->addr.sin_family;
	curClient.second->addr.sin_port = data->addr.sin_port;
	curClient.second->addr.sin_addr.s_addr = data->addr.sin_addr.s_addr;


	curClient.second->bitrate = DESCRIPTOR_LENGTH;
	curClient.second->isReadDescriptor = false;


	clients.insert(curClient);
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

	memcpy(buf + 1, &cli->bitrate, 4);
	memcpy(buf + DESCRIPTOR_LENGTH, bstr.c_str() + cli->bytessend, cli->bitrate);

	return 0;
}