#include <all_shop_states.hpp>

ShopState& RestockUpdate::getInstance() {
  static RestockUpdate singleton;
  return singleton;
}

void RestockUpdate::enter(Shop* shop) {}
void RestockUpdate::exit(Shop* shop) {}
