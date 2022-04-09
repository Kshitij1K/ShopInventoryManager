#include <all_shop_states.hpp>

ShopState& ItemUpdate::getInstance() {
  static ItemUpdate singleton;
  return singleton;
}

void ItemUpdate::enter(Shop* shop) {
  std::cout << "Entered state ItemUpdate\n";
}
void ItemUpdate::exit(Shop* shop) {
  std::cout << "Exited state ItemUpdate\n";
}

ItemUpdate::ItemUpdate() {}

void ItemUpdate::eventCalled(Event event, Shop* shop) {
  switch (event)
  {
    case ShopState::Event::kNewItemAdded:
      shop->database.addNewItem(shop->item_for_update, shop->item_stock_update);
      break;

    case ShopState::Event::kItemStockUpdated:
      shop->database.updateStock(shop->item_for_update, shop->item_stock_update);
      break;

    case ShopState::Event::kExitCalled:
      shop->setState(AdminOptionSelection::getInstance());
      break;

    default:
      break;
  }
}