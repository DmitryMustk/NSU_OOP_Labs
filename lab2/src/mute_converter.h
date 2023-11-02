#ifndef LAB2_MUTE_CONVERTER_H
#define LAB2_MUTE_CONVERTER_H
#include "converter.h"
class MuteConverter: public Converter{
   public:
    MuteConverter(size_t start_sample, size_t end_sample);
    void convert(std::vector<std::shared_ptr<WAVFile>>& files) override;
   private:
    size_t start_sample_;
    size_t end_sample_;
};
#endif  //LAB2_MUTE_CONVERTER_H
