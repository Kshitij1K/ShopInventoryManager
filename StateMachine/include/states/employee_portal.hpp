#pragma once
#include <shop.hpp>
#include <shop_state.hpp>

class EmployeePortal : public ShopState {
 public:
  void enter(Shop* shop);
  void exit(Shop* shop);
  static ShopState& getInstance();
  void eventCalled(Event event, Shop* shop);

 private:
  EmployeePortal();
  EmployeePortal(const EmployeePortal& other);
  EmployeePortal& operator=(const EmployeePortal& other);

};