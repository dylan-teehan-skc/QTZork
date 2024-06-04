/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QPushButton *goNorthButton;
    QPushButton *goWestButton;
    QPushButton *goEastButton;
    QPushButton *goSouthButton;
    QPlainTextEdit *QTextEdit;
    QPushButton *attackButton;
    QPushButton *blockButton;
    QPushButton *battleButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(430, 360, 291, 28));
        goNorthButton = new QPushButton(centralwidget);
        goNorthButton->setObjectName(QString::fromUtf8("goNorthButton"));
        goNorthButton->setGeometry(QRect(110, 360, 161, 61));
        goWestButton = new QPushButton(centralwidget);
        goWestButton->setObjectName(QString::fromUtf8("goWestButton"));
        goWestButton->setGeometry(QRect(40, 430, 141, 61));
        goEastButton = new QPushButton(centralwidget);
        goEastButton->setObjectName(QString::fromUtf8("goEastButton"));
        goEastButton->setGeometry(QRect(190, 430, 151, 61));
        goSouthButton = new QPushButton(centralwidget);
        goSouthButton->setObjectName(QString::fromUtf8("goSouthButton"));
        goSouthButton->setGeometry(QRect(110, 500, 151, 61));
        QTextEdit = new QPlainTextEdit(centralwidget);
        QTextEdit->setObjectName(QString::fromUtf8("QTextEdit"));
        QTextEdit->setGeometry(QRect(20, 20, 751, 301));
        attackButton = new QPushButton(centralwidget);
        attackButton->setObjectName(QString::fromUtf8("attackButton"));
        attackButton->setGeometry(QRect(430, 500, 141, 61));
        blockButton = new QPushButton(centralwidget);
        blockButton->setObjectName(QString::fromUtf8("blockButton"));
        blockButton->setGeometry(QRect(590, 500, 141, 61));
        battleButton = new QPushButton(centralwidget);
        battleButton->setObjectName(QString::fromUtf8("battleButton"));
        battleButton->setGeometry(QRect(500, 420, 151, 61));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lineEdit->setText(QString());
        goNorthButton->setText(QCoreApplication::translate("MainWindow", "NORTH", nullptr));
        goWestButton->setText(QCoreApplication::translate("MainWindow", "WEST", nullptr));
        goEastButton->setText(QCoreApplication::translate("MainWindow", "EAST", nullptr));
        goSouthButton->setText(QCoreApplication::translate("MainWindow", "SOUTH", nullptr));
        attackButton->setText(QCoreApplication::translate("MainWindow", "ATTACK", nullptr));
        blockButton->setText(QCoreApplication::translate("MainWindow", "BLOCK", nullptr));
        battleButton->setText(QCoreApplication::translate("MainWindow", "BATTLE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
