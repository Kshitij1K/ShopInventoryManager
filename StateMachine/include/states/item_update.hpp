#pragma once
#include <shop.hpp>
#include <shop_state.hpp>

class ItemUpdate : public ShopState {
 public:
  void enter(Shop* shop);
  void exit(Shop* shop);
  void eventCalled(Event event, Shop* shop);

  static ShopState& getInstance();

 private:
  ItemUpdate();
  ItemUpdate(const ItemUpdate& other);
  ItemUpdate& operator=(const ItemUpdate& other);
};