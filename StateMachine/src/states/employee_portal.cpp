#include <all_shop_states.hpp>

ShopState& EmployeePortal::getInstance() {
  static EmployeePortal singleton;
  return singleton;
}

void EmployeePortal::enter(Shop* shop) {}
void EmployeePortal::exit(Shop* shop) {}

void EmployeePortal::eventCalled(Event event, Shop* shop) {}

EmployeePortal::EmployeePortal(){};