#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ZorkUL.h"
#include <QDebug>
#include "room.h"
MainWindow* MainWindow::instance = nullptr;

MainWindow* MainWindow::getInstance(QWidget *parent) {
    if (instance == nullptr) {
        instance = new MainWindow(parent);
    }
    return instance;
}

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        zorkUl(new ZorkUL(nullptr))
{
    ui->setupUi(this);
    Room* currentRoom = zorkUl->getCurrentRoom();
    QString Description = QString::fromStdString(currentRoom->longDescription());
    append("Welcome to Zork");
    append("Type info for help!");
    append(Description);
    zorkUl->play();

}

void MainWindow::append(const QString &text)
{
    ui->QTextEdit->appendPlainText(text);
    ui->QTextEdit->appendPlainText("");

}

MainWindow::~MainWindow()
{
    delete ui;
    delete zorkUl;
}

void MainWindow::on_lineEdit_returnPressed()
{
    static bool processing = false;
    if (processing) {
        return;
    }

    processing = true;
    QString userInput = ui->lineEdit->text();

    if (userInput.isEmpty()) {
        processing = false;
        return;
    }

    bool finished = zorkUl->update(userInput.toStdString());

    ui->lineEdit->clear();
    if (finished) {
        QCoreApplication::quit();
    }

    processing = false;
}

void MainWindow::on_goNorthButton_clicked()
{
    handleDirectionCommand("go north");
}

void MainWindow::on_goEastButton_clicked()
{
    handleDirectionCommand("go east");
}

void MainWindow::on_goWestButton_clicked()
{
    handleDirectionCommand("go west");
}

void MainWindow::on_goSouthButton_clicked()
{
    handleDirectionCommand("go south");
}

void MainWindow::handleDirectionCommand(const QString &command)
{
    static bool processing = false;
    if (processing) {
        return;
    }

    processing = true;
    bool finished = zorkUl->update(command.toStdString());

    if (finished) {
        QCoreApplication::quit();
    }

    processing = false;
}
