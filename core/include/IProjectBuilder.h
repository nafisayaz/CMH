// File: include/IProjectBuilder.h
#pragma once
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "IParser.h"
// #include "cmh_info.h"

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace cmh
{
    class IProjectBuilder {
    public:
        IProjectBuilder() = default;
        virtual ~IProjectBuilder() = default;
        virtual bool create() = 0;
    private:
        // virtual void createDir(std::string name) = 0;
        virtual void createDirectories(const std::vector<Project::Directory>& dirs, const fs::path& basePath) = 0;
        virtual bool createFile(const fs::path& filepath) = 0;
        virtual fs::path generateFilePath(const std::string& dirName, const fs::path& dirPath, const std::string& file) = 0;
        virtual void handleDirectory(const Project::Directory& dir, const fs::path& basePath) = 0;
        virtual void createDirectoryIfNotExists(const fs::path& dirPath) = 0;
        virtual void createFilesInDirectory(const std::string& dirName, const std::vector<std::string>& files, const fs::path& dirPath) = 0;

    };
} // namespace cmh::
