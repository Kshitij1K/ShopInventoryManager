#include <all_shop_states.hpp>

ShopState& AdminOptionSelection::getInstance() {
  static AdminOptionSelection singleton;
  return singleton;
}

void AdminOptionSelection::enter(Shop* shop) {
  std::cout << "Entered state AdminOptionSelection\n";
}
void AdminOptionSelection::exit(Shop* shop) {
  std::cout << "Exited state AdminOptionSelection\n";
}

void AdminOptionSelection::eventCalled(Event event, Shop* shop) {
  switch (event)
  {
  // case ShopState::Event::kRestockSuggestionCalled:
  //   shop->setState(RestockingSuggestion::getInstance());
  //   break;

  case ShopState::Event::kForecastUpdateCalled:
    //shop->database.Insert_predict_data();
  case ShopState::Event::kChangeCredentialsPageCalled:
    shop->setState(ChangeLoginInfo::getInstance());
    break;

  case ShopState::Event::kItemUpdateCalled:
    shop->setState(ItemUpdate::getInstance());
    break;

  case ShopState::Event::kEmployeeAttendanceCalled:
    shop->setState(EmployeeAttendanceDisplay::getInstance());
    break;
  
  case ShopState::Event::kStockInfoCalled:
    shop->setState(StockInfo::getInstance());
    break;

  case ShopState::Event::kExitCalled:
    shop->setState(Login::getInstance());
    break;

  default:
    break;
  }
}

AdminOptionSelection::AdminOptionSelection(){}

void AdminOptionSelection::update_smoothed_error( ){
    //std::vector<long double> smoothed_error;
    double alpha = 0.3;
    long long n = smoothed_error.size();
    for (int i =0; i<n;i++){
        double error = demand[i]- forecast[i];
        smoothed_error[i] = (alpha*error + (1-alpha)*(smoothed_error[i]) );
    }
    return;
}

void AdminOptionSelection::update_MADt(){
    //std::vector<long double> MADt;
    double alpha = 0.3;
    long long n = MADt.size();
    for (int i=0; i<n; i++){
        double error = demand[i]-forecast[i];
        if(error<0){
            error = -error;
        }
        MADt[i] = (alpha*error + (1-alpha)*(MADt[i]));
    }
    return;
}

void AdminOptionSelection::T_calculater(){
    long long n = MADt.size();
    for (int i =0; i<n; i++){
        T[i] = (smoothed_error[i]/MADt[i]);
    }
    return;
}

void AdminOptionSelection::update_forecast(){
    long long n = smoothed_error.size();
    update_smoothed_error();
    update_MADt();
    T_calculater();
    for (int i=0; i<n; i++){
        double T_coeff = T[i];
        if(T_coeff<0){
            T_coeff = -T_coeff;
        }
        double error = demand[i] - forecast[i];
        forecast[i] = (forecast[i] + T_coeff*error);
    }
    return;
}
