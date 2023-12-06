#include <iostream>

#include "flat_map.h"

int main(void) {
    FlatMap<std::pair<int, int>, std::string> student;
    student[std::make_pair(4, 4)] = "Ivan";
    student[std::make_pair(4, 4)] = "Petrov";
    student[std::make_pair(4, 4)] = "NSU";
    student[std::make_pair(4, 4)] = "FIT";
    student[std::make_pair(4, 4)] = "22204";
    // for(auto it = student.begin(); it != student.end(); ++it){
    //     std::cout << it->key << ": " << it->value << std::endl;
    // }
    return 0;
}
