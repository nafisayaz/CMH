#include "Parser.h"

cmh::JsonProjectManifestParser::JsonProjectManifestParser(const std::string& path)
    : m_path(path) {}

bool cmh::JsonProjectManifestParser::parse() {
    std::ifstream file(m_path);
    if (!file.is_open()) {
        m_lastError = "Unable to open file: " + m_path;
        return false;
    }

    nlohmann::json j;
    try {
        file >> j;
    } catch (const std::exception& e) {
        m_lastError = e.what();
        return false;
    }

    try {
        const auto& jproject = j.at("project");

        m_project.name = jproject.at("name");
        m_project.version = jproject.at("version");
        m_project.language = jproject.at("language");
        m_project.filenames = jproject.at("filename").get<std::vector<std::string>>();

        parseDirectories(jproject.at("directories"), m_project.m_directories);
    } catch (const std::exception& e) {
        m_lastError = std::string("Parsing error: ") + e.what();
        return false;
    }

    return true;
}

void cmh::JsonProjectManifestParser::parseDirectories(const nlohmann::json& jsonDirs, std::vector<Project::Directory>& dirs) {
    for (const auto& jdir : jsonDirs) {
        Project::Directory dir;
        dir.name = jdir.at("name");
        dir.filenames = jdir.at("filename").get<std::vector<std::string>>();

        if (jdir.contains("sub-directories")) {
            parseDirectories(jdir.at("sub-directories"), dir.subdirectories);
        }

        dirs.push_back(std::move(dir));
    }
}

const Project& cmh::JsonProjectManifestParser::getProject() const {
    return m_project;
}

const std::vector<Project::Directory>& cmh::JsonProjectManifestParser::getSubdirectories() const {
    return m_project.m_directories;
}


std::string cmh::JsonProjectManifestParser::getLastError() const {
    return m_lastError;
}
