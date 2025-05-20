#include <iostream>
#include <fstream>
#include <memory>
#include "ConfigValidator.h"

cmh::ConfigValidator::ConfigValidator(const Config& config)
    :m_config(config) {}


bool cmh::ConfigValidator::supportValidate(){
    std::cout << "__func__ : " << __func__ << "\n";
    return true;
}
