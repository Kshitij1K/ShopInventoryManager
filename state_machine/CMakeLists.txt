cmake_minimum_required(VERSION 2.8.3)
project(state_machine)

add_definitions(-std=c++17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

include_directories(include)

add_library(admin_option_selection src/states/admin_option_selection.cpp)
add_library(employee_attendance_display src/states/employee_attendance_display.cpp)
add_library(employee_portal src/states/employee_portal.cpp)
add_library(login src/states/login.cpp)
add_library(profit_loss_display src/states/profit_loss_display.cpp)
add_library(restock_update src/states/restock_update.cpp)
add_library(restocking_suggestion src/states/restocking_suggestion.cpp)

add_library(shop src/shop.cpp)

target_link_libraries(admin_option_selection shop)
target_link_libraries(employee_attendance_display shop)
target_link_libraries(employee_attendance_display shop)
target_link_libraries(employee_portal shop)
target_link_libraries(login shop)
target_link_libraries(profit_loss_display shop)
target_link_libraries(restock_update shop)
target_link_libraries(restocking_suggestion shop)