#include "UI.h"

UI::UI(QWidget *parent) : QMainWindow(parent),
						  left_dir(0),
						  right_dir(0),
						  currentPanel(0),
						  ftpPanel(0)
{
	ui.setupUi(this);
	QFileInfoList drivesList = QDir::drives();
	int driveCount = drivesList.size();
	left_dir = new QDir[driveCount];
	right_dir = new QDir[driveCount];

	QDir currentDir(QDir::current());
	int i = 0, currentDrive = 0;
	for (i = 0; i < drivesList.size(); i++)
	{
		ui.driveleft_comboBox->addItem(drivesList[i].path());
		ui.driveright_comboBox->addItem(drivesList[i].path());
		if (currentDir.absolutePath().indexOf(drivesList[i].path())==0)
		{
			left_dir[i] = currentDir;
			right_dir[i] = currentDir;
			currentDrive = i;
		}
		else
		{
			left_dir[i] = drivesList[i].path();
			right_dir[i] = drivesList[i].path();
		}
	}
	ui.driveleft_comboBox->setCurrentIndex(currentDrive);
	ui.driveright_comboBox->setCurrentIndex(currentDrive);


	ui.left_tableWidget->setColumnCount(2);
	ui.right_tableWidget->setColumnCount(2);
	ShowDirFiles(PANELS::leftP);
	ShowDirFiles(PANELS::rightP);

	connect(ui.left_tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(changeDirFromFileSystem(QTableWidgetItem *)));
	connect(ui.right_tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(changeDirFromFileSystem(QTableWidgetItem *)));
	connect(ui.driveleft_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeLeftDrive(int)));
	connect(ui.driveright_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeRightDrive(int)));

}

UI::~UI()
{
	if (left_dir)
		delete[] left_dir;
	if (right_dir)
		delete[] right_dir;
}

void UI::ShowDirFiles(PANELS pID)
{
	int driveInd;
	switch (pID)
	{
	case PANELS::leftP:
		driveInd = ui.driveleft_comboBox->currentIndex();
		ShowFilesFromPanel(ui.left_tableWidget, &left_dir[driveInd]);
		ui.left_path_lineEdit->setText(left_dir[driveInd].path());
		break;
	case PANELS::rightP:
		driveInd = ui.driveright_comboBox->currentIndex();
		ShowFilesFromPanel(ui.right_tableWidget, &right_dir[driveInd]);
		ui.right_path_lineEdit->setText(right_dir[driveInd].path());
		break;
	default:
		WriteLogMessage("Error in ShowDirFiles function");
	}
}

void UI::ShowFilesFromPanel(QTableWidget *panel, QDir *dir)
{
	QStringList dirFiles;
	QStringList files;
	QFileIconProvider fp;
	QTableWidgetItem *item;
	int i = 0;
	if (dir->exists())
	{

		panel->clear();
		dirFiles = dir->entryList(QDir::AllDirs, QDir::Name);
		panel->setRowCount(dirFiles.count());
		for (i = 0; i < dirFiles.count(); i++)
		{
			item = new QTableWidgetItem(dirFiles[i]);
			item->setIcon(fp.icon(QFileInfo(dir->filePath(dirFiles[i]))));
			panel->setItem(i, 0, item);
			item = new QTableWidgetItem("DIR");
			panel->setItem(i, 1, item);
			panel->setRowHeight(i, 14);
		}
		int dircount = dirFiles.count();
		dirFiles = dir->entryList(QDir::Files, QDir::Name);
		panel->setRowCount(dircount + dirFiles.count());
		for (i = 0; i < dirFiles.count(); i++)
		{
			item = new QTableWidgetItem(dirFiles[i]);
			item->setIcon(fp.icon(QFileInfo(dir->filePath(dirFiles[i]))));
			panel->setItem(dircount + i, 0, item);
			QFile f(dir->absoluteFilePath(dirFiles[i]));
			qint64 fsize = 0;
			if (f.open(QIODevice::ReadOnly))
			{
				fsize = f.size();  //when file does open.
				f.close();
			}
			item = new QTableWidgetItem(QString::number(fsize));
			panel->setItem(dircount + i, 1, item);
			panel->setRowHeight(dircount + i, 14);
		}
	}
}

void UI::WriteLogMessage(const QString message)
{
	ui.log_listWidget->addItem(message);
}

void UI::changeDirFromFileSystem(QTableWidgetItem * item)
{
	QTableWidget *panel = item->tableWidget();
	QDir *panel_dir;
	PANELS pID;
	int driveInd;

	if (panel == ui.left_tableWidget)
	{
		driveInd = ui.driveleft_comboBox->currentIndex();
		panel_dir = &left_dir[driveInd];
		pID = PANELS::leftP;
	}
	else
	{
		driveInd = ui.driveright_comboBox->currentIndex();
		panel_dir = &right_dir[driveInd];
		pID = PANELS::rightP;
	}


	int curInd = panel->currentRow();
	item = panel->item(curInd, 0);
	if (item->text() == ".")
		return;
	else if (item->text() == "..")
	{
		if (!panel_dir->cdUp())
			WriteLogMessage("Can't change dir. Permission denied.");
	}
	else
	{
		if (!panel_dir->cd(item->text()))
		{
			QFileInfo f(item->text());
			if (!f.isFile())
				WriteLogMessage("Can't change dir. Permission denied.");
		}
	}

	ShowDirFiles(pID);
}

void UI::ChangeLeftDrive(int index)
{
	ShowDirFiles(PANELS::leftP);
}

void UI::ChangeRightDrive(int index)
{
	ShowDirFiles(PANELS::rightP);
}
