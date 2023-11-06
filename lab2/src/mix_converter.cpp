#include "mix_converter.h"
#include "converter.h"

void MixConverter::convert(std::vector<std::shared_ptr<WAVFile>>& files, std::pair<size_t, size_t> time_interval) {
    size_t file1_size = files[0]->samples.size();
    size_t file2_size = files[1]->samples.size();
    for (size_t i = time_interval.first; i < file1_size && i < file2_size && i < time_interval.second; ++i) {
        files[0]->samples[i] += files[1]->samples[i - time_interval.first];
    }
}
