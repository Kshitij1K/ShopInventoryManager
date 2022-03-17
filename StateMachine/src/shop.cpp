#include <shop.hpp>

Shop::Shop() {}

void Shop::setState(ShopState& new_state) {
  current_state_->exit(this);
  current_state_ = &new_state;
  current_state_->enter(this);
}
