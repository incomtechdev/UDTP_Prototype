/********************************************************************************
** Form generated from reading UI file 'FTP_client_connection.ui'
**
** Created: Thu 8. Oct 15:06:42 2015
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FTP_CLIENT_CONNECTION_H
#define UI_FTP_CLIENT_CONNECTION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_FTP_connect_Dialog
{
public:
    QFrame *frame_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QLabel *label_6;
    QLineEdit *authID_lineEdit;
    QLineEdit *login_lineEdit;
    QLineEdit *password_lineEdit;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *clientConnect_pushButton;
    QPushButton *cancel_pushButton;

    void setupUi(QDialog *FTP_connect_Dialog)
    {
        if (FTP_connect_Dialog->objectName().isEmpty())
            FTP_connect_Dialog->setObjectName(QString::fromUtf8("FTP_connect_Dialog"));
        FTP_connect_Dialog->resize(425, 152);
        frame_2 = new QFrame(FTP_connect_Dialog);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(10, 10, 291, 131));
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
        clientConnect_pushButton = new QPushButton(FTP_connect_Dialog);
        clientConnect_pushButton->setObjectName(QString::fromUtf8("clientConnect_pushButton"));
        clientConnect_pushButton->setGeometry(QRect(320, 10, 91, 31));
        cancel_pushButton = new QPushButton(FTP_connect_Dialog);
        cancel_pushButton->setObjectName(QString::fromUtf8("cancel_pushButton"));
        cancel_pushButton->setGeometry(QRect(320, 50, 91, 31));

        retranslateUi(FTP_connect_Dialog);

        QMetaObject::connectSlotsByName(FTP_connect_Dialog);
    } // setupUi

    void retranslateUi(QDialog *FTP_connect_Dialog)
    {
        FTP_connect_Dialog->setWindowTitle(QApplication::translate("FTP_connect_Dialog", "FTP Connection", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("FTP_connect_Dialog", "Login/Password used", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("FTP_connect_Dialog", "Authendificator used", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FTP_connect_Dialog", "Auth ID", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FTP_connect_Dialog", "Login", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FTP_connect_Dialog", "Password", 0, QApplication::UnicodeUTF8));
        clientConnect_pushButton->setText(QApplication::translate("FTP_connect_Dialog", "Connect", 0, QApplication::UnicodeUTF8));
        cancel_pushButton->setText(QApplication::translate("FTP_connect_Dialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FTP_connect_Dialog: public Ui_FTP_connect_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FTP_CLIENT_CONNECTION_H
