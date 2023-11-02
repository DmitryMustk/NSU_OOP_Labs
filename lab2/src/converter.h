#ifndef LAB2_CONVERTER_H
#define LAB2_CONVERTER_H
#include "wav_file.h"
#include <memory>

class Converter{
   public:
    virtual void convert(std::vector<std::shared_ptr<WAVFile>>& files) = 0;
};
#endif  //LAB2_CONVERTER_H
