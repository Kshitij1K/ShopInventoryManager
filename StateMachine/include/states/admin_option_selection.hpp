#pragma once
#include <shop.hpp>
#include <shop_state.hpp>

class AdminOptionSelection : public ShopState {
 public:
  void enter(Shop* shop);
  void exit(Shop* shop);
  static ShopState& getInstance();
  void eventCalled(Event event, Shop* shop);

 private:
  AdminOptionSelection();
  AdminOptionSelection(const AdminOptionSelection& other);
  AdminOptionSelection& operator=(const AdminOptionSelection& other);
};