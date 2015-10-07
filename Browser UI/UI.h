#include "ui_mainwindow.h"
#include <QDir>
#include <QFileIconProvider>
#include "config.h"

class UI : public QMainWindow
{
    Q_OBJECT

public:
	UI(QWidget *parent = 0);
	~UI();

	void keyPressEvent(QKeyEvent * event);
	void WriteLogMessage(const QString message);

private:
	enum PANELS{leftP = 0, rightP = 1, inactiveP = 2};

	PANELS fromToPanel[2];
	QTableWidget *fromToPanelWidget[2];
	PANELS ftpPanel;
	QDir *left_dir;  /// array for drives
	QDir *right_dir; /// array for drives


	Ui::Client_Server_MainWindow ui;
	UI_config config_data;

	void ShowDirFiles(PANELS pID);
	void ShowFilesFromPanel(QTableWidget *panel, QDir *dir);
	void GetFromToDir(QDir *source, QDir *dest);

	void EditClient();
	void EditFTP();
	void CopyClientToClient();
	void CopyClientToFTP();

public slots:
	void changeDirFromFileSystem(QTableWidgetItem * item);
	void SetWorkingPanel(QTableWidgetItem * item);
	void ChangeLeftDrive(int index);
	void ChangeRightDrive(int index);

	void OpenServerOptions(bool checked = false);
	void OpenClientOptions(bool checked = false);
	void OpenViewerOptions(bool checked = false);
};