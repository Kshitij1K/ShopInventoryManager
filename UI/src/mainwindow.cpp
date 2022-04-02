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
    prepareStockInfoTable(shop_->stocks);
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

void MainWindow::prepareStockInfoTable(ItemStocks items) {
    long long int num_items = items.size();
    ui->stock_info_table->setRowCount(num_items);
    ui->stock_info_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    int count = 0;
    for (auto item_ : items) {
        long long int stock = item_.second;
        double profit = stock*(item_.first.selling_price-item_.first.buying_price);
        
        auto item_name_disp = new QTableWidgetItem(QString(item_.first.item_name.c_str()));
        auto holding_price_disp = new QTableWidgetItem(QString(std::to_string(item_.first.holding_price).c_str()));
        auto buying_price_disp = new QTableWidgetItem(QString(std::to_string(item_.first.buying_price).c_str()));
        auto selling_price_disp = new QTableWidgetItem(QString(std::to_string(item_.first.selling_price).c_str()));
        auto item_id_disp = new QTableWidgetItem(QString(std::to_string(item_.first.item_id).c_str()));
        
        auto stock_disp = new QTableWidgetItem(QString(std::to_string(stock).c_str()));
        auto profit_disp = new QTableWidgetItem(QString(std::to_string(profit).c_str()));
        

        ui->stock_info_table->setItem(count, 0, item_id_disp);
        ui->stock_info_table->setItem(count, 1, item_name_disp);
        ui->stock_info_table->setItem(count, 2, buying_price_disp);
        ui->stock_info_table->setItem(count, 3, holding_price_disp);
        ui->stock_info_table->setItem(count, 4, selling_price_disp);
        ui->stock_info_table->setItem(count, 5, stock_disp);
        ui->stock_info_table->setItem(count, 6, profit_disp);

        count++;
    }

}

#include "moc_mainwindow.cpp"