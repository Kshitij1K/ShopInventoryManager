#include <all_shop_states.hpp>

ShopState& EmployeeAttendanceDisplay::getInstance() {
  static EmployeeAttendanceDisplay singleton;
  return singleton;
}

void EmployeeAttendanceDisplay::enter(Shop* shop) {}
void EmployeeAttendanceDisplay::exit(Shop* shop) {}
