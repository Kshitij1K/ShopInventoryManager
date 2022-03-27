#pragma once
#include <list>
#include <string>
#include <utility>

// The list consists of pairs of login and logout times. The first string is for
// the login time, and the second one is for the logout time
typedef std::list<std::pair<std::string, std::string>> AttendanceRecord;
typedef std::list<std::pair<Item, long long int>> ItemStocks;

enum class ItemUpdateResults {
  kExists,
  kDoesNotExist,
  kExistsWithDiffName,
  kStockNegative,
};

struct Item {
  long long int item_id;
  std::string item_name;
  float selling_price;
  float buying_price;
  float holding_price;
};

class Database {
 public:
  void updateEmployeeLogin(std::string employee_name, std::string time,std::string date="");
  // void updateEmployeeLogin(std::string employee_name, std::string time);

  void updateEmployeeLogout(std::string employee_name, std::string time,std::string date="");
  // void updateEmployeeLogout(std::string employee_name, std::string time);
  AttendanceRecord getEmployeeAttendance(std::string employee_name,
                                         std::string date);

  // ItemUpdateResults addNewItem(Item new_item);
  ItemUpdateResults addNewItem(Item new_item,long long int stock=0);


  ItemUpdateResults updateStock(Item item, long long int diff);

  void updateItemsSold(Item item, std::string date, long long int quantity);
  long long int getItemsSold(Item item, std::string date);

  ItemStocks getAllItemStocks();  
};

/*
* Stuff to implement in database
* Implement getAllItemStocks()
* Implement forecasting data storage and retrieval
* Add the buying price and holding price column to database
* Change hardcoded location of database
*/
