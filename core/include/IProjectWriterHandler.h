
// File: include/IProjectWriterHandler.h
#pragma once
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace cmh
{
    class IProjectWriterHandler {
    public:
        virtual ~IProjectWriterHandler() = default;
        virtual void writeInFile(const std::string& dirName, const fs::path& filename, const std::string& projectName) = 0;
    private:
        virtual void writeInHeaderFile(const fs::path& filename) = 0;
        virtual void writeInSourceFile(const fs::path& filename, const std::string& projectName) = 0;
        
    };

}