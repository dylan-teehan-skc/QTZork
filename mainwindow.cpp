#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ZorkUL.h"
#include "player.h"
#include <QPixmap>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QDebug>
#include <QLabel>

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
        zorkUl(new ZorkUL())
{
    setStyleSheet("QMainWindow { background-color: #2E2E2E; }"
                  "QPushButton { background-color: #008080; color: white; border-radius: 5px; padding: 5px; }"
                  "QTextEdit { background-color: #1E1E1E; color: white; }"
                  "QLineEdit { background-color: #1E1E1E; color: white; }");


    ui->setupUi(this);
    Room* currentRoom = zorkUl->getCurrentRoom();
    QString Description = QString::fromStdString(currentRoom->longDescription());
    append("Welcome to Zork");
    append("Embark on a quest through mysterious rooms, each holding unique treasures. Collect valuable items like swords and maps to aid your journey. Defeat enemies strategically to uncover the path to victory. Navigate wisely through the interconnected rooms to win!!");
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
    handleCommand("go north");
}

void MainWindow::on_goEastButton_clicked()
{
    handleCommand("go east");
}

void MainWindow::on_goWestButton_clicked()
{
    handleCommand("go west");
}

void MainWindow::on_goSouthButton_clicked()
{
    handleCommand("go south");
}
void MainWindow::on_battleButton_clicked()
{
    handleCommand("battle");
}
void MainWindow::on_attackButton_clicked()
{
    handleCommand("attack");
}
void MainWindow::on_blockButton_clicked()
{
    handleCommand("block");
}

void MainWindow::handleCommand(const QString &command)
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

