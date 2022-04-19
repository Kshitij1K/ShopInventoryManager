#include "mainwindow.hpp"
#include <chrono>
#include <iostream>
#include <shop.hpp>
#include <thread>
#include "ui_mainwindow.h"

MainWindow::MainWindow(Shop* shop, QWidget* parent)
    : QMainWindow(parent), shop_(shop), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QObject::connect(ui->login_button, &QPushButton::clicked, this,
                   &MainWindow::loginButtonPressed);
  QObject::connect(ui->reset_button, &QPushButton::clicked, this,
                   &MainWindow::resetButtonPressed);
  QObject::connect(ui->admin_logout_button, &QPushButton::clicked, this,
                   &MainWindow::logoutButtonPressed);
  QObject::connect(ui->employee_logout_button, &QPushButton::clicked, this,
                   &MainWindow::logoutButtonPressed);

  QObject::connect(ui->stock_info_button, &QPushButton::clicked, this,
                   &MainWindow::stockInfoRequested);
  QObject::connect(ui->Update_Item_Information, &QPushButton::clicked, this,
                   &MainWindow::updateItemsRequested);
  QObject::connect(ui->Update_Button, &QPushButton::clicked, this,
                   &MainWindow::updateItemStock);
  QObject::connect(ui->recommendation_system_button, &QPushButton::clicked,
                   this, &MainWindow::recommendationPageRequested);
  QObject::connect(ui->item_info_back_button, &QPushButton::clicked, this,
                   &MainWindow::adminBackButtonPressed);
  QObject::connect(ui->editEmployeeButton, &QPushButton::clicked, this,
                   &MainWindow::changeCredentialsPageRequested);

  QObject::connect(ui->addNewEmployeeButton, &QPushButton::clicked, this,
                   &MainWindow::addEmployeeRequest);
  QObject::connect(ui->addNewEmployeeAsAdminButton, &QPushButton::clicked, this,
                   &MainWindow::addEmployeeAsAdminRequest);
  QObject::connect(ui->changeEmployeeCredsButton, &QPushButton::clicked, this,
                   &MainWindow::changeCredentialsRequest);
  QObject::connect(ui->deleteEmployeeButton, &QPushButton::clicked, this,
                   &MainWindow::deleteEmployeeRequest);

  QObject::connect(ui->restocking_suggestion_back_button, &QPushButton::clicked,
                   this, &MainWindow::adminBackButtonPressed);
  QObject::connect(ui->forecast_button, &QPushButton::clicked, this,
                   &MainWindow::forecastButtonPressed);
  QObject::connect(ui->Back_Button, &QPushButton::clicked, this,
                   &MainWindow::adminBackButtonPressed);
  QObject::connect(ui->addChangeEmployeeBackButton, &QPushButton::clicked, this,
                   &MainWindow::adminBackButtonPressed);

  QObject::connect(ui->compute_suggestion_button, &QPushButton::clicked, this,
                   &MainWindow::computeSuggestionButtonPressed);

  QObject::connect(ui->Add_Button, &QPushButton::clicked, this,
                   &MainWindow::addNewItem);

  QObject::connect(ui->deleteItemButton, &QPushButton::clicked, this,
                   &MainWindow::deleteItem);

  QObject::connect(ui->Add_Button_Invoice, &QPushButton::clicked, this,
                   &MainWindow::addButtonInvoicePressed);
  QObject::connect(ui->Delete_Button_Invoice, &QPushButton::clicked, this,
                   &MainWindow::deleteButtonInvoicePressed);
  QObject::connect(ui->Generate_Button, &QPushButton::clicked, this,
                   &MainWindow::generateInvoiceCalled);
  QObject::connect(ui->Cancel_Button, &QPushButton::clicked, this,
                   &MainWindow::cancelInvoiceCalled);

  ui->itemIDLineEdit->setValidator(new QIntValidator(1, 32000, this));
  ui->stockChangesLineEdit->setValidator(new QIntValidator(1, 32000, this));
  ui->buyingPriceLineEdit->setValidator(new QDoubleValidator(0.0, 10000000000000000.00, 2, this));
  ui->sellingPriceLineEdit->setValidator(new QDoubleValidator(0.0, 10000000000000000.00, 2, this));
  ui->holdingPriceLineEdit->setValidator(new QDoubleValidator(0.0, 10000000000000000.00, 2, this));

  ui->capital_input_field->setValidator(new QDoubleValidator(0.0, 10000000000000000.00, 2, this));

  // No space validators

  ui->Item_id_Line_Edit->setValidator(new QIntValidator(1, 32000, this));
  ui->Quantity_Line_Edit->setValidator(new QIntValidator(1, 32000, this));
  
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::loginButtonPressed() {
  shop_->username = ui->username_field->text().toStdString();
  shop_->password = ui->password_field->text().toStdString();
  shop_->callEvent(ShopState::Event::kLoginCalled);

  if (shop_->are_credentials_correct) {
    if (shop_->is_admin_login) {
      ui->stackedWidget->setCurrentIndex(1);
    } else {
      ui->stackedWidget->setCurrentIndex(7);
      refreshInvoiceTable();
    }
    ui->username_field->clear();
    ui->password_field->clear();
  }
}

void MainWindow::resetButtonPressed() {
  ui->username_field->clear();
  ui->password_field->clear();
}

void MainWindow::logoutButtonPressed() {
  ui->stackedWidget->setCurrentIndex(0);
  shop_->callEvent(ShopState::Event::kExitCalled);
  refreshInvoiceTable();
}

void MainWindow::stockInfoRequested() {
  ui->stackedWidget->setCurrentIndex(2);
  shop_->callEvent(ShopState::Event::kStockInfoCalled);
  prepareStockInfoTable(shop_->stocks);
  // ui->stock_info_table->setRows()
}

void MainWindow::addNewItem() {
  shop_->item_for_update.item_id = ui->itemIDLineEdit->text().toLongLong();
  shop_->item_for_update.item_name = ui->itemNameLineEdit->text().toStdString();
  shop_->item_for_update.buying_price =
      ui->buyingPriceLineEdit->text().toFloat();
  shop_->item_for_update.selling_price =
      ui->sellingPriceLineEdit->text().toFloat();
  shop_->item_for_update.holding_price =
      ui->holdingPriceLineEdit->text().toFloat();
  shop_->item_stock_update = ui->stockChangesLineEdit->text().toLongLong();
  shop_->callEvent(ShopState::Event::kNewItemAdded);

  ui->itemIDLineEdit->clear();
  ui->itemNameLineEdit->clear();
  ui->buyingPriceLineEdit->clear();
  ui->sellingPriceLineEdit->clear();
  ui->holdingPriceLineEdit->clear();
  ui->stockChangesLineEdit->clear();
}

void MainWindow::updateItemStock() {
  shop_->item_for_update.item_id = ui->itemIDLineEdit->text().toLongLong();
  shop_->item_for_update.item_name = ui->itemNameLineEdit->text().toStdString();
  shop_->item_for_update.buying_price =
      ui->buyingPriceLineEdit->text().toFloat();
  shop_->item_for_update.selling_price =
      ui->sellingPriceLineEdit->text().toFloat();
  shop_->item_for_update.holding_price =
      ui->holdingPriceLineEdit->text().toFloat();
  shop_->item_stock_update = ui->stockChangesLineEdit->text().toLongLong();
  shop_->callEvent(ShopState::Event::kItemStockUpdated);

  ui->itemIDLineEdit->clear();
  ui->itemNameLineEdit->clear();
  ui->buyingPriceLineEdit->clear();
  ui->sellingPriceLineEdit->clear();
  ui->holdingPriceLineEdit->clear();
  ui->stockChangesLineEdit->clear();
}

void MainWindow::recommendationPageRequested() {
  ui->stackedWidget->setCurrentIndex(4);
  shop_->callEvent(ShopState::Event::kRestockSuggestionCalled);
  ui->restocking_suggestion_table->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeMode::Stretch);
}

void MainWindow::adminBackButtonPressed() {
  ui->stackedWidget->setCurrentIndex(1);
  shop_->callEvent(ShopState::Event::kExitCalled);
}

void MainWindow::updateItemsRequested() {
  ui->stackedWidget->setCurrentIndex(3);
  shop_->callEvent(ShopState::Event::kItemUpdateCalled);
}

// void MainWindow::suggestionAsked() {
//     shop_->callEvent(ShopState::Event::kRestockSuggestionAsked);
// }

void MainWindow::prepareStockInfoTable(ItemStocks items) {
  long long int num_items = items.size();
  ui->stock_info_table->setRowCount(num_items);
  ui->stock_info_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->stock_info_table->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeMode::Stretch);

  int count = 0;
  for (auto item_ : items) {
    long long int stock = item_.second;

    auto item_name_disp =
        new QTableWidgetItem(QString(item_.first.item_name.c_str()));
    auto holding_price_disp = new QTableWidgetItem(
        QString(std::to_string(item_.first.holding_price).c_str()));
    auto buying_price_disp = new QTableWidgetItem(
        QString(std::to_string(item_.first.buying_price).c_str()));
    auto selling_price_disp = new QTableWidgetItem(
        QString(std::to_string(item_.first.selling_price).c_str()));
    auto item_id_disp = new QTableWidgetItem(
        QString(std::to_string(item_.first.item_id).c_str()));

    auto stock_disp =
        new QTableWidgetItem(QString(std::to_string(stock).c_str()));

    ui->stock_info_table->setItem(count, 0, item_id_disp);
    ui->stock_info_table->setItem(count, 1, item_name_disp);
    ui->stock_info_table->setItem(count, 2, buying_price_disp);
    ui->stock_info_table->setItem(count, 3, holding_price_disp);
    ui->stock_info_table->setItem(count, 4, selling_price_disp);
    ui->stock_info_table->setItem(count, 5, stock_disp);

    count++;
  }
}

void MainWindow::addButtonInvoicePressed() {
  long long int item_id = stoll(ui->Item_id_Line_Edit->text().toStdString());
  long long int quantity = stoll(ui->Quantity_Line_Edit->text().toStdString());

  Item item = shop_->database.getItemInfo(item_id);
  long long int stock = shop_->database.getItemStock(item_id);

  ItemStocks::iterator cart_item_;
  for (cart_item_ = shop_->consumer_cart.begin();
       cart_item_ != shop_->consumer_cart.end(); cart_item_++) {
    if (cart_item_->first.item_id == item_id) {
      if ((cart_item_->second + quantity) > stock) {
        std::cout << "Not enough items in stock! Aborting.\n\n";
        return;
      }
      cart_item_->second += quantity;
      refreshInvoiceTable();
      break;
    }
  }

  if (cart_item_ == shop_->consumer_cart.end()) {
    if (quantity > stock) {
      std::cout << "Not enough items in stock! Aborting.\n\n";
      return;
    }
    shop_->consumer_cart.push_back({item, quantity});
    refreshInvoiceTable();
  }

  ui->Item_id_Line_Edit->clear();
  ui->Quantity_Line_Edit->clear();
}

void MainWindow::deleteButtonInvoicePressed() {
  long long int item_id = stoll(ui->Item_id_Line_Edit->text().toStdString());
  long long int quantity = stoll(ui->Quantity_Line_Edit->text().toStdString());

  Item item = shop_->database.getItemInfo(item_id);

  ItemStocks::iterator cart_item_;
  for (cart_item_ = shop_->consumer_cart.begin();
       cart_item_ != shop_->consumer_cart.end(); cart_item_++) {
    if (cart_item_->first.item_id == item_id) {
      cart_item_->second -= quantity;

      if (cart_item_->second <= 0) shop_->consumer_cart.erase(cart_item_);

      refreshInvoiceTable();
      break;
    }
  }

  ui->Item_id_Line_Edit->clear();
  ui->Quantity_Line_Edit->clear();
}

void MainWindow::refreshInvoiceTable() {
  total_amount_ = 0;
  ui->invoice_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->invoice_table->setRowCount(shop_->consumer_cart.size());
  ui->invoice_table->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeMode::Stretch);

  int count = 0;
  for (auto item_ : shop_->consumer_cart) {
    double amount = item_.first.selling_price * item_.second;
    total_amount_ += amount;

    auto item_name_disp =
        new QTableWidgetItem(QString(item_.first.item_name.c_str()));
    auto item_id_disp = new QTableWidgetItem(
        QString(std::to_string(item_.first.item_id).c_str()));
    auto quantity_disp =
        new QTableWidgetItem(QString(std::to_string(item_.second).c_str()));
    auto amount_disp =
        new QTableWidgetItem(QString(std::to_string(amount).c_str()));
    auto selling_price_disp = new QTableWidgetItem(
        QString(std::to_string(item_.first.selling_price).c_str()));

    ui->invoice_table->setItem(count, 0, item_id_disp);
    ui->invoice_table->setItem(count, 1, item_name_disp);
    ui->invoice_table->setItem(count, 2, selling_price_disp);
    ui->invoice_table->setItem(count, 3, quantity_disp);
    ui->invoice_table->setItem(count, 4, amount_disp);

    count++;
  }

  ui->label_4->setText(QString(std::to_string(total_amount_).c_str()));
}

void MainWindow::generateInvoiceCalled() {
  shop_->callEvent(ShopState::Event::kItemsBought);
  refreshInvoiceTable();
}

void MainWindow::cancelInvoiceCalled() {
  shop_->consumer_cart.clear();
  refreshInvoiceTable();
  ui->Item_id_Line_Edit->clear();
  ui->Quantity_Line_Edit->clear();
}

void MainWindow::changeCredentialsPageRequested() {
  shop_->callEvent(ShopState::Event::kChangeCredentialsPageCalled);
  ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::addEmployeeRequest() {
  shop_->employee_name = ui->employeeNameLineEdit->text().toStdString();
  shop_->employee_username = ui->employeeUsernameLineEdit->text().toStdString();
  shop_->employee_password = ui->employeePasswordLineEdit->text().toStdString();

  shop_->callEvent(ShopState::Event::kAddEmployeeCredentialsCalled);

  ui->employeeNameLineEdit->clear();
  ui->employeeUsernameLineEdit->clear();
  ui->employeePasswordLineEdit->clear();
}

void MainWindow::addEmployeeAsAdminRequest() {
  shop_->employee_name = ui->employeeNameLineEdit->text().toStdString();
  shop_->employee_username = ui->employeeUsernameLineEdit->text().toStdString();
  shop_->employee_password = ui->employeePasswordLineEdit->text().toStdString();

  shop_->callEvent(ShopState::Event::kAddAdminCredentialsCalled);

  ui->employeeNameLineEdit->clear();
  ui->employeeUsernameLineEdit->clear();
  ui->employeePasswordLineEdit->clear();
}

void MainWindow::changeCredentialsRequest() {
  shop_->employee_name = ui->employeeNameLineEdit->text().toStdString();
  shop_->employee_username = ui->employeeUsernameLineEdit->text().toStdString();
  shop_->employee_password = ui->employeePasswordLineEdit->text().toStdString();

  shop_->callEvent(ShopState::Event::kCredentialsChanged);

  ui->employeeNameLineEdit->clear();
  ui->employeeUsernameLineEdit->clear();
  ui->employeePasswordLineEdit->clear();
}

void MainWindow::deleteEmployeeRequest() {
  std::string employee_name = ui->employeeNameLineEdit->text().toStdString();
  if (employee_name == "Admin") return;

  shop_->employee_name = employee_name;

  shop_->callEvent(ShopState::Event::kEmployeeDeleted);
  ui->employeeNameLineEdit->clear();
  ui->employeeUsernameLineEdit->clear();
  ui->employeePasswordLineEdit->clear();
}

void MainWindow::deleteItem() {
  auto id = ui->itemIDLineEdit->text().toLongLong();
  shop_->database.removeItem(id);
  ui->itemIDLineEdit->clear();
}

void MainWindow::forecastButtonPressed() {
  shop_->callEvent(ShopState::Event::kForecastUpdateCalled);
}

void MainWindow::computeSuggestionButtonPressed() {
  shop_->restocking_capital_available =
      ui->capital_input_field->text().toDouble();
  shop_->callEvent(ShopState::Event::kRestockSuggestionAsked);
  refreshSuggestionTable();
}

void MainWindow::refreshSuggestionTable() {
  total_amount_ = 0;
  ui->restocking_suggestion_table->setEditTriggers(
      QAbstractItemView::NoEditTriggers);
  ui->restocking_suggestion_table->setRowCount(
      shop_->restocking_solution.size());
  ui->restocking_suggestion_table->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeMode::Stretch);
  auto items_list = shop_->database.getAllItemStocks();
  int count = 0;
  for (auto item_it_ : items_list) {
    // double amount = item_.first.selling_price*item_.second;
    // total_amount_ += amount;

    auto item_id_disp = new QTableWidgetItem(
        QString(std::to_string(item_it_.first.item_id).c_str()));
    auto item_name_disp =
        new QTableWidgetItem(QString(item_it_.first.item_name.c_str()));
    auto restock_quantity_disp = new QTableWidgetItem(
        QString(std::to_string(shop_->restocking_solution[count]).c_str()));
    // auto amount_disp = new
    // QTableWidgetItem(QString(std::to_string(amount).c_str())); auto
    // selling_price_disp = new
    // QTableWidgetItem(QString(std::to_string(item_.first.selling_price).c_str()));

    ui->restocking_suggestion_table->setItem(count, 0, item_id_disp);
    ui->restocking_suggestion_table->setItem(count, 1, item_name_disp);
    ui->restocking_suggestion_table->setItem(count, 2, restock_quantity_disp);
    // ui->invoice_table->setItem(i, 3, quantity_disp);
    // ui->invoice_table->setItem(i, 4, amount_disp);
    std::cout << "refresh suggestion ran\n\n\n\n\n";
    count++;
  }
}

#include "moc_mainwindow.cpp"