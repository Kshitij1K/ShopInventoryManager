#pragma once
#include <shop.hpp>
#include <shop_state.hpp>

class ChangeLoginInfo : public ShopState {
 public:
  void enter(Shop* shop);
  void exit(Shop* shop);
  static ShopState& getInstance();
  void eventCalled(Event event, Shop* shop);

 private:
  ChangeLoginInfo();
  ChangeLoginInfo(const ChangeLoginInfo& other);
  ChangeLoginInfo& operator=(const ChangeLoginInfo& other);
};