#include "UI.h"
#include "server_options_dialog.h"
#include "client_options_dialog.h"
#include "viewer_options_dialog.h"
#include "progress_copy_dialog.h"
#include "FTP_server_thread.h"
#include "FTP_client_start.h"
#include <QKeyEvent>
#include <QProcess>

UI::UI(QWidget *parent) :   QMainWindow(parent),
							left_dir(0),
							right_dir(0),
							ftpPanel(inactiveP),
							config_data("conf.txt"),
							serverThread(0),
							clientData(0),
							FTPServerRun(false),
							FTPClientRun(false)
{
	ui.setupUi(this);


	fromToPanel[0] = UI::inactiveP;
	fromToPanel[1] = UI::inactiveP;
	fromToPanelWidget[0] = ui.left_tableWidget;
	fromToPanelWidget[1] = ui.right_tableWidget;

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
	ShowDirFiles(UI::leftP);
	ShowDirFiles(UI::rightP);

	connect(ui.left_tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(changeDirFromFileSystem(QTableWidgetItem *)));
	connect(ui.right_tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(changeDirFromFileSystem(QTableWidgetItem *)));

	connect(ui.left_tableWidget, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(SetWorkingLeftPanel(QTableWidgetItem *)));
	connect(ui.right_tableWidget, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(SetWorkingRightPanel(QTableWidgetItem *)));
	
	connect(ui.driveleft_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeLeftDrive(int)));
	connect(ui.driveright_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeRightDrive(int)));

	connect(ui.action_MenuServerOptions, SIGNAL(triggered(bool)), this, SLOT(OpenServerOptions(bool)));
	connect(ui.action_MenuClientOptions, SIGNAL(triggered(bool)), this, SLOT(OpenClientOptions(bool)));
	connect(ui.action_ViewOptions, SIGNAL(triggered(bool)), this, SLOT(OpenViewerOptions(bool)));

	connect(ui.action_ToolServerStarted, SIGNAL(triggered(bool)), this, SLOT(StartFTPServer(bool)));
	connect(ui.action_MenuServerStarted, SIGNAL(triggered(bool)), this, SLOT(StartFTPServer(bool)));

	connect(ui.action_MenuClientConnected, SIGNAL(triggered(bool)), this, SLOT(StartFTPClient(bool)));
	connect(ui.action_ToolClientConnected, SIGNAL(triggered(bool)), this, SLOT(StartFTPClient(bool)));

	ui.left_tableWidget->selectRow(0);
	SetWorkingLeftPanel(ui.left_tableWidget->item(0, 0));

	if (WSAStartup(0x0202, &wsaData) != 0)
	{
		WriteLogMessage("Error in starting WSAStartup()");
		WSACleanup();
	}

	QString udtp_dll_path = config_data.getDataValue("UDTPdllPath");
	LPCWSTR dllLibName = (const wchar_t*)udtp_dll_path.utf16();
	dllHandle = LoadLibrary(dllLibName);
}

UI::~UI()
{
	if (left_dir)
		delete[] left_dir;
	if (right_dir)
		delete[] right_dir;

	if (serverThread)
		delete serverThread;
	if (clientData)
		delete clientData;

	if (dllHandle)
		FreeLibrary(dllHandle);

	WSACleanup();
}

void UI::ShowDirFiles(PANELS pID, QStringList *filesList)
{
	int driveInd;
	switch (pID)
	{
	case UI::leftP:
		driveInd = ui.driveleft_comboBox->currentIndex();
		if (ftpPanel == UI::inactiveP)
		{
			ShowFilesFromPanel(ui.left_tableWidget, &left_dir[driveInd]);
			ui.left_path_lineEdit->setText(left_dir[driveInd].path());
		}
		else if (ftpPanel == UI::leftP)
		{
			ShowFilesFromPanel(ui.left_tableWidget, 0, filesList);
			ui.left_path_lineEdit->setText(clientData->dir);
		}
		break;
	case UI::rightP:
		driveInd = ui.driveright_comboBox->currentIndex();
		if (ftpPanel == UI::inactiveP)
		{
			ShowFilesFromPanel(ui.right_tableWidget, &right_dir[driveInd]);
			ui.right_path_lineEdit->setText(right_dir[driveInd].path());
		}
		else if (ftpPanel == UI::rightP)
		{
			ShowFilesFromPanel(ui.right_tableWidget, 0, filesList);
			ui.right_path_lineEdit->setText(clientData->dir);
		}
		break;
	default:
		WriteLogMessage("Error in ShowDirFiles function");
	}
}

void UI::ShowFilesFromPanel(QTableWidget *panel, QDir *dir, QStringList *filesList)
{
	QStringList dirFiles;
	QStringList files;
	QFileIconProvider fp;
	QTableWidgetItem *item;
	int i = 0;
	if (dir == 0 && filesList != 0)  ///// FROM FTP
	{
		panel->clear();
		panel->setRowCount(filesList->count());
		for (i = 0; i < filesList->count(); i++)
		{
			if (filesList->at(i).size() == 0)
				continue;
			QStringList fileAttrib = filesList->at(i).split(":");
			if (fileAttrib.size() < 2)
				continue;
			item = new QTableWidgetItem(fileAttrib[1]);
			if (fileAttrib[0] == "0" || fileAttrib[0] == "1" || fileAttrib[0] == "2")
				item->setIcon(fp.icon(QFileIconProvider::Folder));
			else
				item->setIcon(fp.icon(QFileIconProvider::File));
			panel->setItem(i, 0, item);
			item = new QTableWidgetItem(fileAttrib[2]);
			panel->setItem(i, 1, item);
			panel->setRowHeight(i, 14);
		}
	}
	else if (dir->exists())
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
	panel->selectRow(0);
}

void UI::WriteLogMessage(const QString &message)
{
	QListWidgetItem *item = new QListWidgetItem(message);
	ui.log_listWidget->addItem(item);
	ui.log_listWidget->setCurrentItem(item);
}

void UI::changeDirFromFileSystem(QTableWidgetItem * item)
{
	QTableWidget *panel = item->tableWidget();
	QDir *panel_dir;
	PANELS pID;
	int driveInd;

	if (ftpPanel == GetPannelIDFromWidget(panel))
		ExecFTPCommand("dir " + panel->item(item->row(), 0)->text());
	else
	{
		if (panel == ui.left_tableWidget)
		{

			driveInd = ui.driveleft_comboBox->currentIndex();
			panel_dir = &left_dir[driveInd];
			pID = UI::leftP;
		}
		else
		{
			driveInd = ui.driveright_comboBox->currentIndex();
			panel_dir = &right_dir[driveInd];
			pID = UI::rightP;
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
}

void UI::ChangeLeftDrive(int index)
{
	ShowDirFiles(UI::leftP);
}

void UI::ChangeRightDrive(int index)
{
	ShowDirFiles(UI::rightP);
}

void UI::OpenServerOptions(bool checked)
{
	Server_Options_dialog options_dialog(&config_data, this);
	options_dialog.exec();
}

void UI::OpenClientOptions(bool checked)
{
	Client_Options_dialog options_dialog(&config_data, this);
	options_dialog.exec();
}

void UI::OpenViewerOptions(bool checked)
{
	Viewer_Options_dialog options_dialog(&config_data, this);
	options_dialog.exec();

}

void UI::SetWorkingLeftPanel(QTableWidgetItem *item)
{
	fromToPanel[0] = UI::leftP;
	fromToPanelWidget[0] = ui.left_tableWidget;
	fromToPanel[1] = UI::rightP;
	fromToPanelWidget[1] = ui.right_tableWidget;
	
	ui.right_tableWidget->clearSelection();
}

void UI::SetWorkingRightPanel(QTableWidgetItem *item)
{
	fromToPanel[0] = UI::rightP;
	fromToPanelWidget[0] = ui.right_tableWidget;
	fromToPanel[1] = UI::leftP;
	fromToPanelWidget[1] = ui.left_tableWidget;
	ui.left_tableWidget->clearSelection();
}

void UI::GetFromToDir(QDir *source, QDir *dest)
{
	if (fromToPanel[0] == UI::inactiveP)
		return;

	int leftPInd = ui.driveleft_comboBox->currentIndex();
	int rightPInd = ui.driveright_comboBox->currentIndex();
	if (fromToPanel[0] == UI::leftP)
	{
		*source = left_dir[leftPInd];
		*dest = right_dir[rightPInd];
	}
	else
	{
		*source = right_dir[rightPInd];
		*dest = left_dir[leftPInd];
	}
}

void UI::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_F4: // view
		if (ftpPanel != UI::inactiveP) /// one panel is FTP
			EditFTP();
		else
			EditClient();
		break;

	case Qt::Key_F5: // copy
		if (ftpPanel != UI::inactiveP) /// one panel is FTP
			CopyClientToFTP();
		else
			CopyClientToClient();
		break;
	default:
		break;
	}
}

void UI::EditClient()
{
	QString viewer;
	QTableWidget *selectPanel = 0;
	QDir dir_source, dir_dest;
	QFile file_source, file_dest;
	QString fname;
	QString selectedFile;
	qint64 buffsize;


	viewer = config_data.getDataValue("UsedViewer");
	if (viewer == "-")
		viewer = config_data.getDataValue("DefaultViewer");
	selectPanel = fromToPanelWidget[0];
	GetFromToDir(&dir_source, &dir_dest);
	fname = selectPanel->item(selectPanel->currentRow(), 0)->text();
	selectedFile = dir_source.absoluteFilePath(fname);
	QProcess::execute(viewer + " " + selectedFile);
	file_source.setFileName(selectedFile);
	buffsize = 0;
	if (file_source.open(QIODevice::ReadOnly))
	{
		buffsize = file_source.size();  //when file does open.
		file_source.close();
	}
	selectPanel->item(selectPanel->currentRow(), 1)->setText(QString::number(buffsize));
	if (dir_source.absolutePath() == dir_dest.absolutePath())
		fromToPanelWidget[1]->item(selectPanel->currentRow(), 1)->setText(QString::number(buffsize));
}

void UI::CopyClientToClient()
{
	QTableWidget *selectPanel = 0;
	QDir dir_source, dir_dest;
	QString fname;

	selectPanel = fromToPanelWidget[0];
	GetFromToDir(&dir_source, &dir_dest);
	fname = selectPanel->item(selectPanel->currentRow(), 0)->text();

	CopyProgress_dialog progress_dialog(this, dir_source.absoluteFilePath(fname), dir_dest.absoluteFilePath(fname), 2);
	if (progress_dialog.OpenFilesForCopy())
	{
		progress_dialog.exec();
		progress_dialog.CloseFiles();

		ShowDirFiles(fromToPanel[1]);
	}
}

void UI::EditFTP()
{}

void UI::CopyClientToFTP()
{}

void UI::StartFTPServer(bool checked)
{
	QIcon icon1, icon2;
	icon1.addFile(QString::fromUtf8(":/icons/icon/Home-Server-icon_off.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon2.addFile(QString::fromUtf8(":/icons/icon/Home-Server-icon_on.png"), QSize(), QIcon::Normal, QIcon::Off);

	if (!FTPServerRun)
	{
		QString strHomeDir = config_data.getDataValue("ServerHomeDir");
		QDir homeDir(strHomeDir);
		if (!homeDir.exists())
			config_data.setDataValue("ServerHomeDir", QDir::current().path());
		serverThread = new FTPServer(	this,
										config_data.getDataValue("ServerHomeDir"),
										config_data.getDataValue("ServerPort").toShort(),
										config_data.getDataValue("ServerBitrate").toLong());
		serverThread->start();
		ui.action_ToolServerStarted->setIcon(icon2);
	}
	else
	{
		if (serverThread)
			emit abortServer();

		ui.action_ToolServerStarted->setIcon(icon1);
	}

}

void UI::StartFTPClient(bool checked)
{
	QIcon icon1, icon2;
	icon1.addFile(QString::fromUtf8(":/icons/icon/right.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon2.addFile(QString::fromUtf8(":/icons/icon/forward_button.png"), QSize(), QIcon::Normal, QIcon::Off);

	if (!FTPClientRun)
	{
		FTP_Client_Start_dialog	client_start_dialog(this);
		if (client_start_dialog.exec() == true)
		{
			FTP_Client_Running();
			ui.action_ToolClientConnected->setIcon(icon1);
		}
		else
		{
			AbortClient();
			ui.action_ToolClientConnected->setIcon(icon2);
		}
	}
	else
	{
		AbortClient();
		ui.action_ToolClientConnected->setIcon(icon2);
	}
}

void UI::SetFTPServerStatus(bool status)
{
	FTPServerRun = status;
	if (!status)
	{
		if (serverThread)
		{
//			serverThread->terminate();
			delete serverThread;
			serverThread = 0;
		}
	}
}

UI_config *UI::getConfig()
{
	return &config_data; 
}

void UI::setFTPData(FTPClient *_clientData)
{
	clientData = _clientData; 
}

UI::PANELS UI::GetPannelIDFromWidget(QTableWidget *panel)
{
	if (panel == ui.left_tableWidget)
		return UI::leftP;
	else if (panel == ui.right_tableWidget)
		return UI::rightP;

	return UI::inactiveP;
}

HINSTANCE UI::GetDLLHandle()
{
	return dllHandle;
}