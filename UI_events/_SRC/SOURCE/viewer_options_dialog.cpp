#include "viewer_options_dialog.h"
#include "config.h"
#include <QFileDialog>

Viewer_Options_dialog::Viewer_Options_dialog(UI_config *_data, QWidget *parent) :QDialog(parent), data(_data)
{
	ui.setupUi(this);
	ui.defaultEditor_lineEdit->setText(data->getDataValue("DefaultViewer"));
	ui.userdefinedEditor_lineEdit->setText(data->getDataValue("UsedViewer"));

	connect(ui.browse_defaultEditor_pushButton, SIGNAL(clicked()), this, SLOT(DefaultEditorBrowse()));
	connect(ui.browse_uderdefinedEditor_pushButton, SIGNAL(clicked()), this, SLOT(UserdefEditorBrowse()));
	connect(ui.OK_pushButton, SIGNAL(clicked()), this, SLOT(SaveChanges()));
	connect(ui.CANCEL_pushButton, SIGNAL(clicked()), this, SLOT(rejected()));
	connect(ui.RESET_pushButton, SIGNAL(clicked()), this, SLOT(SetDefaults()));
}

void Viewer_Options_dialog::DefaultEditorBrowse()
{
	QString fileName;
	if (!(fileName = QFileDialog::getOpenFileName(this, QString("Default Editor"), QDir::currentPath())).isEmpty())
	{
		if (fileName.indexOf(" ") != -1)
			fileName = "\"" + fileName + "\"";
		ui.defaultEditor_lineEdit->setText(fileName);
	}
}

void Viewer_Options_dialog::UserdefEditorBrowse()
{
	QString fileName;
	if (!(fileName = QFileDialog::getOpenFileName(this, QString("User Defined Editor"), QDir::currentPath())).isEmpty())
	{
		if (fileName.indexOf(" ") != -1)
			fileName = "\"" + fileName + "\"";
		ui.userdefinedEditor_lineEdit->setText(fileName);
	}
}

void Viewer_Options_dialog::SaveChanges()
{
	data->setDataValue("DefaultViewer", ui.defaultEditor_lineEdit->text());
	data->setDataValue("UsedViewer", ui.userdefinedEditor_lineEdit->text());

	accept();
}

void Viewer_Options_dialog::SetDefaults()
{
	ui.defaultEditor_lineEdit->setText("notepad.exe");
	ui.userdefinedEditor_lineEdit->setText("-");
}
