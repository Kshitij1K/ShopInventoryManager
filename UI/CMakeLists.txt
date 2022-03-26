cmake_minimum_required(VERSION 3.21)
project(shopinventory_ui CXX)

# First, create your library. List all the files one by one. Don't use globs
add_library(${PROJECT_NAME} 
  src/mainwindow.cpp
  src/models/stock_info_model.cpp
)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../StateMachine/build")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../Database/build")


# Then add an alias of your library to enable target syntax
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Automatically generate Qt ui and moc
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTOUIC_SEARCH_PATHS forms
)

# Then, include gnuinstalldir to get the platform's standard directories:
include(GNUInstallDirs)

# Then, carefully add your include directories. All of your `target_include_directories` must look like this
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # include directory in your build tree
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>       # include directory when installed
)

# Then, include Qt and link qt
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Widgets)

find_package(state_machine REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC state_machine::state_machine)

find_package(database REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC database::database)

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