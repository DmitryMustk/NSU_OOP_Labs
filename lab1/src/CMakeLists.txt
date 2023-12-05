cmake_minimum_required(VERSION 3.10)
project(lab4_task3)

set(exe_name ${PROJECT_NAME})
set(test_name flat_map_test)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_library(corelib OBJECT flat_map.cpp)

add_executable(${exe_name} main.cpp)
target_link_libraries(${exe_name} PRIVATE corelib)

find_package(GTest REQUIRED)
target_include_directories(${exe_name} PRIVATE ${GTEST_INCLUDE_DIRS})

add_executable(${test_name} flat_map_test.cc)
target_link_libraries(${test_name} PRIVATE corelib ${GTEST_LIBRARIES} pthread)
target_include_directories(${test_name} PUBLIC ${GTEST_INCLUDE_DIRS})

enable_testing()
add_test(NAME MyTest COMMAND ${test_name})