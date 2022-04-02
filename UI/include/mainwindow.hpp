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
    void addButtonInvoicePressed();
    void deleteButtonInvoicePressed();
    void generateInvoiceCalled();
    void cancelInvoiceCalled();
    
    void suggestionAsked();
    void addNewItem();
    void updateItemStock();

    void prepareStockInfoTable(ItemStocks items);

private:
    Ui::MainWindow *ui;
    Shop* shop_;

    StockInfoModel stock_info_model;

    void refreshInvoiceTable();
    ItemStocks consumer_cart_;
    double total_amount_;
};

#endif // MAINWINDOW_H
