#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct Config {
    struct Compiler {
        std::string name;
        std::string version;
        std::vector<std::string> flags;
    };

    struct DependencyOptions {
        bool header_only = false;
        bool multithreaded = false;
    };
    
    struct Dependency {
        std::string name;
        std::string version;
        // std::unordered_map<std::string, bool> options; // specially for rapidYML
        DependencyOptions options; // specially for YML-CPP
    };

    struct Toolchain {
        std::string build_generator;
        std::string cmake_minimum_required;
        std::string build_type;
        std::string pkg_manager;
        std::string version;
        std::string host;
        std::string build;
    };


    Config::Compiler m_compiler;
    std::vector<Config::Dependency> m_dependencies;
    std::vector<Config::Toolchain> m_toolchains;
};



namespace cmh{

    class IYMLConfigParser {
    public:
        virtual ~IYMLConfigParser() = default;
        virtual bool parse() = 0; // yml parse() 
        virtual const Config& getConfig() const = 0;
        virtual const Config::Compiler& getCompiler() const = 0;
        virtual const std::vector<Config::Dependency>& getDependencies() const = 0;
        virtual const std::vector<Config::Toolchain>& getToolchains() const = 0;
        virtual std::string getLastError() const = 0;
    };

} // namespace cmh::