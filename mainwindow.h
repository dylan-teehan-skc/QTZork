#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "ZorkUL.h"
#include <QLabel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    QVBoxLayout *mainLayout;
    static MainWindow* getInstance(QWidget *parent = nullptr);
    ~MainWindow();
    void append(const QString &text);

private:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;
    static MainWindow* instance;
    Ui::MainWindow *ui;
    ZorkUL *zorkUl;

private slots:
    void on_lineEdit_returnPressed();
    void on_goNorthButton_clicked();
    void on_goEastButton_clicked();
    void on_goWestButton_clicked();
    void on_goSouthButton_clicked();
    void on_blockButton_clicked();
    void on_attackButton_clicked();
    void on_battleButton_clicked();
    void handleCommand(const QString &command);
};

#endif // MAINWINDOW_H
