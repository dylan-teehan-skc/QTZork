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

//void MainWindow::refreshInventory() {
//    // Clear the current inventory display
//    QLayout *inventoryLayout = inventoryWidget->layout();
//    QLayoutItem *item;
//    while ((item = inventoryLayout->takeAt(0)) != nullptr) {
//        delete item->widget();
//        delete item;
//    }
//
//    Player* player = Player::getInstance();
//    const vector<Item>& items = player->getItemsInCharacter();
//
//    for (const Item& item : items) {
//        QString itemName = QString::fromStdString(item.getName());
//        QPushButton *equipButton = new QPushButton("Equip");
//        connect(equipButton, &QPushButton::clicked, this, [=]() {
//            player->equipWeapon(item);
//            append("Equipped " + itemName);
//        });
//
//        QHBoxLayout *itemLayout = new QHBoxLayout;
//        itemLayout->addWidget(new QLabel(itemName));
//        itemLayout->addWidget(equipButton);
//
//        inventoryLayout->addItem(itemLayout);
//    }
//
//    // Add a stretchable space at the end of the inventory layout
//    inventoryLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
//}

