#pragma once
#include <string>
#include <list>
#include <utility>

// The list consists of pairs of login and logout times. The first string is for the login time, and the second one is for the logout time
typedef std::list<std::pair<std::string, std::string>> AttendanceRecord;

enum class ItemUpdateResults {
    kExists,
    kDoesNotExist,
    kExistsWithDiffName,
    kStockNegative,
};

struct Item {
    long long int item_id;
    long long int item_name;
    float price;
};

class Database{
    public:
    void updateEmployeeLogin(std::string employee_name, std::string time);
    void updateEmployeeLogout(std::string employee_name, std::string time);
    AttendanceRecord getEmployeeAttendance(std::string employee_name, std::string date);

    ItemUpdateResults addNewItem(Item new_item);

    ItemUpdateResults updateStock(Item item, long long int diff);

    void updateItemsSold(Item item, std::string date, long long int quantity);
    long long int getItemsSold (Item item, std::string date);
};