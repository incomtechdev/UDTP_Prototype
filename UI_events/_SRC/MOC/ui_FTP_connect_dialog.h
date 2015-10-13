/********************************************************************************
** Form generated from reading UI file 'FTP_connect_dialog.ui'
**
** Created: Tue 13. Oct 10:55:18 2015
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FTP_CONNECT_DIALOG_H
#define UI_FTP_CONNECT_DIALOG_H

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
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_FTP_connect_Dialog
{
public:
    QFrame *frame;
    QLabel *label;
    QLineEdit *IP_lineEdit;
    QLabel *label_7;
    QLineEdit *port_lineEdit;
    QFrame *frame_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QLabel *label_6;
    QLineEdit *authID_lineEdit;
    QLineEdit *login_lineEdit;
    QLineEdit *password_lineEdit;
    QLabel *label_3;
    QLabel *label_4;
    QFrame *btr_frame;
    QLabel *label_2;
    QLineEdit *bitrate_lineEdit;
    QCheckBox *checkBox;

    void setupUi(QDialog *FTP_connect_Dialog)
    {
        if (FTP_connect_Dialog->objectName().isEmpty())
            FTP_connect_Dialog->setObjectName(QString::fromUtf8("FTP_connect_Dialog"));
        FTP_connect_Dialog->resize(332, 328);
        frame = new QFrame(FTP_connect_Dialog);
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
        frame_2 = new QFrame(FTP_connect_Dialog);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(30, 100, 291, 131));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        radioButton = new QRadioButton(frame_2);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(20, 10, 121, 18));
        radioButton_2 = new QRadioButton(frame_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(160, 10, 121, 18));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 100, 61, 21));
        authID_lineEdit = new QLineEdit(frame_2);
        authID_lineEdit->setObjectName(QString::fromUtf8("authID_lineEdit"));
        authID_lineEdit->setGeometry(QRect(70, 100, 201, 21));
        login_lineEdit = new QLineEdit(frame_2);
        login_lineEdit->setObjectName(QString::fromUtf8("login_lineEdit"));
        login_lineEdit->setGeometry(QRect(70, 40, 201, 20));
        password_lineEdit = new QLineEdit(frame_2);
        password_lineEdit->setObjectName(QString::fromUtf8("password_lineEdit"));
        password_lineEdit->setGeometry(QRect(70, 70, 201, 20));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 40, 46, 21));
        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 70, 51, 21));
        btr_frame = new QFrame(FTP_connect_Dialog);
        btr_frame->setObjectName(QString::fromUtf8("btr_frame"));
        btr_frame->setGeometry(QRect(29, 240, 291, 80));
        btr_frame->setFrameShape(QFrame::Box);
        btr_frame->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(btr_frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 50, 46, 20));
        bitrate_lineEdit = new QLineEdit(btr_frame);
        bitrate_lineEdit->setObjectName(QString::fromUtf8("bitrate_lineEdit"));
        bitrate_lineEdit->setGeometry(QRect(70, 50, 201, 20));
        checkBox = new QCheckBox(btr_frame);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(70, 10, 181, 21));

        retranslateUi(FTP_connect_Dialog);

        QMetaObject::connectSlotsByName(FTP_connect_Dialog);
    } // setupUi

    void retranslateUi(QDialog *FTP_connect_Dialog)
    {
        FTP_connect_Dialog->setWindowTitle(QApplication::translate("FTP_connect_Dialog", "FTP Connection", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FTP_connect_Dialog", "Server IP", 0, QApplication::UnicodeUTF8));
        IP_lineEdit->setText(QApplication::translate("FTP_connect_Dialog", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FTP_connect_Dialog", "Port", 0, QApplication::UnicodeUTF8));
        port_lineEdit->setText(QApplication::translate("FTP_connect_Dialog", "1234", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("FTP_connect_Dialog", "Login/Password used", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("FTP_connect_Dialog", "Authendificator used", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FTP_connect_Dialog", "Auth ID", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FTP_connect_Dialog", "Login", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FTP_connect_Dialog", "Password", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FTP_connect_Dialog", "Bitrate", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("FTP_connect_Dialog", "Use realtime data transfer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FTP_connect_Dialog: public Ui_FTP_connect_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FTP_CONNECT_DIALOG_H
