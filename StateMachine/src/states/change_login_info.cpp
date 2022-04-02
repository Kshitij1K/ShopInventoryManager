#include <all_shop_states.hpp>

ShopState& ChangeLoginInfo::getInstance() {
  static ChangeLoginInfo singleton;
  return singleton;
}

void ChangeLoginInfo::enter(Shop* shop) {
  std::cout << "Entered State ChangeLoginInfo\n";
}

void ChangeLoginInfo::exit(Shop* shop) {
  std::cout << "Exited State ChangeLoginInfo\n";

}

void ChangeLoginInfo::eventCalled(Event event, Shop* shop) {
  switch (event)
  {
  case Event::kAddEmployeeCredentialsCalled:
    shop->database.addEmployee(shop->employee_name, shop->employee_username, shop->employee_password, false);
    break;

  case Event::kAddAdminCredentialsCalled:
    shop->database.addEmployee(shop->employee_name, shop->employee_username, shop->employee_password, true);
    break;
  
  case Event::kCredentialsChanged:
    shop->database.changeEmployeeCredentials(shop->employee_name, shop->employee_username, shop->employee_password);
    break;

  case Event::kEmployeeDeleted:
    shop->database.removeEmployee(shop->employee_name);
  
  default:
    break;
  }
}

ChangeLoginInfo::ChangeLoginInfo() {}
