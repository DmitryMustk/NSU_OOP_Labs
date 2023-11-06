#include "factory.h"
#include "mix_converter.h"
#include "mute_converter.h"
#include "nightcore_converter.h"
#include "wav_file.h"

#include <string>

void Factory::process_instructions(std::vector<std::string> files, std::string output_name,
                                   std::string instructions_txt) {

    std::vector<std::shared_ptr<WAVFile>> wav_files;
    wav_files.push_back(std::make_shared<WAVFile>(files[0]));

    Instructions instructions(instructions_txt);
    for (const auto& instruction : instructions.data) {
        std::unique_ptr<Converter> converter = create_converter(instruction.converter);
        std::pair<size_t, size_t> time_interval = std::make_pair(0, 0);

        if (instruction.converter == "mix") {
            size_t mix_file_index = std::stoi(instruction.args[0].substr(1));
            wav_files.push_back(std::make_shared<WAVFile>(files[mix_file_index - 1]));
            time_interval.second = std::stoi(instruction.args[1]) * wav_files[0]->get_sample_rate();
            converter->convert(wav_files, time_interval);
        }

        else if (instruction.converter == "mute") {
            time_interval.first = std::stoi(instruction.args[0]) * wav_files[0]->get_sample_rate();
            time_interval.second = std::stoi(instruction.args[1]) * wav_files[0]->get_sample_rate();
            converter->convert(wav_files, time_interval);
        }

        else if (instruction.converter == "nightcore") {
            float speed_mult = std::stof(instruction.args[0]);
            int semitones = std::stoi(instruction.args[1]);
            std::unique_ptr<NightcoreConverter> nightcore_converter = std::make_unique<NightcoreConverter>();
            std::shared_ptr<NightcoreConverter> shared_nightcore_converter = std::move(nightcore_converter);
            shared_nightcore_converter->convert(wav_files, time_interval, speed_mult, semitones);
        }
    }
    wav_files[0]->save_file(output_name);
}

std::unique_ptr<Converter> ConcreteFactory::create_converter(const std::string& converter) {
    if (converter == "mix")
        return std::make_unique<MixConverter>();
    else if (converter == "mute")
        return std::make_unique<MuteConverter>();

    return std::make_unique<NightcoreConverter>();
}
