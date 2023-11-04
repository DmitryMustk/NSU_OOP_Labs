#include <cmath>

#include "nightcore_converter.h"

void NightcoreConverter::convert(std::vector<std::shared_ptr<WAVFile>>& files,
                                 std::vector<std::pair<size_t, size_t>> time_intervals) {
    convert(files, time_intervals, 1.25, 4);
}

void NightcoreConverter::convert(std::vector<std::shared_ptr<WAVFile>>& files,
                                 std::vector<std::pair<size_t, size_t>> time_intervals, const float speed_multiplier,
                                 const int pitch_multiplier) {
    speed_up(files, speed_multiplier);
    pitch(files, pitch_multiplier);
}
void NightcoreConverter::speed_up(std::vector<std::shared_ptr<WAVFile>>& files, const float speed_mult) {
    for (size_t j = 0; j < files.size(); ++j) {
        const int sample_count = files[j]->samples.size();
        const size_t new_sample_count = static_cast<size_t>(sample_count / speed_mult);

        std::vector<WAVSample> new_samples;
        for (size_t i = 0; i < new_sample_count; ++i) {
            size_t old_index = static_cast<size_t>(i * speed_mult);
            new_samples.push_back(files[j]->samples[old_index]);
        }
        files[j]->samples = new_samples;

        files[j]->set_subchunk2_size(new_sample_count * sizeof(int16_t));
        files[j]->set_chunk_size(files[j]->get_subchunk2_size() + 36);
        files[j]->set_byte_rate(files[j]->get_sample_rate() * files[j]->get_bits_per_sample() / 8);
    }
}
void NightcoreConverter::pitch(std::vector<std::shared_ptr<WAVFile>>& files, const int semitones) {
    for (size_t j = 0; j < files.size(); ++j) {
        const double pitch_factor = pow(2.0, static_cast<double>(semitones) / 12.0);
        std::vector<WAVSample> new_samples;
        double position = 0.0;

        for (size_t i = 0; i < files[j]->samples.size(); ++i) {
            position += pitch_factor;
            size_t index1 = static_cast<int>(floor(position));
            size_t index2 = static_cast<int>(ceil(position));
            double fract = position - index1;

            if (index2 < files[j]->samples.size()) {
                int16_t interpol_sample = static_cast<int16_t>((1.0 - fract) * files[j]->samples[index1].value +
                                                               fract * files[j]->samples[index2].value);
                new_samples.push_back(WAVSample(interpol_sample));
            }
        }
        files[j]->samples = new_samples;
        files[j]->set_subchunk2_size(new_samples.size() * sizeof(int16_t));
        files[j]->set_chunk_size(files[j]->get_subchunk2_size() + 36);
        files[j]->set_byte_rate(files[j]->get_sample_rate() * files[j]->get_bits_per_sample() / 8);

    }
}
