#include <iostream>
#include <memory>

#include "Parser.h"
#include "ProjectBuilder.h"

int main() {
    const std::string filePath = "../project.json";

    std::unique_ptr<cmh::IParser> parser = std::make_unique<cmh::JsonProjectManifestParser>(filePath);

    if (!parser->parse()) {
        std::cerr << "Failed to parse manifest: " << parser->getLastError() << std::endl;
        return 1;
    }

    // ✅ Clean, safe, no casting
    const Project& project = parser->getProject();
    std::cout << "Project: " << project.name << "\n"
              << "Version: " << project.version << "\n"
              << "Language: " << project.language << "\n";

    std::cout << "Source files: ";
    for (const auto& file : project.filenames)
        std::cout << file << " ";
    std::cout << "\n";

    const auto& directories = parser->getSubdirectories();
    for (const auto& dir : directories) {
        std::cout << "Directory: " << dir.name << "\n";
        for (const auto& file : dir.filenames)
            std::cout << "  File: " << file << "\n";
    }


    std::unique_ptr<cmh::IProjectBuilder> project_builder =  std::make_unique<cmh::ProjectBuilder>(project);
    project_builder->create();
    

    return 0;
}
