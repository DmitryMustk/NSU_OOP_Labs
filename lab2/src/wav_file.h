#ifndef LAB2_WAV_FILE_H
#define LAB2_WAV_FILE_H

#include <iostream>
#include <vector>
#include <fstream>
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

    WAVSample();
    WAVSample(int16_t val);

    WAVSample& operator+=(const WAVSample& other);

    void mute();
};

class WAVFile {
   public:
    WAVHeader header;
    std::vector<WAVSample> samples;

    bool load_file(const std::string& filename);
    void mute(size_t start_sample, size_t end_sample);
    bool save_file(const std::string& filename);
    void mix(const WAVFile& other, size_t start_sample);
   private:
    bool is_header_valid();
};
#endif  //LAB2_WAV_FILE_H
