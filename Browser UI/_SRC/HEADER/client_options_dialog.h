#include "ui_FTP_client_options.h"

using namespace std;

class UI_config;

class Client_Options_dialog : public QDialog
{
	Q_OBJECT

private:
	Ui::FTP_clientOptions_Dialog ui;
	UI_config *data;

	void closeEvent(QCloseEvent *event);

public:
	Client_Options_dialog(UI_config *_data, QWidget *parent = 0);


public slots:
	void UserBitrateCheck(int state);
};