#ifndef SOUNDPROCESSOR_INSTRUCTIONS_H
#define SOUNDPROCESSOR_INSTRUCTIONS_H
#include <string>
#include <vector>

class Instructions {
   public:
    struct Instruction {
        std::string converter;
        std::vector<std::string> args;
    };
    std::vector<Instruction> data;

    Instructions(const std::string& filename);
};

#endif  //SOUNDPROCESSOR_INSTRUCTIONS_H
