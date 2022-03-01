#include <all_shop_states.hpp>

ShopState& RestockingSuggestion::getInstance(){
    static RestockingSuggestion singleton;
    return singleton;
}

void RestockingSuggestion::enter(Shop* shop) {}
void RestockingSuggestion::exit(Shop* shop) {}
