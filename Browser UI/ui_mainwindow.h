/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue 6. Oct 18:28:45 2015
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client_Server_MainWindow
{
public:
    QAction *action_MenuServerStarted;
    QAction *action_MenuServerOptions;
    QAction *action_MenuClientConnected;
    QAction *action_MenuClientOptions;
    QAction *action_ToolServerStarted;
    QAction *action_ToolClientConnected;
    QAction *action_ViewOptions;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *frame;
    QFrame *frame_2;
    QFrame *frame_3;
    QFrame *frame_4;
    QFrame *frame_5;
    QLabel *label_4;
    QFrame *frame_6;
    QLabel *label_3;
    QFrame *frame_7;
    QFrame *right_frame;
    QVBoxLayout *verticalLayout_2;
    QComboBox *driveright_comboBox;
    QLineEdit *right_path_lineEdit;
    QTableWidget *right_tableWidget;
    QFrame *left_frame;
    QVBoxLayout *verticalLayout;
    QComboBox *driveleft_comboBox;
    QLineEdit *left_path_lineEdit;
    QTableWidget *left_tableWidget;
    QLabel *label;
    QListWidget *log_listWidget;
    QMenuBar *menubar;
    QMenu *menuFTP_Server;
    QMenu *menuFTP_Client;
    QMenu *menuOptions;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *Client_Server_MainWindow)
    {
        if (Client_Server_MainWindow->objectName().isEmpty())
            Client_Server_MainWindow->setObjectName(QString::fromUtf8("Client_Server_MainWindow"));
        Client_Server_MainWindow->resize(638, 771);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icon/Home-Server-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        Client_Server_MainWindow->setWindowIcon(icon);
        action_MenuServerStarted = new QAction(Client_Server_MainWindow);
        action_MenuServerStarted->setObjectName(QString::fromUtf8("action_MenuServerStarted"));
        action_MenuServerOptions = new QAction(Client_Server_MainWindow);
        action_MenuServerOptions->setObjectName(QString::fromUtf8("action_MenuServerOptions"));
        action_MenuClientConnected = new QAction(Client_Server_MainWindow);
        action_MenuClientConnected->setObjectName(QString::fromUtf8("action_MenuClientConnected"));
        action_MenuClientOptions = new QAction(Client_Server_MainWindow);
        action_MenuClientOptions->setObjectName(QString::fromUtf8("action_MenuClientOptions"));
        action_ToolServerStarted = new QAction(Client_Server_MainWindow);
        action_ToolServerStarted->setObjectName(QString::fromUtf8("action_ToolServerStarted"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icon/Home-Server-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_ToolServerStarted->setIcon(icon1);
        action_ToolClientConnected = new QAction(Client_Server_MainWindow);
        action_ToolClientConnected->setObjectName(QString::fromUtf8("action_ToolClientConnected"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icon/right.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_ToolClientConnected->setIcon(icon2);
        action_ViewOptions = new QAction(Client_Server_MainWindow);
        action_ViewOptions->setObjectName(QString::fromUtf8("action_ViewOptions"));
        centralwidget = new QWidget(Client_Server_MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 25));
        frame->setMaximumSize(QSize(16777215, 25));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(0, 0, 100, 25));
        frame_2->setMinimumSize(QSize(100, 25));
        frame_2->setMaximumSize(QSize(100, 25));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(100, 0, 100, 25));
        frame_3->setMinimumSize(QSize(100, 25));
        frame_3->setMaximumSize(QSize(100, 25));
        frame_3->setFrameShape(QFrame::Box);
        frame_3->setFrameShadow(QFrame::Raised);
        frame_4 = new QFrame(frame);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(200, 0, 100, 25));
        frame_4->setMinimumSize(QSize(100, 25));
        frame_4->setMaximumSize(QSize(100, 25));
        frame_4->setFrameShape(QFrame::Box);
        frame_4->setFrameShadow(QFrame::Raised);
        frame_5 = new QFrame(frame);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(300, 0, 100, 25));
        frame_5->setMinimumSize(QSize(100, 25));
        frame_5->setMaximumSize(QSize(100, 25));
        frame_5->setFrameShape(QFrame::Box);
        frame_5->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(frame_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 1, 101, 21));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);
        frame_6 = new QFrame(frame);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setGeometry(QRect(400, 0, 100, 25));
        frame_6->setMinimumSize(QSize(100, 25));
        frame_6->setMaximumSize(QSize(100, 25));
        frame_6->setFrameShape(QFrame::Box);
        frame_6->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(frame_6);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 1, 101, 20));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        frame_7 = new QFrame(frame);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setGeometry(QRect(500, 0, 100, 25));
        frame_7->setMinimumSize(QSize(100, 25));
        frame_7->setMaximumSize(QSize(100, 25));
        frame_7->setFrameShape(QFrame::Box);
        frame_7->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frame, 3, 0, 1, 2);

        right_frame = new QFrame(centralwidget);
        right_frame->setObjectName(QString::fromUtf8("right_frame"));
        right_frame->setFrameShape(QFrame::Box);
        right_frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(right_frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        driveright_comboBox = new QComboBox(right_frame);
        driveright_comboBox->setObjectName(QString::fromUtf8("driveright_comboBox"));
        driveright_comboBox->setMaximumSize(QSize(60, 16777215));

        verticalLayout_2->addWidget(driveright_comboBox);

        right_path_lineEdit = new QLineEdit(right_frame);
        right_path_lineEdit->setObjectName(QString::fromUtf8("right_path_lineEdit"));
        right_path_lineEdit->setAutoFillBackground(false);
        right_path_lineEdit->setFrame(false);
        right_path_lineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(right_path_lineEdit);

        right_tableWidget = new QTableWidget(right_frame);
        if (right_tableWidget->columnCount() < 3)
            right_tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        right_tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        right_tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (right_tableWidget->rowCount() < 2)
            right_tableWidget->setRowCount(2);
        right_tableWidget->setObjectName(QString::fromUtf8("right_tableWidget"));
        right_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        right_tableWidget->setShowGrid(false);
        right_tableWidget->setSortingEnabled(true);
        right_tableWidget->setRowCount(2);
        right_tableWidget->setColumnCount(3);
        right_tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        right_tableWidget->verticalHeader()->setVisible(false);
        right_tableWidget->verticalHeader()->setHighlightSections(false);

        verticalLayout_2->addWidget(right_tableWidget);


        gridLayout->addWidget(right_frame, 0, 1, 1, 1);

        left_frame = new QFrame(centralwidget);
        left_frame->setObjectName(QString::fromUtf8("left_frame"));
        left_frame->setFrameShape(QFrame::Box);
        left_frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(left_frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        driveleft_comboBox = new QComboBox(left_frame);
        driveleft_comboBox->setObjectName(QString::fromUtf8("driveleft_comboBox"));
        driveleft_comboBox->setMaximumSize(QSize(60, 16777215));

        verticalLayout->addWidget(driveleft_comboBox);

        left_path_lineEdit = new QLineEdit(left_frame);
        left_path_lineEdit->setObjectName(QString::fromUtf8("left_path_lineEdit"));
        left_path_lineEdit->setFocusPolicy(Qt::NoFocus);
        left_path_lineEdit->setAutoFillBackground(true);
        left_path_lineEdit->setFrame(false);
        left_path_lineEdit->setReadOnly(true);

        verticalLayout->addWidget(left_path_lineEdit);

        left_tableWidget = new QTableWidget(left_frame);
        if (left_tableWidget->columnCount() < 3)
            left_tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        left_tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        left_tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        if (left_tableWidget->rowCount() < 2)
            left_tableWidget->setRowCount(2);
        left_tableWidget->setObjectName(QString::fromUtf8("left_tableWidget"));
        left_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        left_tableWidget->setShowGrid(false);
        left_tableWidget->setSortingEnabled(true);
        left_tableWidget->setRowCount(2);
        left_tableWidget->setColumnCount(3);
        left_tableWidget->horizontalHeader()->setVisible(true);
        left_tableWidget->horizontalHeader()->setHighlightSections(true);
        left_tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        left_tableWidget->verticalHeader()->setVisible(false);
        left_tableWidget->verticalHeader()->setHighlightSections(false);
        left_tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));

        verticalLayout->addWidget(left_tableWidget);


        gridLayout->addWidget(left_frame, 0, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 20));

        gridLayout->addWidget(label, 1, 0, 1, 2);

        log_listWidget = new QListWidget(centralwidget);
        log_listWidget->setObjectName(QString::fromUtf8("log_listWidget"));
        log_listWidget->setMaximumSize(QSize(16777215, 80));

        gridLayout->addWidget(log_listWidget, 2, 0, 1, 2);

        Client_Server_MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Client_Server_MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 638, 18));
        menuFTP_Server = new QMenu(menubar);
        menuFTP_Server->setObjectName(QString::fromUtf8("menuFTP_Server"));
        menuFTP_Client = new QMenu(menubar);
        menuFTP_Client->setObjectName(QString::fromUtf8("menuFTP_Client"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        Client_Server_MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(Client_Server_MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Client_Server_MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(Client_Server_MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setIconSize(QSize(40, 40));
        Client_Server_MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFTP_Server->menuAction());
        menubar->addAction(menuFTP_Client->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menuFTP_Server->addAction(action_MenuServerStarted);
        menuFTP_Server->addSeparator();
        menuFTP_Server->addAction(action_MenuServerOptions);
        menuFTP_Client->addAction(action_MenuClientConnected);
        menuFTP_Client->addAction(action_MenuClientOptions);
        menuOptions->addAction(action_ViewOptions);
        toolBar->addAction(action_ToolServerStarted);
        toolBar->addAction(action_ToolClientConnected);

        retranslateUi(Client_Server_MainWindow);

        QMetaObject::connectSlotsByName(Client_Server_MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *Client_Server_MainWindow)
    {
        Client_Server_MainWindow->setWindowTitle(QApplication::translate("Client_Server_MainWindow", "Client-Server Browser", 0, QApplication::UnicodeUTF8));
        action_MenuServerStarted->setText(QApplication::translate("Client_Server_MainWindow", "Create Connection...", 0, QApplication::UnicodeUTF8));
        action_MenuServerOptions->setText(QApplication::translate("Client_Server_MainWindow", "Connection Options...", 0, QApplication::UnicodeUTF8));
        action_MenuClientConnected->setText(QApplication::translate("Client_Server_MainWindow", "Connect...", 0, QApplication::UnicodeUTF8));
        action_MenuClientOptions->setText(QApplication::translate("Client_Server_MainWindow", "Connection Options", 0, QApplication::UnicodeUTF8));
        action_ToolServerStarted->setText(QApplication::translate("Client_Server_MainWindow", "FTP Server Started", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_ToolServerStarted->setToolTip(QApplication::translate("Client_Server_MainWindow", "FTP Server Started", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_ToolClientConnected->setText(QApplication::translate("Client_Server_MainWindow", "Client Connected", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_ToolClientConnected->setToolTip(QApplication::translate("Client_Server_MainWindow", "Client Connected", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_ViewOptions->setText(QApplication::translate("Client_Server_MainWindow", "View Options", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Client_Server_MainWindow", "F4  Edit", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Client_Server_MainWindow", "F5  Copy", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = right_tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Client_Server_MainWindow", "Name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = right_tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Client_Server_MainWindow", "Size", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = left_tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("Client_Server_MainWindow", "Name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = left_tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("Client_Server_MainWindow", "Size", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Client_Server_MainWindow", "Log Output", 0, QApplication::UnicodeUTF8));
        menuFTP_Server->setTitle(QApplication::translate("Client_Server_MainWindow", "FTP Server", 0, QApplication::UnicodeUTF8));
        menuFTP_Client->setTitle(QApplication::translate("Client_Server_MainWindow", "FTP Client", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("Client_Server_MainWindow", "Options", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("Client_Server_MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Client_Server_MainWindow: public Ui_Client_Server_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
