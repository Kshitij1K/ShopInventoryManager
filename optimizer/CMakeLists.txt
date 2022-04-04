cmake_minimum_required(VERSION 3.14)
project(myproj VERSION 1.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  or-tools
  GIT_REPOSITORY https://github.com/google/or-tools.git
  GIT_TAG        master
)

# After the following call, the CMake targets defined by or-tools
# will be defined and available to the rest of the build
FetchContent_MakeAvailable(or-tools)

add_executable(optimizer optimizer.cpp)
target_link_libraries(optimizer ortools::ortools)