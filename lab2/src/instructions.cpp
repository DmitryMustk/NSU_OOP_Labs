#include "instructions.h"

#include <fstream>
#include <sstream>

Instructions::Instructions(const std::string& filename) {
    std::ifstream input(filename);
    if (!input.is_open())
        throw std::runtime_error("Can not open the instructions file");

    std::string line;
    while (std::getline(input, line)) {
        std::stringstream str_stream(line);

        if(line == "")
            continue;

        std::string converter;
        str_stream >> converter;

        if (converter != "mute" && converter != "mix" && converter != "nightcore") {
            input.close();
            throw std::runtime_error("Wrong instructions file format, please use -h to get help");
        }

        std::vector<std::string> args;
        size_t num_args = 2;

        for (size_t i = 0; i < num_args; ++i) {
            std::string tmp;
            if (!(str_stream >> tmp)) {
                input.close();
                throw std::runtime_error("Wrong instructions file format, please use -h to get help");
            }
            args.push_back(tmp);
        }

        data.push_back(Instruction{converter, args});
    }
    input.close();
}
