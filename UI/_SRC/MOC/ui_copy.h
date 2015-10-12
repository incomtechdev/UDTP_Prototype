/********************************************************************************
** Form generated from reading UI file 'copy.ui'
**
** Created: Thu 8. Oct 15:06:42 2015
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPY_H
#define UI_COPY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_copyfile_Dialog
{
public:
    QProgressBar *copy_progressBar;
    QLabel *label;
    QLabel *label_2;
    QLabel *source_label;
    QLabel *dest_label;

    void setupUi(QDialog *copyfile_Dialog)
    {
        if (copyfile_Dialog->objectName().isEmpty())
            copyfile_Dialog->setObjectName(QString::fromUtf8("copyfile_Dialog"));
        copyfile_Dialog->resize(347, 125);
        copyfile_Dialog->setModal(false);
        copy_progressBar = new QProgressBar(copyfile_Dialog);
        copy_progressBar->setObjectName(QString::fromUtf8("copy_progressBar"));
        copy_progressBar->setGeometry(QRect(20, 80, 311, 23));
        copy_progressBar->setValue(24);
        label = new QLabel(copyfile_Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 46, 21));
        label_2 = new QLabel(copyfile_Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 40, 61, 21));
        source_label = new QLabel(copyfile_Dialog);
        source_label->setObjectName(QString::fromUtf8("source_label"));
        source_label->setGeometry(QRect(90, 10, 221, 21));
        dest_label = new QLabel(copyfile_Dialog);
        dest_label->setObjectName(QString::fromUtf8("dest_label"));
        dest_label->setGeometry(QRect(90, 40, 221, 21));

        retranslateUi(copyfile_Dialog);

        QMetaObject::connectSlotsByName(copyfile_Dialog);
    } // setupUi

    void retranslateUi(QDialog *copyfile_Dialog)
    {
        copyfile_Dialog->setWindowTitle(QApplication::translate("copyfile_Dialog", "Copy...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("copyfile_Dialog", "Source", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("copyfile_Dialog", "Destination", 0, QApplication::UnicodeUTF8));
        source_label->setText(QApplication::translate("copyfile_Dialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        dest_label->setText(QApplication::translate("copyfile_Dialog", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class copyfile_Dialog: public Ui_copyfile_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPY_H
