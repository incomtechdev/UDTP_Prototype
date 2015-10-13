#include "client_options_dialog.h"
#include "config.h"

Client_Options_dialog::Client_Options_dialog(UI_config *_data, QWidget *parent) :QDialog(parent), data(_data)
{
	ui.setupUi(this);
	ui.IP_lineEdit->setText(data->getDataValue("ServerIP"));
	ui.port_lineEdit->setText(data->getDataValue("ClientPort"));
	ui.bitrate_lineEdit->setText(data->getDataValue("ClientBitrate"));

	connect(ui.userbitrate_checkBox, SIGNAL(stateChanged(int)), this, SLOT(UserBitrateCheck(int)));

	if (data->getDataValue("ClientBitrateAccept").toInt() == 0)
	{
		ui.userbitrate_checkBox->setChecked(Qt::Unchecked);
		ui.bitrate_lineEdit->setEnabled(false);
	}
	else
	{
		ui.userbitrate_checkBox->setCheckState(Qt::Checked);
		ui.bitrate_lineEdit->setEnabled(true);
	}
}

void Client_Options_dialog::closeEvent(QCloseEvent *event)
{
	data->setDataValue("ServerIP", ui.IP_lineEdit->text());
	data->setDataValue("ClientPort", ui.port_lineEdit->text());
	if (ui.userbitrate_checkBox->checkState() == Qt::Checked)
	{
		data->setDataValue("ClientBitrateAccept", "1");
		data->setDataValue("ClientBitrate", ui.bitrate_lineEdit->text());
	}
	else
		data->setDataValue("ClientBitrateAccept", "0");

}

void Client_Options_dialog::UserBitrateCheck(int state)
{
	if (state == 0)
		ui.bitrate_lineEdit->setEnabled(false);
	else if (state == 2)
		ui.bitrate_lineEdit->setEnabled(true);
}