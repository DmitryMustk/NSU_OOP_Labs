#ifndef SOUNDPROCESSOR_MIX_CONVERTER_H
#define SOUNDPROCESSOR_MIX_CONVERTER_H
#include "converter.h"

class MixConverter : public Converter {
   public:
    void convert(std::vector<std::shared_ptr<WAVFile>>& files, std::pair<size_t, size_t> time_intervals) override;
};
#endif  //SOUNDPROCESSOR_MIX_CONVERTER_H
