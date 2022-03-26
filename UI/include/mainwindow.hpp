#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QTableView>
#include <shop.hpp>
#include <models/stock_info_model.hpp>

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
    void logoutButtonPressed();
    void resetButtonPressed();
    void stockInfoRequested();
    void employeeListRequested();
    void updateItemsRequested();
    void recommendationPageRequested();
    void adminBackButtonPressed();
    void suggestionAsked();

    void prepareStockInfoTable();

private:
    Ui::MainWindow *ui;
    Shop* shop_;

    StockInfoModel stock_info_model;
};

#endif // MAINWINDOW_H
