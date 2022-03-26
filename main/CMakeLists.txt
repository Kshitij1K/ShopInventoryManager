cmake_minimum_required(VERSION 3.10)
project(shop_inventory_manager)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../UI/build")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../StateMachine/build")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../Database/build")
find_package(shopinventory_ui REQUIRED)
find_package(state_machine REQUIRED)
find_package(database REQUIRED)

add_definitions(-std=c++17)
set(CMAKE_BUILD_TYPE Release)

include_directories(include)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
  ${PROJECT_NAME}
  shopinventory_ui::shopinventory_ui
  state_machine::state_machine
  database::database
)