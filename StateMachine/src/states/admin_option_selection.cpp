#include <all_shop_states.hpp>

ShopState& AdminOptionSelection::getInstance() {
  static AdminOptionSelection singleton;
  return singleton;
}

void AdminOptionSelection::enter(Shop* shop) {}
void AdminOptionSelection::exit(Shop* shop) {}

void AdminOptionSelection::eventCalled(Event event, Shop* shop) {
  switch (event)
  {
  case ShopState::Event::kRestockSuggestionCalled:
    shop->setState(RestockingSuggestion::getInstance());
    break;

  case ShopState::Event::kEmployeeAttendanceCalled:
    shop->setState(EmployeeAttendanceDisplay::getInstance());
    break;
  
  case ShopState::Event::kStockInfoCalled:
    break;

  case ShopState::Event::kExitCalled:
    shop->setState(Login::getInstance());
    break;

  default:
    break;
  }
}

AdminOptionSelection::AdminOptionSelection(){}
