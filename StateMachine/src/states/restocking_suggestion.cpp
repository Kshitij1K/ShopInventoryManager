#include <all_shop_states.hpp>

ShopState& RestockingSuggestion::getInstance() {
  static RestockingSuggestion singleton;
  return singleton;
}

void RestockingSuggestion::enter(Shop* shop) {}
void RestockingSuggestion::exit(Shop* shop) {}

void RestockingSuggestion::eventCalled(Event event, Shop* shop) {
  switch (event)
  {
  case ShopState::Event::kExitCalled:
    shop->setState(AdminOptionSelection::getInstance());
    break;
  
  default:
    break;
  }
}

RestockingSuggestion::RestockingSuggestion() {}