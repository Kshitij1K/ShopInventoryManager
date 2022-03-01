#pragma once
#include <shop_state.hpp>

class Shop {

public:
Shop();

inline ShopState* getCurrentState() const {return current_state_;}
void setState(ShopState& new_state);

private:
ShopState* current_state_;

};