#ifndef SOUNDPROCESSOR_FACTORY_H
#define SOUNDPROCESSOR_FACTORY_H

#include "converter.h"
#include "instructions.h"

class Factory {
   public:
    virtual std::unique_ptr<Converter> create_converter(const std::string& converter) = 0;
    void process_instructions(std::vector<std::string> files, std::string output_name, std::string instructions_txt);
};

class ConcreteFactory : public Factory {
   public:
    std::unique_ptr<Converter> create_converter(const std::string& converter) override;
};

#endif  //SOUNDPROCESSOR_FACTORY_H
