#include <all_shop_states.hpp>

ShopState& AdminOptionSelection::getInstance() {
  static AdminOptionSelection singleton;
  return singleton;
}

void AdminOptionSelection::enter(Shop* shop) {}
void AdminOptionSelection::exit(Shop* shop) {}

void AdminOptionSelection::eventCalled(Event event, Shop* shop) {}

AdminOptionSelection::AdminOptionSelection(){}
