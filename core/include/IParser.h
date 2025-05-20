#pragma once
#include <string>
#include <vector>
// #include "cmh_info.h"

struct Project {
    std::string name;
    std::string version;
    std::string language;
    std::vector<std::string> filenames;

    struct Directory {
        std::string name;
        std::vector<std::string>    filenames;
        std::vector<Directory>      subdirectories;
    };

    std::vector<Project::Directory> m_directories;
};


namespace cmh{

    class IParser {
    public:
        virtual ~IParser() = default;
        virtual bool parse() = 0; // Json & yml parse() 
        virtual const Project& getProject() const = 0;
        virtual const std::vector<Project::Directory>& getSubdirectories() const = 0;
        virtual std::string getLastError() const = 0;
    };

} // namespace cmh::