#pragma once
#include <shop_state.hpp>

class Shop;

class EmployeeAttendanceDisplay : public ShopState {
 public:
  void enter(Shop* shop);
  void exit(Shop* shop);
  static ShopState& getInstance();
  void eventCalled(Event event, Shop* shop);

 private:
  EmployeeAttendanceDisplay();
  EmployeeAttendanceDisplay(const EmployeeAttendanceDisplay& other);
  EmployeeAttendanceDisplay& operator=(const EmployeeAttendanceDisplay& other);
};