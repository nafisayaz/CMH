#include <iostream>
#include <memory>

#include "YMLConfigParser.h"

int main() {
    const std::string filePath = "../local_configuration.yml";

    std::unique_ptr<cmh::IYMLConfigParser> parser = std::make_unique<cmh::YMLConfigParser>(filePath);

    if (!parser->parse()) {
        std::cerr << "Failed to parse manifest: " << parser->getLastError() << std::endl;
        return 1;
    }

    const Config& config = parser->getConfig();

    // Print Compiler
    std::cout << "\n===== COMPILER =====\n";
    std::cout << "Name: " << config.m_compiler.name << "\n";
    // std::cout << "Version: " << config.m_compiler.version << "\n";
    // std::cout << "Flags:\n";
    // for (const auto& flag : config.m_compiler.flags) {
    //     std::cout << "  - " << flag << "\n";
    // }

    // // Print Dependencies
    // std::cout << "\n===== DEPENDENCIES =====\n";
    // for (const auto& dep : config.m_dependencies) {
    //     std::cout << "- Name: " << dep.name << "\n";
    //     std::cout << "  Version: " << dep.version << "\n";
    //     std::cout << "  Options:\n";
    //     for (const auto& option : dep.options) {
    //         std::cout << "    " << option.first << ": " << (option.second ? "true" : "false") << "\n";
    //     }
    // }

    // // Print Toolchains
    // std::cout << "\n===== TOOLCHAINS =====\n";
    // for (const auto& tool : config.m_toolchains) {
    //     std::cout << "- Tool: " << tool.name << "\n";
    //     std::cout << "  Version: " << tool.version << "\n";
    //     if (!tool.build_type.empty()) std::cout << "  Build Type: " << tool.build_type << "\n";
    //     if (!tool.host.empty())      std::cout << "  Host: " << tool.host << "\n";
    //     if (!tool.build.empty())     std::cout << "  Build: " << tool.build << "\n";
    // }

    return 0;
}
