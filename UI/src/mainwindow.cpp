#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <shop.hpp>
#include <iostream>

MainWindow::MainWindow(Shop* shop, QWidget *parent) :
    QMainWindow(parent),
    shop_(shop),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->login_button, &QPushButton::clicked, this, &MainWindow::loginButtonPressed);
    QObject::connect(ui->reset_button, &QPushButton::clicked, this, &MainWindow::resetButtonPressed);
    QObject::connect(ui->admin_logout_button, &QPushButton::clicked, this, &MainWindow::logoutButtonPressed);

    QObject::connect(ui->stock_info_button, &QPushButton::clicked, this, &MainWindow::stockInfoRequested);
    // QObject::connect(ui->employee_list_button, &QPushButton::clicked, this, &MainWindow::employeeListRequested);
    QObject::connect(ui->Update_Item_Information, &QPushButton::clicked, this, &MainWindow::updateItemsRequested);
    QObject::connect(ui->Update_Button, &QPushButton::clicked, this, &MainWindow::updateItemStock);
    QObject::connect(ui->recommendation_system_button, &QPushButton::clicked, this, &MainWindow::recommendationPageRequested);
    
    QObject::connect(ui->restocking_suggestion_back_button, &QPushButton::clicked, this, &MainWindow::adminBackButtonPressed);
    // QObject::connect(ui->employee_list_back_button, &QPushButton::clicked, this, &MainWindow::adminBackButtonPressed);
    QObject::connect(ui->Back_Button, &QPushButton::clicked, this, &MainWindow::adminBackButtonPressed);

    QObject::connect(ui->compute_suggestion_button, &QPushButton::clicked, this, &MainWindow::suggestionAsked);
    QObject::connect(ui->Add_Button, &QPushButton::clicked, this, &MainWindow::addNewItem);

    // ui->stock_info_table->setModel(&stock_info_model);

    // ui->stock_info_table->insertRow(2);
    // ui->stock_info_table->setRowCount(10);
    // ui->stock_info_table->setColumnCount(4);
    // QStringList k = {"yo, u, i, o"};
    // ui->stock_info_table->setHorizontalHeaderLabels(k);
    // ui->stock_info_table->
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loginButtonPressed() {
    shop_->username = ui->username_field->text().toStdString();
    shop_->password = ui->password_field->text().toStdString();
    shop_->callEvent(ShopState::Event::kLoginCalled);
    
    if (shop_->are_credentials_correct) {
        if(shop_->is_admin_login) {
            ui->stackedWidget->setCurrentIndex(1);
        } else {
            // ui->stackedWidget->setCurrentIndex(2);
        }
    }
}

void MainWindow::resetButtonPressed() {
    ui->username_field->clear();
    ui->password_field->clear();
}

void MainWindow::logoutButtonPressed() {
    ui->stackedWidget->setCurrentIndex(0);
    shop_->callEvent(ShopState::Event::kExitCalled);
}

void MainWindow::stockInfoRequested() {
    ui->stackedWidget->setCurrentIndex(2);
    shop_->callEvent(ShopState::Event::kStockInfoCalled);
    prepareStockInfoTable();
    // ui->stock_info_table->setRows()
}

void MainWindow::addNewItem() {
    shop_->item_for_update.item_id = ui->Item_ID_Line_Edit->text().toLongLong();
    shop_->item_for_update.item_name = ui->Item_Name_line_edit->text().toStdString();
    shop_->item_for_update.buying_price = ui->Buying_Price_line_edit->text().toFloat();
    shop_->item_for_update.selling_price = ui->Selling_Price_line_edit->text().toFloat();
    shop_->item_for_update.holding_price = ui->Holding_Price_line_edit->text().toFloat();
    shop_->item_stock_update = ui->Stock_Change_Line_Edit->text().toLongLong();
    shop_->callEvent(ShopState::Event::kNewItemAdded);

    ui->Item_ID_Line_Edit->clear();
    ui->Item_Name_line_edit->clear();
    ui->Buying_Price_line_edit->clear();
    ui->Selling_Price_line_edit->clear();
    ui->Holding_Price_line_edit->clear();
    ui->Stock_Change_Line_Edit->clear();

}

void MainWindow::updateItemStock() {
    shop_->item_for_update.item_id = ui->Item_ID_Line_Edit->text().toLongLong();
    shop_->item_for_update.item_name = ui->Item_Name_line_edit->text().toStdString();
    shop_->item_for_update.buying_price = ui->Buying_Price_line_edit->text().toFloat();
    shop_->item_for_update.selling_price = ui->Selling_Price_line_edit->text().toFloat();
    shop_->item_for_update.holding_price = ui->Holding_Price_line_edit->text().toFloat();
    shop_->item_stock_update = ui->Stock_Change_Line_Edit->text().toLongLong();
    shop_->callEvent(ShopState::Event::kItemStockUpdated);

    ui->Item_ID_Line_Edit->clear();
    ui->Item_Name_line_edit->clear();
    ui->Buying_Price_line_edit->clear();
    ui->Selling_Price_line_edit->clear();
    ui->Holding_Price_line_edit->clear();
    ui->Stock_Change_Line_Edit->clear();
}

void MainWindow::recommendationPageRequested() {
    ui->stackedWidget->setCurrentIndex(4);
    shop_->callEvent(ShopState::Event::kRestockSuggestionCalled);
}

void MainWindow::adminBackButtonPressed() {
    ui->stackedWidget->setCurrentIndex(1);
    shop_->callEvent(ShopState::Event::kExitCalled);
}

void MainWindow::updateItemsRequested() {
    ui->stackedWidget->setCurrentIndex(3);
    shop_->callEvent(ShopState::Event::kItemUpdateCalled);
}


void MainWindow::suggestionAsked() {
    shop_->callEvent(ShopState::Event::kRestockSuggestionAsked);
}

void MainWindow::prepareStockInfoTable() {
    // ui->stock_info_table->setColumnCount(4);
    ui->stock_info_table->setRowCount(10);
    ui->stock_info_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // ui->stock_info_table->verticalHeader()->setHidden(true);
    auto k = new QTableWidgetItem(QString("Test data"));
    ui->stock_info_table->setItem(0, 0, k);
    // QStringList column_names = {"Item ID", "Item Name", "Item Price", "Item Profit/Loss"};

}

#include "moc_mainwindow.cpp"