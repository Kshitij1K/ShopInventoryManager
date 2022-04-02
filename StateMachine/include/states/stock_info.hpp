#pragma once
#include <shop.hpp>
#include <shop_state.hpp>

class StockInfo : public ShopState {
 public:
  void enter(Shop* shop);
  void exit(Shop* shop);
  static ShopState& getInstance();
  void eventCalled(Event event, Shop* shop);

 private:
  StockInfo();
  StockInfo(const StockInfo& other);
  StockInfo& operator=(const StockInfo& other);
};