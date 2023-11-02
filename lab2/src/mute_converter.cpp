#include "mute_converter.h"

MuteConverter::MuteConverter(size_t start_sample, size_t end_sample) {
    start_sample_ = start_sample;
    end_sample_ = end_sample;
}

void MuteConverter::convert(std::vector<std::shared_ptr<WAVFile>>& files) {
    for (const auto& wav : files) {
        size_t samples_size = wav->samples.size();
        for (size_t i = start_sample_; i < end_sample_ && i < samples_size; ++i) {
            wav->samples[i].mute();
        }
    }
}

