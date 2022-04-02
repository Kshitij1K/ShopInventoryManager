#pragma once
#include <list>
#include <string>
#include <utility>
#include <sqlite3.h>


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

struct Predict_data_type
{
    long long int item_id;
    double Smoothed_error;
    double Forecast;
    double MADt;
    double T;
};

// The list consists of pairs of login and logout times. The first string is for
// the login time, and the second one is for the logout time
typedef std::list<std::pair<std::string, std::string>> AttendanceRecord;
//list contains pair of Item and stocks retrieved from Item_Info table
typedef std::list<std::pair<Item, long long int>> ItemStocks;
//list of Predict_data_type {item_id,item_name,selling_price, buying_price , holding_price}
typedef std::list<Predict_data_type> Predict_record;



class Database 
{

 public:

  std::string databse_var = "Dbmain.db";
    //added later
  sqlite3* establish_connection(int &);



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



  void Insert_predict_data(Predict_data_type input_1);
  Predict_record retrieve_predict_data_basis_of_name(std::string name); //search on basis of item name
  Predict_record retrieve_predict_data_basis_of_id(long long int); //search on basis of item_id

};

/*
* Stuff to implement in database
* Done :: Implement getAllItemStocks() 
* Done :: Implement forecasting data storage and retrieval
* Done Add the buying price and holding price column to database
* Done Change hardcoded location of database
*/




/*
* 
* 
*
*
* Pending
* 
* various optimistation 
* connection_established function usage and removal of repeated code
* Fucntion callback renaming
* Variables for table name
*/







