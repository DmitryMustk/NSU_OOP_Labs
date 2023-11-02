#include <iostream>

#include "wav_file.h"
#include "mute_converter.h"

//TODO: Create a Converter classes
//TODO: Create a Nightcore_mix Converter
//TODO: add an -h
//TODO: create CLI Parser
//TODO: create Instruction File Parser

int main() {
    const std::string input1_file = "input1.wav";
    const std::string output1_file = "input1_muted.wav";

    std::vector<std::shared_ptr<WAVFile>> files;
    files.push_back(std::make_shared<WAVFile>(input1_file));

    MuteConverter mc(441000, 30 * 44100);
    mc.convert(files);

    if (!files.empty())
        files[0]->save_file(output1_file);

    return 0;
}

