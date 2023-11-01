#include <iostream>

#include "wav_file.h"
#include "mute_converter.h"

//TODO: Create a Converter classes
//TODO: Create a Nightcore_mix Converter
//TODO: add an -h
//TODO: create CLI Parser
//TODO: create Instruction File Parser

int main(void) {
    const std::string input1_file = "input1.wav";
//    const char* input2_file = "input2.wav";

    const std::string output1_file = "input1_muted.wav";
//    const char* output2_file = "input2_muted.wav";
//    const char* output_mix_file = "input_mix.wav";

    WAVFile input1(input1_file);
    WAVFile output1;
//    WAVFile input2,  output2, output_mix;
//    input1.load_file(input1_file);
    output1 = input1;
    MuteConverter mc(441000, 30 * 44100);
    mc.convert(output1);
    output1.save_file(output1_file);
//    if (input1.load_file(input1_file) && input2.load_file(input2_file)) {
//
//        output1 = input1;
//        output2 = input2;
//        output1.mute(10 * 44100, 30 * 44100);
//        output2.mute(10 * 44100, 30 * 44100);
//
//        if (output1.save_file(output1_file) && output2.save_file(output2_file)) {
//
//            output_mix = input1;
//            output_mix.mix(input2, 0);
//
//            if (output_mix.save_file(output_mix_file)) {
//                std::cout << "Conversion completed successfully." << std::endl;
//            } else {
//                std::cerr << "Failed to save mix file." << std::endl;
//                return 1;
//            }
//        } else {
//            std::cerr << "Failed to save muted files." << std::endl;
//            return 1;
//        }
//    } else {
//        std::cerr << "Failed to load input files." << std::endl;
//        return 1;
//    }

    return 0;
}
