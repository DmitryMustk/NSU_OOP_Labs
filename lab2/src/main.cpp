#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

class WAVHeader {
   public:
    char chunk_id[4];
    uint32_t chunk_size;
    char format[4];
    char subchunk1_id[4];
    uint32_t subchunk1_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
    char subchunk2_id[4];
    uint32_t subchunk2_size;
};

class WAVSample {
   public:
    int16_t value;

    WAVSample() : value(0) {}
    WAVSample(int16_t val) : value(val) {}

    WAVSample& operator+=(const WAVSample& other) {
        value = (value + other.value) / 2;
        return *this;
    }

    void mute() {
        value = 0;
    }
};

class WAVFile {
   public:
    WAVHeader header;
    std::vector<WAVSample> samples;

    bool load_file(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return false;
        }

        file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

        if (std::string(header.chunk_id, 4) != "RIFF" ||
            std::string(header.format, 4) != "WAVE" ||
            header.audio_format != 1 ||
            header.num_channels != 1 ||
            header.sample_rate != 44100 ||
            header.bits_per_sample != 16) {
            std::cerr << "Unsupported WAV format." << std::endl;
            return false;
        }

        samples.resize(header.subchunk2_size / 2);
        file.read(reinterpret_cast<char*>(samples.data()), header.subchunk2_size);

        file.close();
        return true;
    }

    void mute(int start_sample, int end_sample) {
        for (int i = start_sample; i < end_sample && i < samples.size(); ++i) {
            samples[i].mute();
        }
    }

    bool save_file(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing: " << filename << std::endl;
            return false;
        }

        header.chunk_size = 36 + header.subchunk2_size;
        header.byte_rate = header.sample_rate * header.num_channels * (header.bits_per_sample / 8);
        header.block_align = header.num_channels * (header.bits_per_sample / 8);

        file.write(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

        for (const auto& sample : samples) {
            file.write(reinterpret_cast<const char*>(&sample.value), sizeof(int16_t));
        }

        file.close();
        return true;
    }


    void mix(const WAVFile& other, int start_sample) {
        for (int i = start_sample; i < samples.size() && i - start_sample < other.samples.size(); ++i) {
            samples[i] += other.samples[i - start_sample];
        }
    }

};

int main(int argc, char* argv[]) {
    const char* input1_file = "input1.wav";
    const char* input2_file = "input2.wav";

    const char* output1_file = "input1_muted.wav";
    const char* output2_file = "input2_muted.wav";
    const char* output_mix_file = "input_mix.wav";

    WAVFile input1, input2, output1, output2, output_mix;

    if (input1.load_file(input1_file) && input2.load_file(input2_file)) {

        output1 = input1;
        output2 = input2;
        output1.mute(10 * 44100, 30 * 44100);
        output2.mute(10 * 44100, 30 * 44100);

        if (output1.save_file(output1_file) && output2.save_file(output2_file)) {

            output_mix = input1;
            output_mix.mix(input2, 0);

            if (output_mix.save_file(output_mix_file)) {
                std::cout << "Conversion completed successfully." << std::endl;
            } else {
                std::cerr << "Failed to save mix file." << std::endl;
                return 1;
            }
        } else {
            std::cerr << "Failed to save muted files." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Failed to load input files." << std::endl;
        return 1;
    }

    return 0;
}
