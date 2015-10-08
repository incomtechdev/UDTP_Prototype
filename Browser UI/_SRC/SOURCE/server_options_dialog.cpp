#include "server_options_dialog.h"
#include "config.h"
#include <QFileDialog>

Server_Options_dialog::Server_Options_dialog(UI_config *_data, QWidget *parent) :QDialog(parent), data(_data)
{
	ui.setupUi(this);
	ui.port_lineEdit->setText(data->getDataValue("ServerPort"));
	ui.bitrate_lineEdit->setText(data->getDataValue("ServerBitrate"));
	ui.homeDir_lineEdit->setText(data->getDataValue("ServerHomeDir"));

	connect(ui.usebitrate_checkBox, SIGNAL(stateChanged(int)), this, SLOT(UserBitrateCheck(int)));
	connect(ui.homeDirBrowse_pushButton, SIGNAL(clicked()), this, SLOT(BrowseHomeDir()));

	if (data->getDataValue("ServerBitrateAccept").toInt() == 0)
	{
		ui.usebitrate_checkBox->setChecked(Qt::Unchecked);
		ui.bitrate_lineEdit->setEnabled(false);
	}
	else
	{
		ui.usebitrate_checkBox->setCheckState(Qt::Checked);
		ui.bitrate_lineEdit->setEnabled(true);
	}
}

void Server_Options_dialog::closeEvent(QCloseEvent *event)
{
	data->setDataValue("ServerPort", ui.port_lineEdit->text());
	data->setDataValue("ServerHomeDir", ui.homeDir_lineEdit->text());

	if (ui.usebitrate_checkBox->checkState() == Qt::Checked)
	{
		data->setDataValue("ServerBitrateAccept", "1");
		data->setDataValue("ServerBitrate", ui.bitrate_lineEdit->text());
	}
	else
		data->setDataValue("ServerBitrateAccept", "0");

}

void Server_Options_dialog::UserBitrateCheck(int state)
{
	if (state == 0)
		ui.bitrate_lineEdit->setEnabled(false);
	else if (state == 2)
		ui.bitrate_lineEdit->setEnabled(true);
}

void Server_Options_dialog::BrowseHomeDir()
{
	QString fileName;
	if (!(fileName = QFileDialog::getOpenFileName(this, QString("Browse Server Home Directory"), QDir::currentPath())).isEmpty())
	{
		if (fileName.indexOf(" ") != -1)
			fileName = "\"" + fileName + "\"";
		ui.homeDir_lineEdit->setText(fileName);
	}
}