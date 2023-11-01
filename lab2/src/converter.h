#ifndef LAB2_CONVERTER_H
#define LAB2_CONVERTER_H
#include "wav_file.h"
class Converter{
   public:
    virtual void convert(WAVFile& wav) = 0;
};
#endif  //LAB2_CONVERTER_H
