#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <shop.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow  : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Shop* shop, QWidget *parent = nullptr);
    ~MainWindow();

    void loginButtonPressed();
    void resetButtonPressed();

private:
    Ui::MainWindow *ui;
    Shop* shop_;
};

#endif // MAINWINDOW_H
