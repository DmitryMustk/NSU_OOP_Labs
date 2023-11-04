#include "wav_file.h"

WAVSample::WAVSample(): value(0) {}

WAVSample::WAVSample(int16_t val): value(val) {}

WAVSample& WAVSample::operator+=(const WAVSample& other) {
    value = (value + other.value) / 2;
    return *this;
}

void WAVSample::mute() {
    value = 0;
}

WAVFile::WAVFile() {
    filename_ = "";
    samples = {};
    header = WAVHeader();
}

WAVFile::WAVFile(const std::string& filename) {
    filename_ = filename;
    std::ifstream file(filename, std::ios::binary);
    if(!file.is_open())
        throw std::runtime_error("Failed to open file.");
    file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));
    if(!is_header_valid()) {
        file.close();
        throw std::runtime_error("Wrong file format.");
    }
    samples.resize(header.subchunk2_size / 2);
    file.read(reinterpret_cast<char*>(samples.data()), header.subchunk2_size);

    file.close();
}

bool WAVFile::is_header_valid() {
    if (std::string(header.chunk_id, 4) != "RIFF" ||
        std::string(header.format, 4) != "WAVE" ||
        header.audio_format != 1 ||
        header.num_channels != 1 ||
        header.sample_rate != 44100 ||
        header.bits_per_sample != 16) {

        std::cerr << "Unsupported WAV format." << std::endl;
        return false;
    }
    return true;
}

bool WAVFile::save_file(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if(!file.is_open()){
        std::cerr << "Failed to open file for writing " << filename << std::endl;
        return false;
    }
    header.chunk_size = 36 + header.subchunk2_size;
    header.byte_rate = header.sample_rate * header.num_channels * (header.bits_per_sample / 8);
    header.block_align = header.num_channels * (header.bits_per_sample / 8);

    file.write(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

    for(const auto& sample: samples) {
        file.write(reinterpret_cast<const char*>(&sample.value), sizeof(int16_t));
    }

    file.close();
    return true;
}
uint32_t WAVFile::get_sample_rate() {
    return header.sample_rate;
}
void WAVFile::set_sample_rate(const uint32_t sample_rate) {
    if(sample_rate < 22050 || sample_rate > 96000)
        throw std::runtime_error("Wrong sample_rate value, please use less speed_multiplier");
    header.sample_rate = sample_rate;
}
uint16_t WAVFile::get_bits_per_sample() {
    return header.bits_per_sample;
}
void WAVFile::set_byte_rate(const uint32_t byte_rate) {
    const uint32_t base_byte_rate = header.num_channels * header.bits_per_sample / 8;
    if(byte_rate < 22050 * base_byte_rate || byte_rate > 92000 * base_byte_rate)
        throw std::runtime_error("Wrong byte_rate value, please use less speed_multiplier");
    header.byte_rate = byte_rate;
}
