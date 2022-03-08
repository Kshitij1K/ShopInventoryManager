#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton_next, &QPushButton::clicked, this, &MainWindow::requestPagetwo);
    QObject::connect(ui->pushButton_prev, &QPushButton::clicked, this, &MainWindow::requestPageone);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::requestPagetwo() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::requestPageone() {
    ui->stackedWidget->setCurrentIndex(0);
}


#include "moc_mainwindow.cpp"