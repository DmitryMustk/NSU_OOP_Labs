#ifndef SOUNDPROCESSOR_MIX_CONVERTER_H
#define SOUNDPROCESSOR_MIX_CONVERTER_H
#include "converter.h"

class MixConverter : Converter {
   public:
    void convert(std::vector<std::shared_ptr<WAVFile>>& files,
                 std::vector<std::pair<size_t, size_t>> time_intervals) override;

   private:
    void mix_files(WAVFile& file1, WAVFile& file2, std::pair<size_t, size_t> time_interval);
    size_t start_sample_;
    size_t end_sample_;
};
#endif  //SOUNDPROCESSOR_MIX_CONVERTER_H
