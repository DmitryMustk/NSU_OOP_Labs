#ifndef LAB2_MUTE_CONVERTER_H
#define LAB2_MUTE_CONVERTER_H
#include "converter.h"
class MuteConverter : public Converter {
   public:
    void convert(std::vector<std::shared_ptr<WAVFile>>& files,
                 std::vector<std::pair<size_t, size_t>> time_interval) override;
};
#endif  //LAB2_MUTE_CONVERTER_H
