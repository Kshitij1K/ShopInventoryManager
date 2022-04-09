#include <windows.h>
#include <all_shop_states.hpp>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

ShopState& RestockingSuggestion::getInstance() {
  static RestockingSuggestion singleton;
  return singleton;
}

void RestockingSuggestion::enter(Shop* shop) {
  std::cout << "Entered State Restocking Suggestion.\n";
}
void RestockingSuggestion::exit(Shop* shop) {
  std::cout << "Exited State Restocking Suggestion.\n";
}

void RestockingSuggestion::execCommand() {
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));

  // Start the child process.
  auto retvalue = CreateProcess(
      TEXT("..\\..\\optimizer\\build\\DEBUG\\optimizer.exe"),  // No module name
                                                               // (use command
                                                               // line)
      NULL,                                                    // Command line
      NULL,   // Process handle not inheritable
      NULL,   // Thread handle not inheritable
      FALSE,  // Set handle inheritance to FALSE
      0,      // No creation flags
      NULL,   // Use parent's environment block
      NULL,   // Use parent's starting directory
      &si,    // Pointer to STARTUPINFO structure
      &pi     // Pointer to PROCESS_INFORMATION structure
  );

  WaitForSingleObject(pi.hProcess, INFINITE);
}

void RestockingSuggestion::eventCalled(Event event, Shop* shop) {
  switch (event) {
    case ShopState::Event::kExitCalled:
      shop->setState(AdminOptionSelection::getInstance());
      break;

    case ShopState::Event::kRestockSuggestionAsked: {
      ItemStocks all_items = shop->database.getAllItemStocks();
      ofstream datafile;
      datafile.open("../../optimizer/data.txt", ofstream::trunc);
      datafile << shop->restocking_capital_available << endl;
      for (auto current_pair : all_items) {
        Item item = current_pair.first;
        datafile << current_pair.second << "," << item.buying_price << ","
                 << item.selling_price << "," << item.holding_price << ",";
        datafile << 2 * shop->database
                            .retrieve_predict_data_basis_of_id(item.item_id)
                            .front()
                            .Forecast
                 << endl;
      }
      execCommand();

      // Writing
      shop->restocking_solution.clear();
      ifstream datafile2;
      datafile2.open("../../optimizer/data.txt");
      string value;
      std::cout << "Values: \n";
      while (datafile2 >> value) {
        shop->restocking_solution.push_back(stod(value));
        std::cout << "This ran\n";
      }

      for (auto it : shop->restocking_solution) {
        std::cout << "Val: " << it << "\n";
      }

      break;
    }
    default:
      break;
  }
}

RestockingSuggestion::RestockingSuggestion() {}
