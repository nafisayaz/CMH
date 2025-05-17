
// File: include/ProjectBuilder.h
#pragma once
#include "IProjectBuilder.h"

namespace cmh
{
    class ProjectBuilder : public IProjectBuilder {
    public:
        explicit ProjectBuilder(const Project& project);
        bool create() override;
    private:
        // void createDir(std::string name) override;
        void createDirectories(const std::vector<Project::Directory>& dirs, const std::filesystem::path& basePath) override;
        bool createFile(const std::filesystem::path& filepath) override;
        fs::path generateFilePath(const std::string& dirName, const fs::path& dirPath, const std::string& file) override;
        void handleDirectory(const Project::Directory& dir, const fs::path& basePath) override;
        void createDirectoryIfNotExists(const fs::path& dirPath) override;
        void createFilesInDirectory(const std::string& dirName, const std::vector<std::string>& files, const fs::path& dirPath) override;

        const Project m_project;

    };

} // namespace cmh::
