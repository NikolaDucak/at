cmake_minimum_required(VERSION 3.14)

project(at
    LANGUAGES CXX
    VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --------------------------------- boost -------------------------------- #

find_package(Boost 1.40 COMPONENTS timer REQUIRED)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost Not found")
endif()

# ----------------------------------- at --------------------------------- #

add_executable(at
    ./src/main.cpp
    ./src/tui.cpp
    ./src/at.cpp
)

target_link_libraries(at 
  PRIVATE
    ncurses
    Boost::timer
)
