#include <all_shop_states.hpp>
#include <fstream>

using namespace std;

ShopState& RestockingSuggestion::getInstance() {
  static RestockingSuggestion singleton;
  return singleton;
}

void RestockingSuggestion::enter(Shop* shop) {}
void RestockingSuggestion::exit(Shop* shop) {}

void RestockingSuggestion::eventCalled(Event event, Shop* shop) {
  switch (event)
  {
  case ShopState::Event::kExitCalled:
    shop->setState(AdminOptionSelection::getInstance());
    break;
  
  case ShopState::Event::kRestockSuggestionAsked:
  {
    ItemStocks all_items = shop->database.getAllItemStocks();
    /*
    std::vector<double> buying_price;
    std::vector<long long> current_inventory;
    std::vector<double> selling_price;
    std::vector<double> holding_cost;
    std::vector<double> forecast;
    for (auto current_pair : all_items){
        Item item = current_pair.first;
        current_inventory.push_back(current_pair.second);
        buying_price.push_back(item.buying_price);
        selling_price.push_back(item.selling_price);
        holding_cost.push_back(item.holding_price);
        forecast.push_back(2*shop->database.retrieve_predict_data_basis_of_id(item.item_id).front().Forecast);
        shop->restocking_solution = optimizer(current_inventory,buying_price,selling_price,holding_cost,forecast,shop->restocking_capital_available);

    }
    */
    ofstream datafile;
    datafile.open("../../optimizer/data.txt",ofstream::trunc);
    datafile << shop->capital <<endl;
    for (auto current_pair : all_items){
      Item item = current_pair.first;
      datafile << current_pair.second << "," <<item.buying_price << "," << item.selling_price << "," << item.holding_price << ",";
      datafile << 2*shop->database.retrieve_predict_data_basis_of_id(item.item_id).front().Forecast <<endl;
    }

    // Writing
    ifstream datafile2;
    datafile2.open("../../optimizer/data.txt",ifstream::trunc);
    string value;
    while(getline(datafile2,value)){
      shop->restocking_solution.push_back(stod(value));
    }

    break;
  }
  default:
    break;
  }
}

RestockingSuggestion::RestockingSuggestion() {}
