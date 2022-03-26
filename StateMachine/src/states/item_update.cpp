#include <all_shop_states.hpp>

ShopState& ItemUpdate::getInstance() {
  static ItemUpdate singleton;
  return singleton;
}

void ItemUpdate::enter(Shop* shop) {}
void ItemUpdate::exit(Shop* shop) {}

ItemUpdate::ItemUpdate() {}

void ItemUpdate::eventCalled(Event event, Shop* shop) {
  switch (event)
  {
  // case ShopState::Event::kRestockSuggestionCalled:
  //   shop->setState(RestockingSuggestion::getInstance());
  //   break;

  case ShopState::Event::kItemUpdateCalled:
    shop->setState(ItemUpdate::getInstance());
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