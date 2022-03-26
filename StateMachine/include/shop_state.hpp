#pragma once
#include <vector>
#include <iostream>

class Shop;

class ShopState {
 public:
 
  enum class Event {kLoginCalled,
                    kItemUpdateCalled,
                    kRestockSuggestionCalled,
                    kRestockSuggestionAsked,
                    kStockInfoCalled,
                    // kItemUpdateCalled,
                    kNewItemAdded,
                    kItemStockUpdated,
                    kProfitLossCalled,
                    kEmployeeAttendanceCalled,
                    kItemScanned,
                    kItemsBought,
                    kExitCalled};
  
  virtual void enter(Shop* shop) = 0;
  virtual void exit(Shop* shop) = 0;
  virtual void eventCalled(Event event, Shop* shop);
  virtual ~ShopState() {}
};