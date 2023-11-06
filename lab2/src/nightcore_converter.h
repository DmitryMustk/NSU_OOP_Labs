#ifndef SOUNDPROCESSOR_NIGHTCORE_CONVERTER_CPP_H
#define SOUNDPROCESSOR_NIGHTCORE_CONVERTER_CPP_H
#include "converter.h"

class NightcoreConverter : public Converter {
   public:
    void convert(std::vector<std::shared_ptr<WAVFile>>& files, std::pair<size_t, size_t> time_interval);
    void convert(std::vector<std::shared_ptr<WAVFile>>& files, std::pair<size_t, size_t> time_interval,
                 const float speed_multiplier, const int pitch_multiplier);

   private:
    void speed_up(std::vector<std::shared_ptr<WAVFile>>& files, const float speed_mult);
    void pitch(std::vector<std::shared_ptr<WAVFile>>& files, const int semitones);
};

#endif  //SOUNDPROCESSOR_NIGHTCORE_CONVERTER_CPP_H
