#include <all_shop_states.hpp>

ShopState& Login::getInstance(){
    static Login singleton;
    return singleton;
}

void Login::enter(Shop* shop) {}
void Login::exit(Shop* shop) {}
