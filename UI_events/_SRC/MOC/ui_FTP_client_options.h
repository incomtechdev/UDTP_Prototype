/********************************************************************************
** Form generated from reading UI file 'FTP_client_options.ui'
**
** Created: Tue 13. Oct 10:55:18 2015
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FTP_CLIENT_OPTIONS_H
#define UI_FTP_CLIENT_OPTIONS_H

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

QT_BEGIN_NAMESPACE

class Ui_FTP_clientOptions_Dialog
{
public:
    QFrame *frame;
    QLabel *label;
    QLineEdit *IP_lineEdit;
    QLabel *label_7;
    QLineEdit *port_lineEdit;
    QFrame *btr_frame;
    QLabel *label_2;
    QLineEdit *bitrate_lineEdit;
    QCheckBox *userbitrate_checkBox;

    void setupUi(QDialog *FTP_clientOptions_Dialog)
    {
        if (FTP_clientOptions_Dialog->objectName().isEmpty())
            FTP_clientOptions_Dialog->setObjectName(QString::fromUtf8("FTP_clientOptions_Dialog"));
        FTP_clientOptions_Dialog->resize(332, 194);
        frame = new QFrame(FTP_clientOptions_Dialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(30, 20, 291, 71));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 51, 21));
        IP_lineEdit = new QLineEdit(frame);
        IP_lineEdit->setObjectName(QString::fromUtf8("IP_lineEdit"));
        IP_lineEdit->setGeometry(QRect(70, 10, 201, 21));
        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 40, 31, 21));
        port_lineEdit = new QLineEdit(frame);
        port_lineEdit->setObjectName(QString::fromUtf8("port_lineEdit"));
        port_lineEdit->setGeometry(QRect(70, 40, 201, 20));
        btr_frame = new QFrame(FTP_clientOptions_Dialog);
        btr_frame->setObjectName(QString::fromUtf8("btr_frame"));
        btr_frame->setGeometry(QRect(30, 100, 291, 80));
        btr_frame->setFrameShape(QFrame::Box);
        btr_frame->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(btr_frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 50, 46, 20));
        bitrate_lineEdit = new QLineEdit(btr_frame);
        bitrate_lineEdit->setObjectName(QString::fromUtf8("bitrate_lineEdit"));
        bitrate_lineEdit->setGeometry(QRect(70, 50, 201, 20));
        userbitrate_checkBox = new QCheckBox(btr_frame);
        userbitrate_checkBox->setObjectName(QString::fromUtf8("userbitrate_checkBox"));
        userbitrate_checkBox->setGeometry(QRect(70, 10, 181, 21));

        retranslateUi(FTP_clientOptions_Dialog);

        QMetaObject::connectSlotsByName(FTP_clientOptions_Dialog);
    } // setupUi

    void retranslateUi(QDialog *FTP_clientOptions_Dialog)
    {
        FTP_clientOptions_Dialog->setWindowTitle(QApplication::translate("FTP_clientOptions_Dialog", "FTP Client Options", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FTP_clientOptions_Dialog", "Server IP", 0, QApplication::UnicodeUTF8));
        IP_lineEdit->setText(QApplication::translate("FTP_clientOptions_Dialog", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FTP_clientOptions_Dialog", "Port", 0, QApplication::UnicodeUTF8));
        port_lineEdit->setText(QApplication::translate("FTP_clientOptions_Dialog", "1234", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FTP_clientOptions_Dialog", "Bitrate", 0, QApplication::UnicodeUTF8));
        userbitrate_checkBox->setText(QApplication::translate("FTP_clientOptions_Dialog", "Use realtime data transfer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FTP_clientOptions_Dialog: public Ui_FTP_clientOptions_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FTP_CLIENT_OPTIONS_H
