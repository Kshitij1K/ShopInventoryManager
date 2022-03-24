#pragma once
#include <shop.hpp>
#include <shop_state.hpp>

class ProfitLossDisplay : public ShopState {
 public:
  void enter(Shop* shop);
  void exit(Shop* shop);
  static ShopState& getInstance();

 private:
  ProfitLossDisplay();
  ProfitLossDisplay(const ProfitLossDisplay& other);
  ProfitLossDisplay& operator=(const ProfitLossDisplay& other);
};