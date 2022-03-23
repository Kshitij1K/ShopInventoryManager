#pragma once
#include <shop.hpp>
#include <shop_state.hpp>

class Login : public ShopState {
 public:
  void enter(Shop* shop);
  void exit(Shop* shop);
  static ShopState& getInstance();
  void eventCalled(Event event, Shop* shop);

 private:
  Login();
  Login(const Login& other);
  Login& operator=(const Login& other);
};