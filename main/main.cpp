#include <mainwindow.hpp>
// #include <event_handler.hpp>
#include <shop.hpp>
#include <iostream>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    
    Shop shop;
    MainWindow* window = new MainWindow(&shop);
    window->show();

    return 0;
} 