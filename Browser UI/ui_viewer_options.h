/********************************************************************************
** Form generated from reading UI file 'viewer_options.ui'
**
** Created: Tue 6. Oct 18:28:45 2015
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWER_OPTIONS_H
#define UI_VIEWER_OPTIONS_H

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

QT_BEGIN_NAMESPACE

class Ui_Viewer_Options_Dialog
{
public:
    QPushButton *RESET_pushButton;
    QPushButton *OK_pushButton;
    QPushButton *CANCEL_pushButton;
    QFrame *frame;
    QLabel *label;
    QLineEdit *defaultEditor_lineEdit;
    QLabel *label_2;
    QLineEdit *userdefinedEditor_lineEdit;
    QPushButton *browse_uderdefinedEditor_pushButton;
    QPushButton *browse_defaultEditor_pushButton;

    void setupUi(QDialog *Viewer_Options_Dialog)
    {
        if (Viewer_Options_Dialog->objectName().isEmpty())
            Viewer_Options_Dialog->setObjectName(QString::fromUtf8("Viewer_Options_Dialog"));
        Viewer_Options_Dialog->resize(328, 179);
        RESET_pushButton = new QPushButton(Viewer_Options_Dialog);
        RESET_pushButton->setObjectName(QString::fromUtf8("RESET_pushButton"));
        RESET_pushButton->setGeometry(QRect(210, 130, 101, 31));
        OK_pushButton = new QPushButton(Viewer_Options_Dialog);
        OK_pushButton->setObjectName(QString::fromUtf8("OK_pushButton"));
        OK_pushButton->setGeometry(QRect(10, 130, 75, 31));
        CANCEL_pushButton = new QPushButton(Viewer_Options_Dialog);
        CANCEL_pushButton->setObjectName(QString::fromUtf8("CANCEL_pushButton"));
        CANCEL_pushButton->setGeometry(QRect(110, 130, 75, 31));
        frame = new QFrame(Viewer_Options_Dialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 311, 111));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 91, 16));
        defaultEditor_lineEdit = new QLineEdit(frame);
        defaultEditor_lineEdit->setObjectName(QString::fromUtf8("defaultEditor_lineEdit"));
        defaultEditor_lineEdit->setGeometry(QRect(10, 30, 241, 20));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 60, 121, 16));
        userdefinedEditor_lineEdit = new QLineEdit(frame);
        userdefinedEditor_lineEdit->setObjectName(QString::fromUtf8("userdefinedEditor_lineEdit"));
        userdefinedEditor_lineEdit->setGeometry(QRect(10, 80, 241, 20));
        browse_uderdefinedEditor_pushButton = new QPushButton(frame);
        browse_uderdefinedEditor_pushButton->setObjectName(QString::fromUtf8("browse_uderdefinedEditor_pushButton"));
        browse_uderdefinedEditor_pushButton->setGeometry(QRect(260, 80, 40, 25));
        browse_uderdefinedEditor_pushButton->setMinimumSize(QSize(40, 25));
        browse_uderdefinedEditor_pushButton->setMaximumSize(QSize(40, 25));
        browse_defaultEditor_pushButton = new QPushButton(frame);
        browse_defaultEditor_pushButton->setObjectName(QString::fromUtf8("browse_defaultEditor_pushButton"));
        browse_defaultEditor_pushButton->setGeometry(QRect(260, 30, 40, 25));
        browse_defaultEditor_pushButton->setMinimumSize(QSize(40, 25));
        browse_defaultEditor_pushButton->setMaximumSize(QSize(40, 25));

        retranslateUi(Viewer_Options_Dialog);

        QMetaObject::connectSlotsByName(Viewer_Options_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Viewer_Options_Dialog)
    {
        Viewer_Options_Dialog->setWindowTitle(QApplication::translate("Viewer_Options_Dialog", "Viewer Options", 0, QApplication::UnicodeUTF8));
        RESET_pushButton->setText(QApplication::translate("Viewer_Options_Dialog", "Reset to defaults", 0, QApplication::UnicodeUTF8));
        OK_pushButton->setText(QApplication::translate("Viewer_Options_Dialog", "Ok", 0, QApplication::UnicodeUTF8));
        CANCEL_pushButton->setText(QApplication::translate("Viewer_Options_Dialog", "Cancel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Viewer_Options_Dialog", "Default Editor", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Viewer_Options_Dialog", "Used Editor", 0, QApplication::UnicodeUTF8));
        browse_uderdefinedEditor_pushButton->setText(QApplication::translate("Viewer_Options_Dialog", "...", 0, QApplication::UnicodeUTF8));
        browse_defaultEditor_pushButton->setText(QApplication::translate("Viewer_Options_Dialog", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Viewer_Options_Dialog: public Ui_Viewer_Options_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWER_OPTIONS_H
