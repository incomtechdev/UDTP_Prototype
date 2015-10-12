#ifndef _UI_
#define _UI_

#include "ui_mainwindow.h"
#include <QDir>
#include <QFileIconProvider>
#include "config.h"

class FTPServer;
class FTPClient;

class UI : public QMainWindow
{
    Q_OBJECT

public:
	UI(QWidget *parent = 0);
	~UI();

	void keyPressEvent(QKeyEvent * event);
	UI_config *getConfig();
	void setFTPData(FTPClient *_clientData);

private:
	enum PANELS{leftP = 0, rightP = 1, inactiveP = 2};

	PANELS fromToPanel[2];
	PANELS ftpPanel;

	QTableWidget *fromToPanelWidget[2];
	QDir *left_dir;  /// array for drives
	QDir *right_dir; /// array for drives

	FTPServer *serverThread;
	FTPClient *clientData;
	bool FTPServerRun;
	bool FTPClientRun;

	Ui::Client_Server_MainWindow ui;
	UI_config config_data;

	void ShowDirFiles(PANELS pID, QStringList *filesList = 0);
	void ShowFilesFromPanel(QTableWidget *panel, QDir *dir, QStringList *filesList = 0);
	void GetFromToDir(QDir *source, QDir *dest);

	void EditClient();
	void EditFTP();
	void CopyClientToClient();
	void CopyClientToFTP();

	void FTP_Client_Running();
	void AbortClient();

	int ExecFTPCommand(const QString &command);

public slots:
	void SetFTPServerStatus(bool status);
	void WriteLogMessage(const QString &message);
	void changeDirFromFileSystem(QTableWidgetItem * item);
	void SetWorkingPanel(QTableWidgetItem * item);
	void ChangeLeftDrive(int index);
	void ChangeRightDrive(int index);

	void StartFTPServer(bool checked = false);
	void StartFTPClient(bool checked = false); 
	void OpenServerOptions(bool checked = false);
	void OpenClientOptions(bool checked = false);
	void OpenViewerOptions(bool checked = false);

signals:
	void abortServer();
};

#endif