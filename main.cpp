#include <QApplication>
#include "ZorkUL.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow::getInstance()->show();
    return app.exec();
}
