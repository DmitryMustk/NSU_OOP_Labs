#include "mix_converter.h"
#include "converter.h"

void MixConverter::convert(std::vector<std::shared_ptr<WAVFile>>& files,
                           std::vector<std::pair<size_t, size_t>> time_intervals) {
    if (files.size() != time_intervals.size() * 2)
        throw std::runtime_error("Wrong size of args in mute_converter");

    size_t files_size = files.size();
    for (size_t i = 0; i < files_size; i += 2) {
        mix_files(*files[i], *files[i + 1], time_intervals[i]);
    }
}

void MixConverter::mix_files(WAVFile& file1, WAVFile& file2, std::pair<size_t, size_t> time_interval) {
    size_t file1_size = file1.samples.size();
    size_t file2_size = file2.samples.size();
    for (size_t i = time_interval.first; i < file1_size && i - time_interval.first < file2_size; ++i) {
        file1.samples[i] += file2.samples[i - time_interval.first];
    }
}
