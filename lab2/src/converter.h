#ifndef LAB2_CONVERTER_H
#define LAB2_CONVERTER_H
#include <memory>
#include "wav_file.h"

class Converter {
   public:
    virtual void convert(std::vector<std::shared_ptr<WAVFile>>& files,
                         std::vector<std::pair<size_t, size_t>> time_intervals) = 0;
};
#endif  //LAB2_CONVERTER_H
