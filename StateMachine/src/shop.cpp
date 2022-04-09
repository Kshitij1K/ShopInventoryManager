#include <all_shop_states.hpp>
#include <shop.hpp>


Shop::Shop() {
  current_state_ = &Login::getInstance();
  current_state_->enter(this);
}

void Shop::setState(ShopState& new_state) {
  current_state_->exit(this);
  current_state_ = &new_state;
  current_state_->enter(this);
}

void Shop::callEvent(ShopState::Event event) {
  current_state_->eventCalled(event, this);
}

Shop::~Shop() { current_state_->exit(this); }