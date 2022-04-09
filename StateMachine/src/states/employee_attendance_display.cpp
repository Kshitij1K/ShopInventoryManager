#include <all_shop_states.hpp>

ShopState& EmployeeAttendanceDisplay::getInstance() {
  static EmployeeAttendanceDisplay singleton;
  return singleton;
}

void EmployeeAttendanceDisplay::enter(Shop* shop) {}
void EmployeeAttendanceDisplay::exit(Shop* shop) {}

void EmployeeAttendanceDisplay::eventCalled(Event event, Shop* shop) {
  switch (event) {
    case ShopState::Event::kExitCalled:
      shop->setState(AdminOptionSelection::getInstance());
      break;

    default:
      break;
  }
}

EmployeeAttendanceDisplay::EmployeeAttendanceDisplay() {}
