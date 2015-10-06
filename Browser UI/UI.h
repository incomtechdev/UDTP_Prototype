#include "ui_mainwindow.h"
#include <QDir>
#include <QFileIconProvider>

class UI : public QMainWindow
{
    Q_OBJECT

public:
	UI(QWidget *parent = 0);
	~UI();

private:
	enum PANELS{leftP = 0, rightP = 1};

	QTableWidget *currentPanel;
	QTableWidget *ftpPanel;
	QDir *left_dir;  /// array for drives
	QDir *right_dir; /// array for drives


	Ui::Client_Server_MainWindow ui;


	void ShowDirFiles(PANELS pID);
	void ShowFilesFromPanel(QTableWidget *panel, QDir *dir);
	void WriteLogMessage(const QString message);

public slots:
	void changeDirFromFileSystem(QTableWidgetItem * item);
	void ChangeLeftDrive(int index);
	void ChangeRightDrive(int index);
};