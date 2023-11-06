#ifndef SOUNDPROCESSOR_CLI_PARSER_H
#define SOUNDPROCESSOR_CLI_PARSER_H
#include <string>
#include <vector>

class CliParser {
   public:
    CliParser(int argc, char** argv);
    std::vector<std::string> get_args();
    std::string get_flags();
    void print_help();

   private:
    std::vector<std::string> args;
    std::string flags;
};
#endif  //SOUNDPROCESSOR_CLI_PARSER_H
