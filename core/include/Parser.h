#pragma once

#include "IParser.h"
#include <nlohmann/json.hpp>
#include <fstream>

namespace cmh
{

    class JsonProjectManifestParser : public cmh::IParser {
    public:
        explicit JsonProjectManifestParser(const std::string& path);
        bool parse() override;
        const Project& getProject() const override;
        const std::vector<Project::Directory>& getSubdirectories() const override;
    
        std::string getLastError() const override;
    
    private:
        std::string m_path;
        std::string m_lastError;
        Project m_project;
    
        void parseDirectories(const nlohmann::json& jsonDirs, std::vector<Project::Directory>& dirs);
    };
} // namespace cmh::
