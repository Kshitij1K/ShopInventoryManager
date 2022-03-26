#include <all_shop_states.hpp>

ShopState& AdminOptionSelection::getInstance() {
  static AdminOptionSelection singleton;
  return singleton;
}

void AdminOptionSelection::enter(Shop* shop) {}
void AdminOptionSelection::exit(Shop* shop) {}

void AdminOptionSelection::eventCalled(Event event, Shop* shop) {
  switch (event)
  {
  // case ShopState::Event::kRestockSuggestionCalled:
  //   shop->setState(RestockingSuggestion::getInstance());
  //   break;

  case ShopState::Event::kItemUpdateCalled:
    shop->setState(ItemUpdate::getInstance());
    break;

  case ShopState::Event::kEmployeeAttendanceCalled:
    shop->setState(EmployeeAttendanceDisplay::getInstance());
    break;
  
  case ShopState::Event::kStockInfoCalled:
    break;

  case ShopState::Event::kExitCalled:
    shop->setState(Login::getInstance());
    break;

  default:
    break;
  }
}

AdminOptionSelection::AdminOptionSelection(){}

 std::vector<long double> AdminOptionSelection::update_smoothed_error(double alpha, std::vector<long double> smoothed_error_prev, std::vector<long double>forecast_prev, std::vector<long double>demand_prev  ){
        std::vector<long double> smoothed_error;
        long long n = smoothed_error_prev.size();
        for (int i =0; i<n;i++){
            long double error = demand_prev[i]-forecast_prev[i];
            smoothed_error.push_back(alpha*error + (1-alpha)*(smoothed_error_prev[i]) );
        }
        return(smoothed_error);
    }

    std::vector<long double> AdminOptionSelection::update_MADt(double alpha, std::vector<long double> MADt_prev, std::vector<long double> forecast_prev, std::vector<long double> demand_prev){
        std::vector<long double> MADt;
        long long n = MADt_prev.size();
        for (int i=0; i<n; i++){
            long double error = demand_prev[i]-forecast_prev[i];
            if(error<0){
                error = -error;
            }
            MADt.push_back(alpha*error + (1-alpha)*(MADt_prev[i]));
        }
        return(MADt);
    }

    std::vector<long double> AdminOptionSelection::T_calculater(std::vector<long double> smoothed_error, std::vector<long double> MADt){
        long long n = MADt.size();
        std::vector<long double> T;
        for (int i =0; i<n; i++){
            T.push_back(smoothed_error[i]/MADt[i]);
        }
        return(T);
    }

    std::vector<long double> AdminOptionSelection::forecast(std::vector<long double> smoothed_error, std::vector<long double> MADt, std::vector<long double> forecast_prev, std::vector<long double> demand_prev, std::vector<long double> T){
        std::vector<long double> forecast_new;
        long long n = smoothed_error.size();
        for (int i=0; i<n; i++){
            long double T_coeff = T[i];
            if(T_coeff<0){
                T_coeff = -T_coeff;
            }
            long double error = demand_prev[i] - forecast_prev[i];
            forecast_new.push_back(forecast_prev[i] + T_coeff*error);
        }
        return(forecast_new);
    }
