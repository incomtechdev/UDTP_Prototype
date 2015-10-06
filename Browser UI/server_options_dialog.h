#include "ui_FTP_server_options.h"
//#include "config.h"

using namespace std;

class UI_config;

class Server_Options_dialog : public QDialog
{
	Q_OBJECT

private:
	Ui::FTP_serverOptions_Dialog ui;
	UI_config *data;

	void closeEvent(QCloseEvent *event);

public:
	Server_Options_dialog(UI_config *_data, QWidget *parent = 0);


public slots:
	void UserBitrateCheck(int state);
};