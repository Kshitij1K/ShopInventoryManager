#include <sqlite3.h>
#include <database.hpp>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

// for getting attendance data
struct Data_v {
  int size;
  vector<map<string, string>> data;
};

// for getting Item_Info
struct Data_for_Item {
  int size;
  ItemStocks data1;
};

// for getting Item_Info
struct Data_for_Predict {
  int size;
  Predict_record data1;
};

// getting Item_id
struct Data_Item_List {
  int size;
  vector<string> data;
};

static int callback_simple_string(void* data, int argc, char** argv,
                                  char** azColName) {
  std::string* str = (std::string*)data;
  *str = std::string(*argv);

  return 0;
}

static int callback_login_string(void* data, int argc, char** argv,
                                 char** azColName) {
  std::vector<std::string>* str = (std::vector<std::string>*)data;

  str->push_back(std::string(argv[0]));
  str->push_back(std::string(argv[1]));

  return 0;
}

static int callback_iteminfo(void* data, int argc, char** argv,
                             char** azColName) {
  Item* item = (Item*)data;
  item->item_name = argv[0];
  item->selling_price = stod(argv[1]);

  return 0;
}

// function returns rows of data where each column is data mapped to column
// value
static int callback1(void* data, int argc, char** argv, char** azColName) {
  int i;
  struct Data_v* get_ans = (struct Data_v*)data;
  get_ans->size++;
  map<string, string> temp1;
  string temp2, temp3;
  for (i = 0; i < argc; i++) {
    temp2 = azColName[i];
    temp3 = argv[i] ? argv[i] : "NULL";
    temp1[temp2] = temp3;
  }
  get_ans->data.push_back(temp1);

  return 0;
}

static int callback2_getting_Item_data(void* data, int argc, char** argv,
                                       char** azColName) {
  int i;
  struct Data_for_Item* get_ans = (struct Data_for_Item*)data;
  get_ans->size++;

  list<std::pair<Item, long long int>> var1;

  vector<pair<string, string>> temp1;
  Item t1;

  long long int stock;
  string temp2, temp3;
  for (i = 0; i < argc; i++) {
    temp2 = azColName[i];
    temp3 = argv[i] ? argv[i] : "NULL";
    if (temp2.compare("ID") == 0) {
      t1.item_id = stoll(temp3);
    } else if (temp2.compare("name") == 0) {
      t1.item_name = temp3;
    }

    else if (temp2.compare("price") == 0) {
      if (temp3.compare("NULL") != 0)
        t1.selling_price = stof(temp3);
      else
        t1.selling_price = 0;
    } else if (temp2.compare("stock") == 0) {
      stock = stoll(temp3);
    } else if (temp2.compare("Holding_value") == 0) {
      if (temp3.compare("NULL") != 0)
        t1.holding_price = stof(temp3);
      else
        t1.holding_price = 0;
    } else if (temp2.compare("Buying_value") == 0) {
      if (temp3.compare("NULL") != 0)
        t1.buying_price = stof(temp3);
      else
        t1.buying_price = 0;
    }
  }
  get_ans->data1.push_back({t1, stock});
  return 0;
}

static int callback3_getting_Predict_data(void* data, int argc, char** argv,
                                          char** azColName) {
  int i;
  struct Data_for_Predict* get_ans = (struct Data_for_Predict*)data;
  get_ans->size++;

  Predict_data_type t1;

  string temp2, temp3;
  for (i = 0; i < argc; i++) {
    printf("%s = %s ", azColName[i], argv[i] ? argv[i] : "NULL");

    temp2 = azColName[i];
    temp3 = argv[i] ? argv[i] : "NULL";
    if (temp2.compare("Item_Id") == 0) {
      t1.item_id = stoll(temp3);
    } else if (temp2.compare("Smoothed_Error") == 0) {
      if (temp3.compare("NULL") != 0)
        t1.Smoothed_error = stof(temp3);
      else
        t1.Smoothed_error = 0;
    }

    else if (temp2.compare("Forecast") == 0) {
      if (temp3.compare("NULL") != 0)
        t1.Forecast = stof(temp3);
      else
        t1.Forecast = 0;
    }

    else if (temp2.compare("MADt") == 0) {
      if (temp3.compare("NULL") != 0)
        t1.MADt = stof(temp3);
      else
        t1.MADt = 0;
    } else if (temp2.compare("T") == 0) {
      if (temp3.compare("NULL") != 0)
        t1.T = stof(temp3);
      else
        t1.T = 0;
    }
  }
  get_ans->data1.push_back(t1);
  printf("\n");
  return 0;
}

// getting Item_ID list where name is input in Item_Info table
static int callback4_getting_Item_ID(void* data, int argc, char** argv,
                                     char** azColName) {
  int i;
  // Data_Item_List
  struct Data_Item_List* get_ans = (struct Data_Item_List*)data;
  get_ans->size++;

  string temp2, temp3;
  for (i = 0; i < argc; i++) {
    printf("%s = %s ", azColName[i], argv[i] ? argv[i] : "NULL");

    temp2 = azColName[i];
    temp3 = argv[i] ? argv[i] : "NULL";
  }

  get_ans->data.push_back(temp3);
  printf("\n");
  return 0;
}

sqlite3* Database::establish_connection(int& exit) {
  sqlite3* DB;
  exit = sqlite3_open(this->databse_var.c_str(), &DB);
  if (exit) {
    std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
  } else
    std::cout << "Opened Database Successfully!" << std::endl;

  return DB;
}

void Database::Insert_predict_data(Predict_data_type input_1) {
  // conection establishment
  sqlite3* DB;
  int exit = 0;
  DB = this->establish_connection(exit);
  string item_id;

  string id = to_string(input_1.item_id);
  string smoothed = to_string(input_1.Smoothed_error);
  string Forecast = to_string(input_1.Forecast);
  string madt = to_string(input_1.MADt);
  string T = to_string(input_1.T);

  string query = "UPDATE Predict_Table SET Smoothed_Error = " + smoothed +
                 ", Forecast = " + Forecast + ", MADt = " + madt +
                 ", T = " + T + " WHERE Item_Id = " + id + ";";

  char* error_msg1 = NULL;

  cout << endl << "SQL Query :" << query << endl;
  exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &error_msg1);

  std::string string_message1;
  if (error_msg1 == NULL) {
    string_message1 == "";
  } else {
    string_message1 = error_msg1;
  }

  if (exit != SQLITE_OK)
    cout << "Error in Updation" << endl;
  else {
    cout << "Operation OK!" << endl;
  }

  cout << "\nOutput Message " << string_message1 << endl;

  sqlite3_close(DB);
}

Predict_record Database::retrieve_predict_data_basis_of_name(
    std::string name)  // search on basis of item name
{
  // connection establised
  sqlite3* DB;
  int exit = 0;
  DB = this->establish_connection(exit);

  string query = "";
  query = "SELECT ID FROM Item_Info WHERE name = '" + name + "';";
  cout << endl << "SQL Query :" << query << endl;
  struct Data_Item_List* get_ans = new Data_Item_List();
  get_ans->size = 0;
  char* error_msg = NULL;
  exit = sqlite3_exec(DB, query.c_str(), callback4_getting_Item_ID, get_ans,
                      &error_msg);

  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  cout << endl;
  vector<string> id_list = get_ans->data;

  string tuple_ids = "(";
  for (auto in_id : id_list) {
    tuple_ids += in_id;
    tuple_ids += ",";
  }

  tuple_ids = tuple_ids.substr(0, tuple_ids.size() - 1);
  tuple_ids += ")";

  delete get_ans;

  query = "SELECT * FROM Predict_Table WHERE Item_Id IN " + tuple_ids + ";";

  struct Data_for_Predict* get_ans1 = new Data_for_Predict();
  get_ans1->size = 0;

  cout << endl << "SQL Query :" << query << endl;
  exit = sqlite3_exec(DB, query.c_str(), callback3_getting_Predict_data,
                      get_ans1, &error_msg);
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  cout << endl;
  Predict_record return_val1 = get_ans1->data1;
  cout << "\nOutput Message " << string_message << endl;
  delete get_ans1;
  sqlite3_close(DB);
  return return_val1;
}

Predict_record Database::retrieve_predict_data_basis_of_id(
    long long int id)  // search on basis of item id
{
  // connection establised
  sqlite3* DB;
  int exit = 0;
  DB = this->establish_connection(exit);

  string id_val = to_string(id);
  string query = "";
  query = "SELECT * FROM Predict_Table WHERE Item_Id = " + id_val + ";";

  struct Data_for_Predict* get_ans = new Data_for_Predict();
  get_ans->size = 0;
  char* error_msg = NULL;

  cout << endl << "SQL Query :" << query << endl;
  exit = sqlite3_exec(DB, query.c_str(), callback3_getting_Predict_data,
                      get_ans, &error_msg);
  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  cout << endl;
  Predict_record return_val1 = get_ans->data1;
  cout << "\nOutput Message " << string_message << endl;
  delete get_ans;
  sqlite3_close(DB);
  return return_val1;
}

void Database::updateEmployeeLogin(std::string employee_name, std::string time,
                                   std::string date) {
  // connection establised
  sqlite3* DB;
  int exit = 0;
  DB = this->establish_connection(exit);

  string name = employee_name;
  string query = "";

  string insert_1 = "INSERT INTO Emp_login_Info VALUES(";
  string insert_name = name;
  string insert_time = time;
  string insert_date = date;

  char* error_msg = NULL;

  string sql = insert_1 + "'" + insert_name + "','" + insert_time + "',NULL,'" +
               insert_date + "',NULL);";
  cout << "\nSQL : "
       << " " << sql << endl;
  exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &error_msg);
  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  cout << "\nOutput of Execution: " << string_message << endl;

  if (exit != SQLITE_OK)
    cout << "Error in Insertion" << endl;
  else {
    cout << "Operation OK!" << endl;
  }
  sqlite3_close(DB);
}

void Database::updateEmployeeLogout(string name, std::string time,
                                    string date) {
  // connection establised
  sqlite3* DB;
  int exit = 0;
  DB = this->establish_connection(exit);

  string query = "";

  string insert_1 = "UPDATE Emp_Login_Info SET ";
  string emp_name = name;
  string logout_time = time;
  string Date_val_logout = date;
  char* error_msg = NULL;

  string sql = insert_1 + "Logout_T = '" + logout_time + "',Date_val_logout='" +
               Date_val_logout + "' WHERE (Emp_Name = '" + emp_name +
               "' AND Logout_T is NULL AND Date_val_logout is NULL ) ;";
  cout << "\nSQL : "
       << " " << sql << endl;
  exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &error_msg);

  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  cout << "\nOutput: " << string_message << endl;
  if (exit != SQLITE_OK)
    cout << "Error in Insertion" << endl;
  else {
    cout << "Operation OK!" << endl;
  }
  sqlite3_close(DB);
}

AttendanceRecord Database::getEmployeeAttendance(std::string employee_name,
                                                 std::string date) {
  sqlite3* DB;
  int exit = 0;
  DB = this->establish_connection(exit);

  std::list<std::pair<std::string, std::string>> ans1;
  string query = "";
  query = "SELECT Login_T,Logout_T FROM Emp_Login_Info WHERE (Emp_Name = '" +
          employee_name + "' AND Date_val_login='" + date + "' );";
  struct Data_v* get_ans = new Data_v();
  get_ans->size = 0;
  char* error_msg = NULL;

  cout << endl << "SQL Query :" << query << endl;
  exit = sqlite3_exec(DB, query.c_str(), callback1, get_ans, &error_msg);

  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  cout << endl;
  for (auto i1 : get_ans->data) {
    pair<std::string, std::string> temp1 =
        make_pair(i1["Login_T"], i1["Logout_T"]);
    ans1.push_back(temp1);
  }
  cout << "\nOutput Message " << string_message << endl;
  sqlite3_close(DB);
  return ans1;
}

ItemUpdateResults Database::addNewItem(Item new_item, long long int stock) {
  // connection establised
  sqlite3* DB;
  int exit = 0;

  DB = this->establish_connection(exit);

  string query = "";
  string insert_1 = "INSERT INTO Item_Info VALUES(";
  string insert_id = to_string(new_item.item_id);
  string insert_name = new_item.item_name;
  string insert_price = to_string(new_item.selling_price);
  string stock_val = to_string(stock);

  string holding_value = to_string(new_item.holding_price);
  string buying_value = to_string(new_item.buying_price);

  char* error_msg = NULL;

  string sql = insert_1 + insert_id + ",'" + insert_name + "'," + insert_price +
               "," + stock_val + "," + holding_value + "," + buying_value +
               ");";

  struct Data_v* get_ans = new Data_v();
  get_ans->size = 0;
  cout << endl << "SQL Query :" << sql << endl;
  exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &error_msg);

  string match = "UNIQUE constraint failed: Item_Info.ID";
  ItemUpdateResults return_val = ItemUpdateResults::kDoesNotExist;
  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  if (exit != SQLITE_OK)
    cout << "Error in Insertion" << endl;
  else {
    cout << "Operation OK!" << endl;
  }

  cout << endl << "Exr4r4n Output Message " << string_message << endl;

  if (string_message.compare(match) == 0) {
    std::cout << "if is running\n";
    return_val = ItemUpdateResults::kExists;

    query =
        "SELECT Item_Info.name,Item_Info.stock FROM Item_Info Where "
        "Item_Info.ID = " +
        insert_id + ";";
    cout << endl << "SQL Query :" << query << endl;

    exit = sqlite3_exec(DB, query.c_str(), callback1, get_ans, &error_msg);
    cout << endl;
    string temp4_name = "", temp5_stock = "", temp6_hold = "", temp7_buy = "";
    for (auto i1 : get_ans->data)  // select data from query
    {
      temp4_name = i1["name"];
      temp5_stock = i1["stock"];
      temp6_hold = i1["Holding_value"];
      temp7_buy = i1["Buying_value"];
    }

    if (temp4_name.compare(insert_name) != 0) {
      // Different name
      return_val = ItemUpdateResults::kExistsWithDiffName;
    }
  } else {
    std::cout << "if is running\n";

    std::string insert_query1 =
        "INSERT INTO Sold_Items VALUES(" + insert_id + ", 0);";
    char* error_msg1 = NULL;

    cout << endl << "SQL Query :" << insert_query1 << endl;
    exit = sqlite3_exec(DB, insert_query1.c_str(), NULL, 0, &error_msg1);

    if (error_msg1 == NULL) {
      string_message == "";
    } else {
      string_message = error_msg1;
    }

    if (exit != SQLITE_OK)
      cout << "Error in Insertion" << endl;
    else {
      cout << "Operation OK!" << endl;
    }

    cout << endl << "Exn Output Message " << string_message << endl;

    std::string insert_query2 = "INSERT INTO Predict_Table VALUES(" +
                                insert_id + ", 0.0, 0.0, 0.0, 0.0);";
    char* error_msg2 = NULL;

    cout << endl << "SQL Query :" << insert_query2 << endl;
    exit = sqlite3_exec(DB, insert_query2.c_str(), NULL, 0, &error_msg2);

    if (error_msg2 == NULL) {
      string_message == "";
    } else {
      string_message = error_msg1;
    }

    if (exit != SQLITE_OK)
      cout << "Error in Insertion" << endl;
    else {
      cout << "Operation OK!" << endl;
    }

    cout << endl << "Exn Output Message " << string_message << endl;
  }
  sqlite3_close(DB);
  return return_val;
}

void Database::addEmployee(std::string name, std::string username,
                           std::string password, bool is_admin) {
  // connection establised
  sqlite3* DB;
  int exit = 0;

  DB = this->establish_connection(exit);

  string query = "";
  string insert_1 = "INSERT INTO Passwords VALUES(";

  char* error_msg = NULL;

  string sql = insert_1 + "'" + username + "','" + password + "','" + name +
               "'," + std::to_string(int(is_admin)) + ");";

  cout << endl << "SQL Query :" << sql << endl;
  exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &error_msg);

  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  if (exit != SQLITE_OK)
    cout << "Error in Insertion" << endl;
  else {
    cout << "Operation OK!" << endl;
  }

  cout << endl << "Exn Output Message " << string_message << endl;
}

void Database::removeEmployee(std::string name) {
  // connection establised
  sqlite3* DB;
  int exit = 0;

  DB = this->establish_connection(exit);

  string query = "";
  string insert_1 = "DELETE FROM Passwords WHERE Name='";

  char* error_msg = NULL;

  string sql = insert_1 + name + "';";

  cout << endl << "SQL Query :" << sql << endl;
  exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &error_msg);

  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  if (exit != SQLITE_OK)
    cout << "Error in Deletion" << endl;
  else {
    cout << "Operation OK!" << endl;
  }

  cout << endl << "Exn Output Message " << string_message << endl;
}

ItemUpdateResults Database::updateStock(Item new_item, long long int diff) {
  // connection establised
  sqlite3* DB;
  int exit = 0;
  DB = this->establish_connection(exit);

  long long int sto_1;
  string current_id = to_string(new_item.item_id);
  string current_name = new_item.item_name;
  string current_price = to_string(new_item.selling_price);
  string stock_diff = to_string(diff);

  char* error_msg = NULL;

  string query =
      "SELECT * FROM Item_Info Where Item_Info.ID = " + current_id + ";";
  cout << endl << "Sql Query :" << query << endl;

  struct Data_v* get_ans = new Data_v();
  get_ans->size = 0;

  exit = sqlite3_exec(DB, query.c_str(), callback1, get_ans, &error_msg);

  if (exit != SQLITE_OK)
    cout << "Search Query Failed" << endl;
  else {
    cout << "Operation OK!" << endl;
  }

  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  cout << "\nOutput Message " << string_message << endl;

  string temp1_id = "", temp2_name = "", temp3_price = "", temp4_stock = "";

  for (auto i1 : get_ans->data) {
    temp1_id = i1["ID"];
    temp2_name = i1["name"];
    temp3_price = i1["price"];
    temp4_stock = i1["stock"];
  }

  ItemUpdateResults return_val = ItemUpdateResults::kDoesNotExist;

  if (temp1_id == "") {
    // Data is not included in DataBase
    return_val = ItemUpdateResults::kDoesNotExist;
    // no data
    sqlite3_close(DB);
    return return_val;

  } else {
    // compare name and table data
    if (temp2_name.compare(current_name) != 0) {
      // Different name
      return_val = ItemUpdateResults::kExistsWithDiffName;
      sqlite3_close(DB);
      return return_val;

    } else if (temp4_stock < stock_diff) {
      // stock not available
      cout << " " << temp4_stock << " " << stock_diff << endl;
      return_val = ItemUpdateResults::kStockNegative;
      sqlite3_close(DB);
      return return_val;

    } else {
      sto_1 = stoi(temp4_stock);
      sto_1 = sto_1 + diff;  // new stock value
      query = "UPDATE Item_Info SET stock = " + to_string(sto_1) +
              " WHERE ID = " + temp1_id + ";";

      cout << "\nSql Query " << query << endl;

      exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &error_msg);

      if (exit != SQLITE_OK)
        cout << "Search Query Failed" << endl;
      else {
        cout << "Operation OK!" << endl;
      }

      if (error_msg == NULL) {
        string_message == "";
      } else {
        string_message = error_msg;
      }

      cout << " \n Updated Stock Value " << sto_1 << endl;
      cout << " \n Output Message" << string_message << endl;

      return_val = ItemUpdateResults::kExists;
      sqlite3_close(DB);
      return return_val;
    }
  }

  sqlite3_close(DB);
  return return_val;
}

void Database::changeEmployeeCredentials(std::string name,
                                         std::string new_username,
                                         std::string new_password) {
  // connection establised
  sqlite3* DB;
  int exit = 0;
  DB = this->establish_connection(exit);

  char* error_msg = NULL;
  std::string string_message;

  std::string query = "UPDATE Passwords SET Username = '" + new_username +
                      "', Password = '" + new_password + "' WHERE Name = '" +
                      name + "';";

  cout << "\nSql Query " << query << endl;

  exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &error_msg);

  if (exit != SQLITE_OK)
    cout << "Update Query Failed" << endl;
  else {
    cout << "Operation OK!" << endl;
  }

  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  cout << " \n Updated Employee creds Value " << endl;
  cout << " \n Output Message" << string_message << endl;

  sqlite3_close(DB);
}

LoginResult Database::verifyCredentials(std::string username,
                                        std::string password) {
  sqlite3* DB;
  int exit = 0;
  DB = this->establish_connection(exit);

  long long int sto_1;
  char* error_msg = NULL;
  std::string query =
      "SELECT Password, isAdmin FROM Passwords WHERE Username = '" + username +
      "';";

  cout << "\n SQLQuery: " << query << endl;

  std::vector<string> ans;

  exit =
      sqlite3_exec(DB, query.c_str(), callback_login_string, &ans, &error_msg);

  if (exit != SQLITE_OK)
    cout << "Search Query Failed" << endl;
  else {
    cout << "Operation OK!" << endl;
  }

  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  cout << "\nOutput Message " << string_message << endl;

  if (ans.size() != 0 && ans[0] == password) {
    if (ans[1] == "1") return LoginResult::kAdmin;
    return LoginResult::kEmployee;
  }

  return LoginResult::KNone;
}

void Database::updateItemsSold(Item item, long long int quantity) {
  // connection establised
  sqlite3* DB;
  int exit = 0;
  DB = this->establish_connection(exit);

  long long int sto_1;
  char* error_msg = NULL;

  string insert_1 = "INSERT INTO Sold_by_date VALUES(";

  std::string query = "SELECT Quantity FROM Sold_Items WHERE (Item_ID = '" +
                      std::to_string(item.item_id) + "');";

  cout << "\n SQLQuery: " << query << endl;

  std::string ans;

  exit =
      sqlite3_exec(DB, query.c_str(), callback_simple_string, &ans, &error_msg);

  if (exit != SQLITE_OK)
    cout << "Search Query Failed" << endl;
  else {
    cout << "Operation OK!" << endl;
  }

  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  cout << "\nOutput Message " << string_message << endl;

  if (ans == "") {
    std::string new_query = "INSERT INTO Sold_Items VALUES(" +
                            std::to_string(item.item_id) + ", " +
                            std::to_string(quantity) + ");";
    exit = sqlite3_exec(DB, new_query.c_str(), callback_simple_string, &ans,
                        &error_msg);
    if (exit != SQLITE_OK)
      cout << "Insert Query Failed" << endl;
    else {
      cout << "Operation OK!" << endl;
    }

    std::string string_message;
    if (error_msg == NULL) {
      string_message == "";
    } else {
      string_message = error_msg;
    }

    cout << "\nOutput Message " << string_message << endl;

  } else {
    std::string new_query =
        "UPDATE Sold_Items SET Quantity = " + to_string(stoll(ans) + quantity) +
        " WHERE Item_ID = " + std::to_string(item.item_id) + ";";
    exit = sqlite3_exec(DB, new_query.c_str(), callback_simple_string, &ans,
                        &error_msg);
    if (exit != SQLITE_OK)
      cout << "Update Query Failed" << endl;
    else {
      cout << "Operation OK!" << endl;
    }

    std::string string_message;
    if (error_msg == NULL) {
      string_message == "";
    } else {
      string_message = error_msg;
    }

    cout << "\nOutput Message " << string_message << endl;
  }

  sqlite3_close(DB);
}

long long int Database::getItemsSold(long long int id) {
  sqlite3* DB;
  int exit = 0;
  DB = this->establish_connection(exit);

  long long int sto_1;
  char* error_msg = NULL;

  std::string query = "SELECT Quantity FROM Sold_Items WHERE (Item_ID = '" +
                      std::to_string(id) + "');";

  cout << "\n SQLQuery: " << query << endl;

  std::string ans;

  exit =
      sqlite3_exec(DB, query.c_str(), callback_simple_string, &ans, &error_msg);

  if (exit != SQLITE_OK)
    cout << "Search Query Failed" << endl;
  else {
    cout << "Operation OK!" << endl;
  }

  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  cout << "\nOutput Message " << string_message << endl;

  if (ans == "") {
    cout << "No data for this id";
    return 0;
  }
  std::cout << "Ans is " << ans << "but value going is " << stoll(ans) << "\n";
  return stoll(ans);
}

ItemStocks Database::getAllItemStocks() {
  // connection establised
  sqlite3* DB;
  int exit = 0;

  DB = this->establish_connection(exit);

  string query;
  long long int sto_1;

  ItemStocks ans1;
  char* error_msg = NULL;
  struct Data_for_Item* get_ans = new Data_for_Item();
  get_ans->size = 0;
  query = "SELECT * FROM Item_Info;";

  cout << endl << "Sql Query :" << query << endl;
  exit = sqlite3_exec(DB, query.c_str(), callback2_getting_Item_data, get_ans,
                      &error_msg);
  if (get_ans->size == 0) {
    cout << "\n No such Data is present in Database";
    sqlite3_close(DB);
  }
  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }

  ans1 = get_ans->data1;
  delete get_ans;
  cout << "line 1357 reached";
  cout << "\nOutput Message " << string_message << endl;
  sqlite3_close(DB);
  return ans1;
}

Item Database::getItemInfo(long long int item_id) {
  Item* item = new Item;
  item->item_id = item_id;

  sqlite3* DB;
  int exit = 0;
  DB = this->establish_connection(exit);
  string query = "";
  query = "SELECT name,price FROM Item_Info WHERE (ID = '" +
          std::to_string(item_id) + "');";
  struct Data_v* get_ans = new Data_v();
  get_ans->size = 0;
  char* error_msg = NULL;

  cout << endl << "SQL Query :" << query << endl;
  exit = sqlite3_exec(DB, query.c_str(), callback_iteminfo, item, &error_msg);

  std::string string_message;
  if (error_msg == NULL) {
    string_message == "";
  } else {
    string_message = error_msg;
  }
  cout << "\nOutput Message " << string_message << endl;
  sqlite3_close(DB);
  return *item;
}