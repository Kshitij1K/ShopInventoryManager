#pragma once
#include <string>
#include <shop_state.hpp>
#include <database.hpp>

class Shop {
 public:
  Shop();
  ~Shop();

  inline ShopState* getCurrentState() const { return current_state_; }
  void setState(ShopState& new_state);

  std::string username;
  std::string password;
  long long int restocking_capital_available;
  long long int scanned_item_id;
  std::vector<std::pair<long long int, int>> items_bought;
  long double capital;

  bool are_credentials_correct;
  bool is_admin_login;

  Item item_for_update;
  long long int item_stock_update;

  ItemStocks stocks;
  ItemStocks consumer_cart;

  std::string employee_name;
  std::string employee_username;
  std::string employee_password;

  Database database;
  std::vector<double> restocking_solution;

  void callEvent(ShopState::Event event);

 private:
  ShopState* current_state_;
};