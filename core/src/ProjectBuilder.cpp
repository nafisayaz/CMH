
// File: src/ProjectBuilder.cpp

#include <iostream>
#include <fstream>
#include <memory>
#include "ProjectBuilder.h"
#include "ProjectWriterHandler.h"

namespace fs = std::filesystem;

cmh::ProjectBuilder::ProjectBuilder(const Project& project)
    :m_project(project) {}

bool cmh::ProjectBuilder::create() {
    if (!fs::exists(m_project.name)) {
        fs::create_directory(m_project.name);
        std::cout << "Created root directory: " << m_project.name<<"\n";
        fs::path filePath = m_project.name;
        fs::path file = (m_project.filenames[0]+ ".cpp");
        filePath = filePath / file;
        createFile(filePath);
    }

    createDirectories(m_project.m_directories, m_project.name);

    return true;
}

fs::path cmh::ProjectBuilder::generateFilePath(const std::string& dirName, const fs::path& dirPath, const std::string& file) {
    return (dirName == "include") ? dirPath / (file + ".h") : dirPath / (file + ".cpp");
}

void cmh::ProjectBuilder::createDirectories(const std::vector<Project::Directory>& dirs, const fs::path& basePath) {
    for (const auto& dir : dirs) {
        handleDirectory(dir, basePath);
    }
}

void cmh::ProjectBuilder::handleDirectory(const Project::Directory& dir, const fs::path& basePath) {

    fs::path dirPath = basePath / dir.name;
    createDirectoryIfNotExists(dirPath);

    createFilesInDirectory(dir.name, dir.filenames, dirPath);

    if (!dir.subdirectories.empty()) {
        createDirectories(dir.subdirectories, dirPath);  // recursive call
    }
}

void cmh::ProjectBuilder::createDirectoryIfNotExists(const fs::path& dirPath) {
    if (!fs::exists(dirPath)) {
        fs::create_directories(dirPath);
        std::cout << "Created directory: " << dirPath << "\n";
    } else {
        std::cout << "Not created directory: " << dirPath << "\n";
    }
}

void cmh::ProjectBuilder::createFilesInDirectory(const std::string& dirName, const std::vector<std::string>& files, const fs::path& dirPath) {
    for (const auto& file : files) {
        fs::path filePath = generateFilePath(dirName, dirPath, file);
        if (createFile(filePath)) {
            std::unique_ptr<cmh::IProjectWriterHandler> writerHandler = std::make_unique<cmh::ProjectWriterHandler>();
            writerHandler->writeInFile(dirName, filePath, m_project.name);
        }
    }
}

bool cmh::ProjectBuilder::createFile(const fs::path& filepath) {
    if (!fs::exists(filepath)) {
        std::ofstream outfile(filepath);
        if (outfile) {
            std::cout << "Created file: " << filepath << "\n";

        } else {
            std::cerr << "Failed to create file: " << filepath << "\n";
            return false;
        }
    }
    return true;
}





