/* ymlConfigParser.h*/

#pragma once

#include <unordered_map>
#include <fstream>

/* Rapidyml */
#include <ryml_std.hpp>
#include <ryml.hpp>

/* YML-CPP */
#include <yaml-cpp/yaml.h>


#include "IYMLConfigParser.h"

namespace cmh
{

    class YMLConfigParser : public cmh::IYMLConfigParser {
    public:
        explicit YMLConfigParser(const std::string& path);
        bool parse() override;
        const Config& getConfig() const override;
        const Config::Compiler& getCompiler() const override;
        const std::vector<Config::Dependency>& getDependencies() const override;
        const std::vector<Config::Toolchain>& getToolchains() const override;
    
        std::string getLastError() const override;
    
    private:
    /*PRIVATE FUNCTIONS*/
        void parseCompiler(const YAML::Node& compilerNode);
        void parseDependencies(const YAML::Node& depsNode);
        void parseToolchains(const YAML::Node& toolsNode);

    /* DATA MEMBERS*/
        std::string m_path;
        std::string m_lastError;
        Config m_config;
    };

} // namespace cmh::
