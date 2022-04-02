#pragma once
#include <shop.hpp>
#include <shop_state.hpp>

class AdminOptionSelection : public ShopState {
 public:
  void enter(Shop* shop);
  void exit(Shop* shop);
  static ShopState& getInstance();
  void eventCalled(Event event, Shop* shop);
  std::vector<double> smoothed_error;
  std::vector<double> MADt;
  std::vector<double> forecast;
  std::vector<double> T;
  std::vector<double> demand;

 private:
  AdminOptionSelection();
  AdminOptionSelection(const AdminOptionSelection& other);
  AdminOptionSelection& operator=(const AdminOptionSelection& other);
  void update_smoothed_error();
  void update_MADt();
  void T_calculater();
  void update_forecast();
};