cmake_minimum_required(VERSION 3.10)
project(state_machine)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../UI/build")
# find_package(shopinventory_ui REQUIRED)

add_definitions(-std=c++17)
set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

include_directories(include)

# add_library(admin_option_selection src/states/admin_option_selection.cpp)
# add_library(employee_attendance_display src/states/employee_attendance_display.cpp)
# add_library(employee_portal src/states/employee_portal.cpp)
# add_library(login src/states/login.cpp)
# add_library(profit_loss_display src/states/profit_loss_display.cpp)
# add_library(restock_update src/states/restock_update.cpp)
# add_library(restocking_suggestion src/states/restocking_suggestion.cpp)

add_library(
  ${PROJECT_NAME} 
  src/shop.cpp
  src/states/admin_option_selection.cpp
  src/states/employee_portal.cpp
  src/states/login.cpp
)
# target_link_libraries(
#   ${PROJECT_NAME}
#   login
#   employee_portal
#   admin_option_selection
# )

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})


# Then, include gnuinstalldir to get the platform's standard directories:
include(GNUInstallDirs)

# Then, carefully add your include directories. All of your `target_include_directories` must look like this
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # include directory in your build tree
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>       # include directory when installed
)

# Now, create the install script. We install all header files under `include/yourlibrary` to install them in `<prefix>/include/yourlibrary`:
install(
  DIRECTORY include
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)

# We add `${PROJECT_NAME}` target into the export set.
# The export set will contain all targets to be imported by the other project.
# It also installs the library to the install script so they are installed:
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Now, we install the export set. This will generate a CMake file exporting all the target for other projects to use:
install(EXPORT ${PROJECT_NAME}-targets
  DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}"
  NAMESPACE ${PROJECT_NAME}::
)

# Now, we also export the current buildtree. Other project will be able to import the project directly from a build dir:
configure_file(cmake/${PROJECT_NAME}-config.cmake ${PROJECT_NAME}-config.cmake COPYONLY)
export(
  EXPORT ${PROJECT_NAME}-targets
  NAMESPACE ${PROJECT_NAME}::
  FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake"
)

# The file we created earlier:
install(
    FILES cmake/${PROJECT_NAME}-config.cmake
    DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}"
)


# target_link_libraries(admin_option_selection shop)
# target_link_libraries(employee_attendance_display shop)
# target_link_libraries(employee_attendance_display shop)
# target_link_libraries(employee_portal shop)
# target_link_libraries(login shop)
# target_link_libraries(profit_loss_display shop)
# target_link_libraries(restock_update shop)
# target_link_libraries(restocking_suggestion shop)

# add_executable(MAIN src/main.cpp)
# target_link_libraries(MAIN PUBLIC shopinventory_ui::shopinventory_ui)