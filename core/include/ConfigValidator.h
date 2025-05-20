// File: include/ConfigValidator.h
#pragma once
#include <string>
#include <filesystem>
#include "IConfigValidator.h"

namespace fs = std::filesystem;

namespace cmh
{
    class ConfigValidator : public IConfigValidator{
    public:
        explicit ConfigValidator(const Config& config);
        ~ConfigValidator()=default;
        virtual bool supportValidate() override;
    private:
        const Config m_config;
    };
}