#include <mainwindow.hpp>
#include <iostream>
#include <shop.hpp>


int main(int argc, char** argv) {
  QApplication app(argc, argv);

  Shop shop;
  MainWindow* window = new MainWindow(&shop);
  window->show();

  return app.exec();
}