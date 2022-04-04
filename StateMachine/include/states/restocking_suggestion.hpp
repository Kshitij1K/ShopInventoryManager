#pragma once
#include <shop.hpp>
#include <shop_state.hpp>

class RestockingSuggestion : public ShopState {
 public:
  void enter(Shop* shop);
  void exit(Shop* shop);
  static ShopState& getInstance();
  void eventCalled(Event event, Shop* shop);

 private:
  RestockingSuggestion();
  RestockingSuggestion(const RestockingSuggestion& other);
  RestockingSuggestion& operator=(const RestockingSuggestion& other);
  void execCommand();
  //std::vector<double> optimizer(std::vector<long long> current_inventory, std::vector<double> buying_price, std::vector<double> selling_price, std::vector<double> holding_cost, std::vector<double> forecast, long double capital);
};