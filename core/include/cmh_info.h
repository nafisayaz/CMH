#pragma once
#include <string>
#include <vector>

struct ProjectInfo {
    std::string name;
    std::string version;
    std::string language;
    std::vector<std::string> filenames;
};

struct Directory {
    std::string name;
    std::vector<std::string> filenames;
    std::vector<Directory> subdirectories;
};


