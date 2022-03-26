cmake_minimum_required(VERSION 3.10)
project(database)

add_definitions(-std=c++17)
set(CMAKE_BUILD_TYPE Release)

include_directories(include)

add_library(
  ${PROJECT_NAME} 
  src/database.cpp
  src/sqlite3.c
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

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
