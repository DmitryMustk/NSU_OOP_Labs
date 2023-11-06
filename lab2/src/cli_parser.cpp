#include "cli_parser.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

CliParser::CliParser(int argc, char** argv) {
    for (size_t i = 1; i < argc; ++i) {
        std::string tmp = argv[i];
        if (tmp == "-h" || tmp == "--help") {
            flags = tmp;
            return;
        }
        args.push_back(tmp);
    }
    if(args.size() < 3)
        throw std::runtime_error("Wrong number of args to SoundProcessor, please run with -h");
}

std::vector<std::string> CliParser::get_args() {
    return args;
}

std::string CliParser::get_flags() {
    return flags;
}

void CliParser::print_help() {
    std::ifstream help_file("../help.txt");
    if (!help_file.is_open())
        throw std::runtime_error("Failed to open help file");
    std::string line;
    while (std::getline(help_file, line))
        std::cout << line << std::endl;

    help_file.close();
}
