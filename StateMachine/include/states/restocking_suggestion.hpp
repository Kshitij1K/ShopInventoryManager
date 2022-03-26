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
  void MipVarArray(std::vector<long long> current_inventory, std::vector<long double> buying_price, std::vector<long double> selling_price, std::vector<long double> holding_cost, std::vector<long long> forecast, long double capital);
};