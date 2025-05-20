// File: src/SupportParser.cpp

#include <iostream>
#include <fstream>
#include <sstream>

#include "SupportParser.h"

cmh::SupportParser::SupportParser(const std::string &path)
        : m_path(path){}

    
/****************************** YAML-CPP ********************************/
bool cmh::SupportParser::parse(){
    try {
        YAML::Node root = YAML::LoadFile(m_path);

        if (root["OS"]) parseOSVersion(root["OS"]);
        if (root["Arch"]) parseArchitecture(root["Arch"]);
        if (root["Compiler"]) parseCompilerVersion(root["Compiler"]);
        if (root["compiler_flags"]) parseCompilerFlags(root["compiler_flags"]);
        if (root["build_type"]) parseBuildType(root["build_type"]);

    } catch (const YAML::Exception& e) {
        std::cerr << "YAML parsing error: " << e.what() << '\n';
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        return false;
    }

    return true;
}

void cmh::SupportParser::parseOSVersion(const YAML::Node& Node){
    for (const auto& osNode : Node) {
        for (auto it = osNode.begin(); it != osNode.end(); ++it) {
            Support::OSVersion osVer;
            osVer.name = it->first.as<std::string>();
            const YAML::Node& versions = it->second["Version"];
            for (const auto& ver : versions) {
                osVer.versions.push_back(ver.as<std::string>());
            }
            m_Support.m_OS.push_back(std::move(osVer));
        }
    }
}
void cmh::SupportParser::parseCompilerVersion(const YAML::Node& Node){
    for (const auto& compiler : {"gcc", "clang", "apple-clang"}) {
        if (!Node[compiler]) continue;
        for (const auto& ver : Node[compiler]) {
            if (compiler == std::string("gcc"))
                m_Support.m_CompilerVersion.gcc.push_back(ver.as<std::string>());
            else if (compiler == std::string("clang"))
                m_Support.m_CompilerVersion.clang.push_back(ver.as<std::string>());
            else if (compiler == std::string("apple-clang"))
                m_Support.m_CompilerVersion.apple_clang.push_back(ver.as<std::string>());
        }
    }
}
void cmh::SupportParser::parseCompilerFlags(const YAML::Node& Node){
    for (const auto& category : Node) {
        const std::string& key = category.first.as<std::string>();
        const YAML::Node& flags = category.second;
        for (const auto& flag : flags) {
            if (key == "general")
                m_Support.m_CompilerFlags.general.push_back(flag.as<std::string>());
            else if (key == "optimization")
                m_Support.m_CompilerFlags.optimization.push_back(flag.as<std::string>());
            else if (key == "debugging")
                m_Support.m_CompilerFlags.debugging.push_back(flag.as<std::string>());
            else if (key == "language_standards")
                m_Support.m_CompilerFlags.language_standards.push_back(flag.as<std::string>());
            else if (key == "warnings")
                m_Support.m_CompilerFlags.warnings.push_back(flag.as<std::string>());
            else if (key == "linking")
                m_Support.m_CompilerFlags.linking.push_back(flag.as<std::string>());
        }
    }
}
void cmh::SupportParser::parseArchitecture(const YAML::Node& Node){
    for (const auto& arch : Node) {
        m_Support.m_Arch.arch.push_back(arch.as<std::string>());
    }
}

void cmh::SupportParser::parseBuildType(const YAML::Node& Node){
    for (const auto& type : Node) {
        m_Support.m_BuildType.build_type.push_back(type.as<std::string>());
    }
}


const Support& cmh::SupportParser::getSupport() const {
    return m_Support;
}

const std::vector<Support::OSVersion>& cmh::SupportParser::getOSVersion() const {
    return m_Support.m_OS;
}

const Support::CompilerVersions& cmh::SupportParser::getCompilerVersion() const {
    return m_Support.m_CompilerVersion;
}

const Support::CompilerFlags& cmh::SupportParser::getCompilerFlags() const {
    return m_Support.m_CompilerFlags;
}

const Support::Architecture& cmh::SupportParser::getArchitecture() const {
    return m_Support.m_Arch;
}

const Support::BuildType& cmh::SupportParser::getBuildType() const {
    return m_Support.m_BuildType;
}

std::string cmh::SupportParser::getLastError() const {
    return m_lastError;
}
