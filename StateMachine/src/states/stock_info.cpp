#include <all_shop_states.hpp>

ShopState& StockInfo::getInstance() {
  static StockInfo singleton;
  return singleton;
}

void StockInfo::enter(Shop* shop) {
  std::cout << "Entered state Stock Info\n";
  shop->stocks = shop->database.getAllItemStocks();
}

void StockInfo::exit(Shop* shop) {
  std::cout << "Exited state Stock Info\n";
}

StockInfo::StockInfo() {}

void StockInfo::eventCalled(Event event, Shop* shop) {
  switch (event)
  {
    case ShopState::Event::kExitCalled:
      shop->setState(AdminOptionSelection::getInstance());
      break;

    default:
      break;
  }
}