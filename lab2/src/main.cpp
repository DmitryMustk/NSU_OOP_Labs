#include "cli_parser.h"
#include "factory.h"

int main(int argc, char** argv) {
    CliParser cli_parser(argc, argv);
    std::vector<std::string> args = cli_parser.get_args();
    std::string flags = cli_parser.get_flags();
    if (flags == "-h" || flags == "--help") {
        cli_parser.print_help();
        return 0;
    }

    std::string output_name = args[argc - 3];
    std::string instructions_txt = args[argc - 2];
    args.pop_back();

    ConcreteFactory factory;
    factory.process_instructions(args, output_name, instructions_txt);

    if (!system(("ffplay " + output_name).c_str()))
        throw std::runtime_error("Can't play the " + output_name + " file");
    return 0;
}
