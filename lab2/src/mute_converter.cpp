#include "mute_converter.h"

void MuteConverter::convert(std::vector<std::shared_ptr<WAVFile>>& files,
                            std::vector<std::pair<size_t, size_t>> time_intervals) {
    if (files.size() != time_intervals.size())
        throw std::runtime_error("Wrong size of args in mute_converter");

    size_t files_size = files.size();
    for (size_t i = 0; i < files_size; ++i) {
        size_t samples_size = files[i]->samples.size();
        for (size_t j = time_intervals[i].first; j < time_intervals[i].second && j < samples_size; ++j) {
            files[i]->samples[j].mute();
        }
    }
}
