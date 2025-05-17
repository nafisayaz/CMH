
// File: include/ProjectWriterHandler.h
#pragma once
#include <string>
#include <filesystem>
#include "IProjectWriterHandler.h"

namespace fs = std::filesystem;

namespace cmh
{
    class ProjectWriterHandler : public IProjectWriterHandler {
    public:
        // ProjectWriterHandler() = default;
        virtual ~ProjectWriterHandler() = default;
        void writeInFile(const std::string& dirName, const fs::path& filename, const std::string& projectName) override;
    private:
        void writeInHeaderFile(const fs::path& filename) override;
        void writeInSourceFile(const fs::path& filename, const std::string& projectName) override;

    };

}