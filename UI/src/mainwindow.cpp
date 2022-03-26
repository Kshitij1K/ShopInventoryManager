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
    QObject::connect(ui->recommendation_system_button, &QPushButton::clicked, this, &MainWindow::recommendationPageRequested);
    
    QObject::connect(ui->restocking_suggestion_back_button, &QPushButton::clicked, this, &MainWindow::adminBackButtonPressed);
    // QObject::connect(ui->employee_list_back_button, &QPushButton::clicked, this, &MainWindow::adminBackButtonPressed);
    QObject::connect(ui->Back_Button, &QPushButton::clicked, this, &MainWindow::adminBackButtonPressed);

    QObject::connect(ui->compute_suggestion_button, &QPushButton::clicked, this, &MainWindow::suggestionAsked);

    // ui->Stock_Information_Table->setModel(&stock_info_model);

    // ui->Stock_Information_Table->insertRow(2);
    // ui->Stock_Information_Table->setRowCount(10);
    // ui->Stock_Information_Table->setColumnCount(4);
    // QStringList k = {"yo, u, i, o"};
    // ui->Stock_Information_Table->setHorizontalHeaderLabels(k);
    // ui->Stock_Information_Table->
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
    // ui->Stock_Information_Table->setRows()
}

// void MainWindow::employeeListRequested() {
//     ui->stackedWidget->setCurrentIndex(2);
//     shop_->callEvent(ShopState::Event::kEmployeeAttendanceCalled);
//     ui->employee_list_table->setModel(&employee_attendance);
// }

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
    // shop_->callEvent(ShopState::Event::kExitCalled);
}


void MainWindow::suggestionAsked() {
    shop_->callEvent(ShopState::Event::kRestockSuggestionAsked);
}

void MainWindow::prepareStockInfoTable() {
    // ui->Stock_Information_Table->setColumnCount(4);
    ui->Stock_Information_Table->setRowCount(10);
    ui->Stock_Information_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // ui->Stock_Information_Table->verticalHeader()->setHidden(true);
    auto k = new QTableWidgetItem(QString("Test data"));
    ui->Stock_Information_Table->setItem(0, 0, k);
    // QStringList column_names = {"Item ID", "Item Name", "Item Price", "Item Profit/Loss"};

}

#include "moc_mainwindow.cpp"