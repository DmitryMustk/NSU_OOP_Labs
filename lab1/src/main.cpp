#include <iostream>

#include "flat_map.h"

int main(void) {
    FlatMap student;
    student["first_name"] = "Ivan";
    student["last_name"] = "Petrov";
    student["university"] = "NSU";
    //student["department"] = "FIT";
    student["group"] = "22204";
    std::cout << "Student: " << student["first_name"] << ' ' << student["last_name"] << ' ' << student["university"]
              << ' ' << student["group"] << '\n';
    return 0;
}
