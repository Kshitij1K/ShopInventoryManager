#pragma once

#include <string>
#include <vector>

#include <shop.hpp>
#include <mainwindow.hpp>

class EventHandler {
    public:
    EventHandler(Shop& shop, MainWindow& ui);

    void loginButtonPressed(std::string username, std::string password);
    
    void itemScanned(long long int item_id);
    void itemsSold(std::vector<long long int> items, std::vector<int> quantities);
}