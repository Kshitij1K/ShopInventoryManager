#pragma once
#include <iostream>
#include <vector>


class Shop;

class ShopState {
 public:
  enum class Event {
    kLoginCalled,
    kItemUpdateCalled,
    kRestockSuggestionCalled,
    kRestockSuggestionAsked,
    kStockInfoCalled,
    kForecastUpdateCalled,
    kChangeCredentialsPageCalled,
    kAddEmployeeCredentialsCalled,
    kAddAdminCredentialsCalled,
    kCredentialsChanged,
    kEmployeeDeleted,
    kNewItemAdded,
    kItemStockUpdated,
    kProfitLossCalled,
    kEmployeeAttendanceCalled,
    kItemScanned,
    kItemsBought,
    kExitCalled
  };

  virtual void enter(Shop* shop) = 0;
  virtual void exit(Shop* shop) = 0;
  virtual void eventCalled(Event event, Shop* shop);
  virtual ~ShopState() {}
};