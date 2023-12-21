cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

project(task1)

set(exe_name ${PROJECT_NAME})
# add_library(corelib OBJECT 

# )
add_executable(${exe_name} src/main.cpp)
# target_link_libraries(${exe_name} corelib)

