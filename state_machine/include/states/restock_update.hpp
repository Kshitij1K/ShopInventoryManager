#pragma once
#include <shop.hpp>
#include <shop_state.hpp>

class RestockUpdate : public ShopState {
 public:
  void enter(Shop* shop);
  void exit(Shop* shop);
  static ShopState& getInstance();

 private:
  RestockUpdate();
  RestockUpdate(const RestockUpdate& other);
  RestockUpdate& operator=(const RestockUpdate& other);
};