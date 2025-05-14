// config.h
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <toml++/toml.h>

namespace CMH {

struct ProjectConfig {
    std::string name;
    std::string version;
    friend std::ostream& operator<<(std::ostream& os, const ProjectConfig& projectConfig) {
        os << projectConfig.name << " " << projectConfig.version << "\n"; // Pretty print with indent of 4 spaces
        return os;
    }
};

struct CompilerConfig {
    std::string type;
    int version;
    std::vector<std::string> flags;
    friend std::ostream& operator<<(std::ostream& os, const CompilerConfig& compilerConfig) {
        os << compilerConfig.type << " " << compilerConfig.version << "\n"; // Pretty print with indent of 4 spaces
        int count = 0;
        for(const auto& flag: compilerConfig.flags){
            os << flag;
            if(count <= compilerConfig.flags.size())
                os << ", ";
        }
        return os;
    }
};

class ConfigManager {
public:
    virtual bool load(const std::string& filename)=0;

    virtual const ProjectConfig& getProject()=0;
    virtual const CompilerConfig& getCompiler()=0;


private:
    //data

};


class ConfigTOML : public ConfigManager{
    public:
        bool load(const std::string& filename);
    
        const ProjectConfig& getProject()override;
        const CompilerConfig& getCompiler()override;
    
    
    private:
        CMH::ProjectConfig m_project;
        CMH::CompilerConfig m_compiler;
    };
    


} // namespace config