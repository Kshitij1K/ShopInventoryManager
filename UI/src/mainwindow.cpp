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
            ui->stackedWidget->setCurrentIndex(2);
        }
    }
}

void MainWindow::resetButtonPressed() {
    ui->username_field->clear();
    ui->password_field->clear();
}

#include "moc_mainwindow.cpp"