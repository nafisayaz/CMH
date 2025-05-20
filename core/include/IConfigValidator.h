// File: include/IConfigValidator.h
#pragma once
#include <string>
#include <filesystem>
#include "IYMLConfigParser.h"

namespace fs = std::filesystem;

namespace cmh
{
    class IConfigValidator {
    public:
        IConfigValidator()=default;
        ~IConfigValidator()=default;
        virtual bool supportValidate() = 0;
    private:

    };
}