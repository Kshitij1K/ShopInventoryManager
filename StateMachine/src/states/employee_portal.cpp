#include <all_shop_states.hpp>

ShopState& EmployeePortal::getInstance() {
  static EmployeePortal singleton;
  return singleton;
}

void EmployeePortal::enter(Shop* shop) {
  std::cout << "Entered State EmployeePortal\n";
}
void EmployeePortal::exit(Shop* shop) {
  std::cout << "Exited State EmployeePortal\n";

}

void EmployeePortal::eventCalled(Event event, Shop* shop) {
  switch (event)
  {
  case Event::kItemsBought:
    for (auto cart_item_:shop->consumer_cart) {
      shop->database.updateStock(cart_item_.first, -cart_item_.second);
    }
    shop->consumer_cart.clear();
    break;
  
  case Event::kExitCalled:
    shop->setState(Login::getInstance());
    shop->consumer_cart.clear();
    break;
  }
}

EmployeePortal::EmployeePortal(){};