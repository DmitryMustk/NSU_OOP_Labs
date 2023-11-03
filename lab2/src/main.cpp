#include <iostream>

#include "wav_file.h"
#include "mute_converter.h"
#include "mix_converter.h"

//TODO: Create a Converter classes
//TODO: Create a Nightcore_mix Converter
//TODO: add an -h
//TODO: create CLI Parser
//TODO: create Instruction File Parser

int main() {
    const std::string input1_file = "input1.wav";
    const std::string  input2_file = "input2.wav";
    const std::string output1_file = "input1_mixed.wav";

    std::vector<std::shared_ptr<WAVFile>> files;
    std::vector<std::pair<size_t, size_t>> time_intervals;

    files.push_back(std::make_shared<WAVFile>(input1_file));
    files.push_back(std::make_shared<WAVFile>(input2_file));
    time_intervals.emplace_back(44100 * 10, 44100 * 30);

    MuteConverter mc;
    MixConverter mix_converter;
    mix_converter.convert(files, time_intervals);
//    mc.convert(files, time_intervals);

    if (!files.empty())
        files[0]->save_file(output1_file);

    return 0;
}

