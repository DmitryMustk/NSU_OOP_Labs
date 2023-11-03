#ifndef LAB2_WAV_FILE_H
#define LAB2_WAV_FILE_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

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
    std::string filename_;
    std::vector<WAVSample> samples;

    WAVFile();
    WAVFile(const std::string& filename);
    bool save_file(const std::string& filename);
    void mix(const WAVFile& other, size_t start_sample);

   private:
    struct WAVHeader {
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

    WAVHeader header;
    struct FileAttributes {};
    bool is_header_valid();
};
#endif  //LAB2_WAV_FILE_H
