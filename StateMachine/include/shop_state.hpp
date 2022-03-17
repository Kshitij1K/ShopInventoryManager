#pragma once

class Shop;

class ShopState {
 public:
  virtual void enter(Shop* shop) = 0;
  virtual void exit(Shop* shop) = 0;
  virtual ~ShopState() {}
};