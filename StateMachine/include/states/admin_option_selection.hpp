#pragma once
#include <shop.hpp>
#include <shop_state.hpp>

class AdminOptionSelection : public ShopState {
 public:
  void enter(Shop* shop);
  void exit(Shop* shop);
  static ShopState& getInstance();
  void eventCalled(Event event, Shop* shop);

 private:
  AdminOptionSelection();
  AdminOptionSelection(const AdminOptionSelection& other);
  AdminOptionSelection& operator=(const AdminOptionSelection& other);
  std::vector<long double> update_smoothed_error(double alpha, std::vector<long double> smoothed_error_prev, std::vector<long double>forecast_prev, std::vector<long double>demand_prev  );
  std::vector<long double> update_MADt(double alpha, std::vector<long double> MADt_prev, std::vector<long double> forecast_prev, std::vector<long double> demand_prev);
  std::vector<long double> T_calculater(std::vector<long double> smoothed_error, std::vector<long double> MADt);
  std::vector<long double> forecast(std::vector<long double> smoothed_error, std::vector<long double> MADt, std::vector<long double> forecast_prev, std::vector<long double> demand_prev, std::vector<long double> T);
};