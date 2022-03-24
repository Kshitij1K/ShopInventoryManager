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
    QObject::connect(ui->employee_list_button, &QPushButton::clicked, this, &MainWindow::employeeListRequested);
    QObject::connect(ui->recommendation_system_button, &QPushButton::clicked, this, &MainWindow::recommendationPageRequested);
    
    QObject::connect(ui->restocking_suggestion_back_button, &QPushButton::clicked, this, &MainWindow::adminBackButtonPressed);
    QObject::connect(ui->employee_list_back_button, &QPushButton::clicked, this, &MainWindow::adminBackButtonPressed);
    QObject::connect(ui->stock_info_back_button, &QPushButton::clicked, this, &MainWindow::adminBackButtonPressed);

    QObject::connect(ui->compute_suggestion_button, &QPushButton::clicked, this, &MainWindow::suggestionAsked);

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
    // ui->stackedWidget->setCurrentIndex(3);
    // shop_->callEvent(ShopState::Event::kStockInfoCalled);
}

void MainWindow::employeeListRequested() {
    ui->stackedWidget->setCurrentIndex(2);
    shop_->callEvent(ShopState::Event::kEmployeeAttendanceCalled);
}

void MainWindow::recommendationPageRequested() {
    ui->stackedWidget->setCurrentIndex(4);
    shop_->callEvent(ShopState::Event::kRestockSuggestionCalled);
}

void MainWindow::adminBackButtonPressed() {
    ui->stackedWidget->setCurrentIndex(1);
    shop_->callEvent(ShopState::Event::kExitCalled);
}

void MainWindow::suggestionAsked() {
    shop_->callEvent(ShopState::Event::kRestockSuggestionAsked);
}

#include "moc_mainwindow.cpp"