
#include <iostream>
#include <fstream>
#include <sstream>

#include "YMLConfigParser.h"


cmh::YMLConfigParser::YMLConfigParser(const std::string& path)
    :m_path(path) {}


    /****************************** YAML-CPP ********************************/
bool cmh::YMLConfigParser::parse() {
    try {
        YAML::Node root = YAML::LoadFile(m_path);

        parseCompiler(root["compiler"]);
        parseDependencies(root["dependencies"]);
        parseToolchains(root["toolchain"]);
    } catch (const YAML::Exception& e) {
        std::cerr << "YAML parsing error: " << e.what() << '\n';
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        return false;
    }

    return true;

#if 0
    YAML::Node root = YAML::LoadFile(m_path);
    // Compiler
    const auto& compiler = root["compiler"];
    m_config.m_compiler.name = compiler["name"].as<std::string>();
    m_config.m_compiler.version = compiler["version"].as<std::string>();
    m_config.m_compiler.flags = compiler["flags"].as<std::vector<std::string>>();

    // Dependencies
    for (const auto& dep : root["dependencies"]) {
        Config::Dependency d;
        d.name = dep["name"].as<std::string>();
        d.version = dep["version"].as<std::string>();
        if (dep["options"]) {
            if (dep["options"]["header_only"])
                d.options.header_only = dep["options"]["header_only"].as<bool>();
            if (dep["options"]["multithreaded"])
                d.options.multithreaded = dep["options"]["multithreaded"].as<bool>();
        }
        m_config.m_dependencies.push_back(std::move(d));
    }

    // Toolchains
    for (const auto& tool : root["toolchain"]) {
        Config::Toolchain t;
        if (tool["build_generator"])
            t.build_generator = tool["build_generator"].as<std::string>();
        if (tool["cmake_minimum_required"])
            t.cmake_minimum_required = tool["cmake_minimum_required"].as<std::string>();
        if (tool["build_type"])
            t.build_type = tool["build_type"].as<std::string>();

        if (tool["pkg_manager"])
            t.pkg_manager = tool["pkg_manager"].as<std::string>();
        if (tool["version"])
            t.version = tool["version"].as<std::string>();
        if (tool["host"])
            t.host = tool["host"].as<std::string>();
        if (tool["build"])
            t.build = tool["build"].as<std::string>();

        m_config.m_toolchains.push_back(std::move(t));
    }
#endif

}

void cmh::YMLConfigParser::parseCompiler(const YAML::Node& compilerNode){
    if (!compilerNode) {
        std::cerr << "Missing 'compiler' section in YAML.\n";
        return;
    }
    if (!compilerNode["name"] || !compilerNode["version"]) {
        std::cerr << "Missing required compiler fields: 'name' or 'version'.\n";
        return;
    }

    m_config.m_compiler.name = compilerNode["name"].as<std::string>();
    m_config.m_compiler.version = compilerNode["version"].as<std::string>();

    if (compilerNode["flags"])
        m_config.m_compiler.flags = compilerNode["flags"].as<std::vector<std::string>>();
    else {
        std::cerr << "Warning: 'compiler.flags' not specified. Defaulting to empty.\n";
        m_config.m_compiler.flags = {};
    }
}

void cmh::YMLConfigParser::parseDependencies(const YAML::Node& depsNode){
    if (!depsNode || !depsNode.IsSequence()) {
        std::cerr << "'dependencies' section is missing or malformed.\n";
        return;
    }

    for (const auto& dep : depsNode) {
        if (!dep["name"] || !dep["version"]) {
            std::cerr << "Warning: Dependency missing 'name' or 'version'. Skipping.\n";
            continue;
        }

        Config::Dependency d;
        d.name = dep["name"].as<std::string>();
        d.version = dep["version"].as<std::string>();

        const auto& options = dep["options"];
        d.options.header_only = options && options["header_only"]
            ? options["header_only"].as<bool>()
            : false;
        d.options.multithreaded = options && options["multithreaded"]
            ? options["multithreaded"].as<bool>()
            : false;

        m_config.m_dependencies.push_back(std::move(d));
    }

}

void cmh::YMLConfigParser::parseToolchains(const YAML::Node& toolsNode){
    if (!toolsNode || !toolsNode.IsSequence()) {
        std::cerr << "'toolchain' section is missing or malformed.\n";
        return;
    }

    for (const auto& tool : toolsNode) {
        Config::Toolchain t;

        t.build_generator = tool["build_generator"] ? tool["build_generator"].as<std::string>() : "Unix Makefiles";
        t.cmake_minimum_required = tool["cmake_minimum_required"] ? tool["cmake_minimum_required"].as<std::string>() : "3.14";
        t.build_type = tool["build_type"] ? tool["build_type"].as<std::string>() : "Release";

        t.pkg_manager = tool["pkg_manager"] ? tool["pkg_manager"].as<std::string>() : "";
        t.version = tool["version"] ? tool["version"].as<std::string>() : "";
        t.host = tool["host"] ? tool["host"].as<std::string>() : "";
        t.build = tool["build"] ? tool["build"].as<std::string>() : "";

        m_config.m_toolchains.push_back(std::move(t));
    }

}



    /****************************** RAPIDYAML ********************************/
#if 0
bool cmh::YMLConfigParser::parse() { 
    std::cout << "[Start Parsing]" << std::endl;
    m_config.m_dependencies.clear();
    m_config.m_toolchains.clear();
    m_config.m_compiler = Config::Compiler{};  // Reset compiler info and flags

    std::ifstream file(m_path);

    if (!file) {
        m_lastError = "Failed to open YAML file: " + m_path;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    ryml::Tree rymlTree = ryml::parse_in_arena(ryml::to_csubstr(content));
    ryml::NodeRef root = rymlTree.rootref();

    try {
        if (root.has_child("compiler")) {
            auto compilerNode = root["compiler"];
            m_config.m_compiler.name = std::string(compilerNode["name"].val().str);
            m_config.m_compiler.version = std::string(compilerNode["version"].val().str);

            if (compilerNode.has_child("flags")) {
                for (auto flag : compilerNode["flags"]) {
                    m_config.m_compiler.flags.push_back(std::string(flag.val().str));
                }
            }
            
        }

        // 
        /*********** Dependencies ********************/
        if (root.has_child("dependencies")) {
            for (auto depNode : root["dependencies"]) {
                Config::Dependency dep;
                dep.name = std::string(depNode["name"].val().str);
                dep.version = std::string(depNode["version"].val().str);

                if (depNode.has_child("options")) {
                    for (auto opt : depNode["options"].children()) {
                        std::string key = std::string(opt.key().str);
                        std::string val = std::string(opt.val().str);
                        dep.options[key] = (val == "true" || val == "1");
                    }
                }

                m_config.m_dependencies.push_back(std::move(dep));
            }
        }

        /*********** Toolchain ********************/
        if (root.has_child("toolchain")) {
            for (auto toolNode : root["toolchain"]) {
                Config::Toolchain tool;

                if (toolNode.has_child("build_generator")) {
                    tool.name = std::string(toolNode["build_generator"].val().str);
                    tool.version = std::string(toolNode["cmake_minimum_required"].val().str);
                    tool.build_type = std::string(toolNode["build_type"].val().str);
                } else if (toolNode.has_child("pkg_manager")) {
                    tool.name = std::string(toolNode["pkg_manager"].val().str);
                    tool.version = std::string(toolNode["version"].val().str);
                    tool.host = std::string(toolNode["host"].val().str);
                    tool.build = std::string(toolNode["build"].val().str);
                }

                m_config.m_toolchains.push_back(std::move(tool));
            }
        }


    } catch (const std::exception& e) {
        m_lastError = "YAML parsing error: " + std::string(e.what());
        return false;
    }

    std::cout << "[End Parsing]" << std::endl; 

    return true;

}
#endif 

const Config& cmh::YMLConfigParser::getConfig() const {
    return m_config;
}

const Config::Compiler& cmh::YMLConfigParser::getCompiler() const {
    return m_config.m_compiler;
}

const std::vector<Config::Dependency>& cmh::YMLConfigParser::getDependencies() const {
    return m_config.m_dependencies;
}

const std::vector<Config::Toolchain>& cmh::YMLConfigParser::getToolchains() const {
    return m_config.m_toolchains;
}

std::string cmh::YMLConfigParser::getLastError() const {
    return m_lastError;
}
