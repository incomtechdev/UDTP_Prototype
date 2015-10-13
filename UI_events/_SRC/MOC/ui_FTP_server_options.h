/********************************************************************************
** Form generated from reading UI file 'FTP_server_options.ui'
**
** Created: Tue 13. Oct 10:55:18 2015
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FTP_SERVER_OPTIONS_H
#define UI_FTP_SERVER_OPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FTP_serverOptions_Dialog
{
public:
    QFrame *frame;
    QLabel *label_7;
    QLineEdit *port_lineEdit;
    QLabel *label;
    QLineEdit *homeDir_lineEdit;
    QPushButton *homeDirBrowse_pushButton;
    QFrame *btr_frame;
    QLabel *label_2;
    QLineEdit *bitrate_lineEdit;
    QCheckBox *usebitrate_checkBox;

    void setupUi(QDialog *FTP_serverOptions_Dialog)
    {
        if (FTP_serverOptions_Dialog->objectName().isEmpty())
            FTP_serverOptions_Dialog->setObjectName(QString::fromUtf8("FTP_serverOptions_Dialog"));
        FTP_serverOptions_Dialog->resize(312, 196);
        frame = new QFrame(FTP_serverOptions_Dialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 291, 81));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 10, 81, 21));
        port_lineEdit = new QLineEdit(frame);
        port_lineEdit->setObjectName(QString::fromUtf8("port_lineEdit"));
        port_lineEdit->setGeometry(QRect(100, 10, 141, 20));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 52, 71, 21));
        homeDir_lineEdit = new QLineEdit(frame);
        homeDir_lineEdit->setObjectName(QString::fromUtf8("homeDir_lineEdit"));
        homeDir_lineEdit->setGeometry(QRect(100, 50, 141, 20));
        homeDirBrowse_pushButton = new QPushButton(frame);
        homeDirBrowse_pushButton->setObjectName(QString::fromUtf8("homeDirBrowse_pushButton"));
        homeDirBrowse_pushButton->setGeometry(QRect(250, 50, 31, 23));
        btr_frame = new QFrame(FTP_serverOptions_Dialog);
        btr_frame->setObjectName(QString::fromUtf8("btr_frame"));
        btr_frame->setGeometry(QRect(10, 100, 291, 80));
        btr_frame->setFrameShape(QFrame::Box);
        btr_frame->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(btr_frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 50, 61, 20));
        bitrate_lineEdit = new QLineEdit(btr_frame);
        bitrate_lineEdit->setObjectName(QString::fromUtf8("bitrate_lineEdit"));
        bitrate_lineEdit->setGeometry(QRect(100, 50, 141, 20));
        usebitrate_checkBox = new QCheckBox(btr_frame);
        usebitrate_checkBox->setObjectName(QString::fromUtf8("usebitrate_checkBox"));
        usebitrate_checkBox->setGeometry(QRect(100, 10, 161, 21));

        retranslateUi(FTP_serverOptions_Dialog);

        QMetaObject::connectSlotsByName(FTP_serverOptions_Dialog);
    } // setupUi

    void retranslateUi(QDialog *FTP_serverOptions_Dialog)
    {
        FTP_serverOptions_Dialog->setWindowTitle(QApplication::translate("FTP_serverOptions_Dialog", "Server Options", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FTP_serverOptions_Dialog", "Server Port", 0, QApplication::UnicodeUTF8));
        port_lineEdit->setText(QApplication::translate("FTP_serverOptions_Dialog", "1234", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FTP_serverOptions_Dialog", "Home Dir", 0, QApplication::UnicodeUTF8));
        homeDirBrowse_pushButton->setText(QApplication::translate("FTP_serverOptions_Dialog", "...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FTP_serverOptions_Dialog", "Max Bitrate", 0, QApplication::UnicodeUTF8));
        usebitrate_checkBox->setText(QApplication::translate("FTP_serverOptions_Dialog", "Use realtime data transfer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FTP_serverOptions_Dialog: public Ui_FTP_serverOptions_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FTP_SERVER_OPTIONS_H
