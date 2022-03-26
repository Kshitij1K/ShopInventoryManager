#pragma once
#include <string>
#include <shop_state.hpp>
#include <database.hpp>

class Shop {
 public:
  Shop();

  inline ShopState* getCurrentState() const { return current_state_; }
  void setState(ShopState& new_state);

  std::string username;
  std::string password;
  long long int restocking_capital_available;
  long long int scanned_item_id;
  std::vector<std::pair<long long int, int>> items_bought;

  bool are_credentials_correct;
  bool is_admin_login;

  Database database;

  void callEvent(ShopState::Event event);

 private:
  ShopState* current_state_;
};