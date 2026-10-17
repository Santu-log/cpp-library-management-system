cmake_minimum_required(VERSION 3.16)
project(LibraryManagementSystem VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(library_core
    src/Book.cpp src/User.cpp src/Admin.cpp src/Member.cpp src/Loan.cpp
    src/Library.cpp src/LibraryManagementSystem.cpp)
target_include_directories(library_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(MSVC)
    target_compile_options(library_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(library_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(library_management src/main.cpp)
target_link_libraries(library_management PRIVATE library_core)

include(CTest)
if(BUILD_TESTING)
    add_executable(library_tests tests/library_tests.cpp)
    target_link_libraries(library_tests PRIVATE library_core)
    add_test(NAME library_tests COMMAND library_tests)
endif()
