#include <all_shop_states.hpp>

ShopState& Login::getInstance() {
  static Login singleton;
  return singleton;
}

void Login::enter(Shop* shop) {
}
void Login::exit(Shop* shop) {
}

void Login::eventCalled(Event event, Shop* shop) {
  if (event == Event::kLoginCalled) {
    if (shop->username == "admin" && shop->password == "pass") {
      shop->is_admin_login = true;
      shop->are_credentials_correct = true;
      shop->setState(AdminOptionSelection::getInstance());
    } else if (shop->username == "employee" && shop->password == "pass") {
      shop->is_admin_login = false;
      shop->are_credentials_correct = true;
      shop->setState(EmployeePortal::getInstance());
    } else {
      shop->are_credentials_correct = false;
      shop->setState(Login::getInstance());
    }
  }
}

Login::Login() {}
