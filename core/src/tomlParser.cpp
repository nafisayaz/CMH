#include "system_configuration.h"

bool CMH::ConfigTOML::load(const std::string& path) {
    toml::table config = toml::parse_file(path);

    if (auto proj = config["project"].as_table()) {
        if (auto name = (*proj)["name"].value<std::string>())
            m_project.name = *name;

        if (auto version = (*proj)["version"].value<std::string>())
            m_project.version = *version;
    }

    if (auto comp = config["compiler"].as_table()) {
        if (auto type = (*comp)["type"].value<std::string>())
            m_compiler.type = *type;

        if (auto version = (*comp)["version"].value<int>())
            m_compiler.version = *version;

        if (auto flags = (*comp)["flags"].as_array()) {
            for (auto&& flag : *flags) {
                if (auto val = flag.value<std::string>())
                    m_compiler.flags.push_back(*val);
            }
        }
    }

    return true;
}

const CMH::ProjectConfig& CMH::ConfigTOML::getProject() { return m_project; }
const CMH::CompilerConfig& CMH::ConfigTOML::getCompiler() { return m_compiler; }
