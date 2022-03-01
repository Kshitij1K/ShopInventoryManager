#include <all_shop_states.hpp>

ShopState& ProfitLossDisplay::getInstance(){
    static ProfitLossDisplay singleton;
    return singleton;
}

void ProfitLossDisplay::enter(Shop* shop) {}
void ProfitLossDisplay::exit(Shop* shop) {}
