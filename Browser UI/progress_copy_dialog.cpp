#include "UI.h"
#include "progress_copy_dialog.h"
#include "windows.h"
#include <QTimer>

using namespace std;

ClientCopyThread::ClientCopyThread(	CopyProgress_dialog *_main_thread,
									QFile *_file_source,
									QFile::Permissions *_source_permissions,
									QFile *_file_dest):
									main_thread(_main_thread),
									source_permissions(_source_permissions),
									source(_file_source),
									dest(_file_dest),
									bytesCopied(0)
{
	connect(this, SIGNAL(updateProgressBar(int)), main_thread, SLOT(UpdateProgressBar(int)));
	connect(this, SIGNAL(closeWindow()), main_thread, SLOT(close()));

//	timer = new QTimer(this);
//	timer->setInterval(1000);
//	connect(timer, SIGNAL(timeout()), main_thread, SLOT(UpdateProgressBar(int)));
//	timer->start();
}

void ClientCopyThread::run()
{
	const int COPY_BUFFER = 1000;
	bytesCopied = 0;
	char copyData[COPY_BUFFER];
	qint64 buffsize;

	while (!source->atEnd())
	{
		buffsize = source->read(copyData, COPY_BUFFER);
		bytesCopied += buffsize;
		dest->write(copyData, buffsize);
		emit updateProgressBar(bytesCopied);
	}

//	timer->stop();
	emit closeWindow();
}

CopyProgress_dialog::CopyProgress_dialog(	UI *_mainwnd,
											const QString &_filesource,
											const QString &_filedest,
											int _FTPcopyType) :
											QDialog(_mainwnd),
											source(_filesource),
											dest(_filedest),
											mainwnd(_mainwnd),
											bytesCopied(0),
											fileSize(0),
											FTPcopyType(_FTPcopyType)
{
	ui.setupUi(this);
	ui.source_label->setText(_filesource);
	ui.dest_label->setText(_filedest);
	ui.copy_progressBar->reset();
}

bool CopyProgress_dialog::OpenFilesForCopy()
{
	if (FTPcopyType > 1)
	{
		if (!source.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			mainwnd->WriteLogMessage("Can't open file " + source.fileName() + " for read. Copy aborted");
			return false;
		}

		fileSize = source.size();
		source_permissions = source.permissions();
		ui.copy_progressBar->setRange(0, fileSize);

		source.setPermissions(QFile::ReadOwner | QFile::ReadGroup | QFile::ReadOther);

		if (!dest.open(QIODevice::Truncate | QIODevice::Append | QIODevice::Text))
		{
			mainwnd->WriteLogMessage("Can't open file " + source.fileName() + " for write. Copy aborted");
			source.setPermissions(source_permissions);
			source.close();
			return false;
		}
	}
	else
	{


	}
	
	return true;
}

void CopyProgress_dialog::CloseFiles()
{
	if (FTPcopyType > 1)
	{
		if (source.isOpen())
		{
			source.setPermissions(source_permissions);
			source.close();
		}
		if (dest.isOpen())
			dest.close();
	}
	else
	{
		
	}

}

void CopyProgress_dialog::UpdateProgressBar(int size)
{
	ui.copy_progressBar->setValue(size);
}

void CopyProgress_dialog::showEvent(QShowEvent *event)
{
	if (FTPcopyType > 1)
	{
		ClientCopyThread *t = new ClientCopyThread(this, &source, &source_permissions, &dest);
		t->start();
	}

	else   ///// FTP COPY
	{

	}
}

/*
void CopyProgress_dialog::closeEvent(QCloseEvent * event)
{

}
*/