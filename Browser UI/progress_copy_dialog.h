#include "ui_copy.h"
#include <QFile>
#include <QThread>

class CopyProgress_dialog;

class ClientCopyThread : public QThread
{
	Q_OBJECT

private:
	QFile *source;
	QFile::Permissions *source_permissions;
	QFile *dest;
	CopyProgress_dialog *main_thread;
	qint64 bytesCopied;
	QTimer *timer;

public:
	ClientCopyThread(	CopyProgress_dialog *_main_thread,
						QFile *_file_source,
						QFile::Permissions *_source_permissions,
						QFile *_file_dest);
signals:
	void updateProgressBar(int size);
	void closeWindow();

private:
	void run();
};

class UI;

using namespace std;

class CopyProgress_dialog : public QDialog
{
	Q_OBJECT

private:
	QFile source;
	QFile::Permissions source_permissions;
	QFile dest;
	int FTPcopyType;

	UI *mainwnd;
	Ui::copyfile_Dialog ui;
	qint64 fileSize;
	qint64 bytesCopied;

public:
	CopyProgress_dialog(UI *_mainwnd, const QString &_filesource, const QString &_filedest, int _FTPcopyType);
	//  FTPcopyType =  0 - filesource is ftp, 1 - filedest if ftp, 2+ - none is ftp

	bool OpenFilesForCopy();
	void CloseFiles();

	void showEvent(QShowEvent *event);

public slots:
		void UpdateProgressBar(int size);

};