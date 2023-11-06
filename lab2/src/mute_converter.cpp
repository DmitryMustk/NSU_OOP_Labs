#include "mute_converter.h"

void MuteConverter::convert(std::vector<std::shared_ptr<WAVFile>>& files, std::pair<size_t, size_t> time_interval) {

    size_t samples_size = files[0]->samples.size();
    for (size_t j = time_interval.first; j < time_interval.second && j < samples_size; ++j) {
        files[0]->samples[j].mute();
    }
}
