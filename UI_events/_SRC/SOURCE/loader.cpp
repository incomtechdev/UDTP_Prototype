#include "UI.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	int argc = 0;
	QApplication app(argc, 0);

    UI *wnd = new UI;

	wnd->show();
    return app.exec();
}