#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// --------------------------------------------
// 🔹 Interface for loading configuration data
// --------------------------------------------
class IConfigLoader {
public:
    virtual json load(const std::string& filename) const = 0;
    virtual ~IConfigLoader() = default;
};

// -------------------------------------------------
// 🔹 Concrete class for loading JSON configuration
// -------------------------------------------------
class JsonConfigLoader : public IConfigLoader {
public:
    json load(const std::string& filename) const override {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Error: Could not open JSON file: " + filename);
        }
        
        json jsonData;
        file >> jsonData;
        return jsonData;
    }
};

// -----------------------------------------------
// 🔹 Interface for extracting project information
// -----------------------------------------------
class IProjectParser {
public:
    virtual std::string getProjectName(const json& data) const = 0;
    virtual std::vector<std::string> getDirectories(const json& data) const = 0;
    virtual std::vector<std::string> getSubDirectories(const json& directory) const = 0;
    virtual ~IProjectParser() = default;
};

// ------------------------------------------------
// 🔹 Concrete class for parsing JSON project data
// ------------------------------------------------
class JsonProjectParser : public IProjectParser {
public:
    std::string getProjectName(const json& data) const override {
        return data.value("project", "Unknown Project");
    }

    std::vector<std::string> getDirectories(const json& data) const override {
        std::vector<std::string> directories;
        if (data.contains("directories") && data["directories"].is_array()) {
            for (const auto& dir : data["directories"]) {
                directories.push_back(dir["name"].get<std::string>());
            }
        }
        return directories;
    }

    std::vector<std::string> getSubDirectories(const json& directory) const override {
        std::vector<std::string> subDirs;
        if (directory.contains("sub-directories") && directory["sub-directories"].is_array()) {
            for (const auto& subdir : directory["sub-directories"]) {
                subDirs.push_back(subdir["name"].get<std::string>());
            }
        }
        return subDirs;
    }
};

// ----------------------------------------------
// 🔹 High-level module that depends on Abstraction (DIP)
// ----------------------------------------------
class ProjectDataProcessor {
private:
    std::shared_ptr<IConfigLoader> configLoader;
    std::shared_ptr<IProjectParser> parser;

public:
    ProjectDataProcessor(std::shared_ptr<IConfigLoader> loader, std::shared_ptr<IProjectParser> projectParser)
        : configLoader(std::move(loader)), parser(std::move(projectParser)) {}

    void processProjectData(const std::string& filename) const {
        json jsonData = configLoader->load(filename);

        std::cout << "Project Name: " << parser->getProjectName(jsonData) << "\n";
        std::cout << "Directories:\n";

        for (const auto& dir : jsonData["directories"]) {
            std::cout << "  - " << dir["name"].get<std::string>() << "\n";

            auto subDirs = parser->getSubDirectories(dir);
            if (!subDirs.empty()) {
                std::cout << "    Sub-directories:\n";
                for (const auto& subdir : subDirs) {
                    std::cout << "      - " << subdir << "\n";
                }
            }
        }
    }
};

// ----------------------------------------------
// 🔹 Main function
// ----------------------------------------------
int main() {
    try {
        std::shared_ptr<IConfigLoader> jsonLoader = std::make_shared<JsonConfigLoader>();
        std::shared_ptr<IProjectParser> jsonParser = std::make_shared<JsonProjectParser>();

        ProjectDataProcessor processor(jsonLoader, jsonParser);
        processor.processProjectData("project_manifest.json");  // Change to your file
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
