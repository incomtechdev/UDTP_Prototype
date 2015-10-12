/********************************************************************************
** Form generated from reading UI file 'FTP_client_connection.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FTP_CLIENT_CONNECTION_H
#define UI_FTP_CLIENT_CONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_FTP_connect_Dialog
{
public:
    QFrame *frame_2;
    QRadioButton *loginpass_radioButton;
    QRadioButton *authID_radioButton;
    QLabel *label_6;
    QLineEdit *authID_lineEdit;
    QLineEdit *login_lineEdit;
    QLineEdit *password_lineEdit;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *clientConnect_pushButton;
    QPushButton *cancel_pushButton;
    QFrame *frame;
    QLabel *label;
    QLineEdit *IP_lineEdit;
    QLabel *label_7;
    QLineEdit *port_lineEdit;

    void setupUi(QDialog *FTP_connect_Dialog)
    {
        if (FTP_connect_Dialog->objectName().isEmpty())
            FTP_connect_Dialog->setObjectName(QStringLiteral("FTP_connect_Dialog"));
        FTP_connect_Dialog->resize(423, 233);
        frame_2 = new QFrame(FTP_connect_Dialog);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 90, 291, 131));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        loginpass_radioButton = new QRadioButton(frame_2);
        loginpass_radioButton->setObjectName(QStringLiteral("loginpass_radioButton"));
        loginpass_radioButton->setGeometry(QRect(20, 10, 121, 18));
        authID_radioButton = new QRadioButton(frame_2);
        authID_radioButton->setObjectName(QStringLiteral("authID_radioButton"));
        authID_radioButton->setGeometry(QRect(160, 10, 121, 18));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 100, 61, 21));
        authID_lineEdit = new QLineEdit(frame_2);
        authID_lineEdit->setObjectName(QStringLiteral("authID_lineEdit"));
        authID_lineEdit->setGeometry(QRect(70, 100, 201, 21));
        login_lineEdit = new QLineEdit(frame_2);
        login_lineEdit->setObjectName(QStringLiteral("login_lineEdit"));
        login_lineEdit->setGeometry(QRect(70, 40, 201, 20));
        password_lineEdit = new QLineEdit(frame_2);
        password_lineEdit->setObjectName(QStringLiteral("password_lineEdit"));
        password_lineEdit->setGeometry(QRect(70, 70, 201, 20));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 40, 46, 21));
        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 70, 51, 21));
        clientConnect_pushButton = new QPushButton(FTP_connect_Dialog);
        clientConnect_pushButton->setObjectName(QStringLiteral("clientConnect_pushButton"));
        clientConnect_pushButton->setGeometry(QRect(320, 10, 91, 31));
        cancel_pushButton = new QPushButton(FTP_connect_Dialog);
        cancel_pushButton->setObjectName(QStringLiteral("cancel_pushButton"));
        cancel_pushButton->setGeometry(QRect(320, 50, 91, 31));
        frame = new QFrame(FTP_connect_Dialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 291, 71));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 51, 21));
        IP_lineEdit = new QLineEdit(frame);
        IP_lineEdit->setObjectName(QStringLiteral("IP_lineEdit"));
        IP_lineEdit->setGeometry(QRect(70, 10, 201, 21));
        label_7 = new QLabel(frame);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 40, 31, 21));
        port_lineEdit = new QLineEdit(frame);
        port_lineEdit->setObjectName(QStringLiteral("port_lineEdit"));
        port_lineEdit->setGeometry(QRect(70, 40, 201, 20));

        retranslateUi(FTP_connect_Dialog);

        QMetaObject::connectSlotsByName(FTP_connect_Dialog);
    } // setupUi

    void retranslateUi(QDialog *FTP_connect_Dialog)
    {
        FTP_connect_Dialog->setWindowTitle(QApplication::translate("FTP_connect_Dialog", "FTP Connection", 0));
        loginpass_radioButton->setText(QApplication::translate("FTP_connect_Dialog", "Login/Password used", 0));
        authID_radioButton->setText(QApplication::translate("FTP_connect_Dialog", "Authendificator used", 0));
        label_6->setText(QApplication::translate("FTP_connect_Dialog", "Auth ID", 0));
        label_3->setText(QApplication::translate("FTP_connect_Dialog", "Login", 0));
        label_4->setText(QApplication::translate("FTP_connect_Dialog", "Password", 0));
        clientConnect_pushButton->setText(QApplication::translate("FTP_connect_Dialog", "Connect", 0));
        cancel_pushButton->setText(QApplication::translate("FTP_connect_Dialog", "Cancel", 0));
        label->setText(QApplication::translate("FTP_connect_Dialog", "Server IP", 0));
        IP_lineEdit->setText(QApplication::translate("FTP_connect_Dialog", "127.0.0.1", 0));
        label_7->setText(QApplication::translate("FTP_connect_Dialog", "Port", 0));
        port_lineEdit->setText(QApplication::translate("FTP_connect_Dialog", "1234", 0));
    } // retranslateUi

};

namespace Ui {
    class FTP_connect_Dialog: public Ui_FTP_connect_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FTP_CLIENT_CONNECTION_H
