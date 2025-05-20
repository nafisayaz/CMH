#include <iostream>
#include <memory>

#include "SupportParser.h"

int main() {
    const std::string filePath = "../support.yml";

    std::unique_ptr<cmh::ISupportParser> parser = std::make_unique<cmh::SupportParser>(filePath);

    if (!parser->parse()) {
        std::cerr << "Failed to parse manifest: " << parser->getLastError() << std::endl;
        return 1;
    }

    const Support& support = parser->getSupport();

    // Print Compiler
    std::cout << "\n===== Operating System =====\n";
    for( const auto& os :  support.m_OS){
        std::cout << os.name << "\n";
        std::cout << "[ ";
        for(const auto& version: os.versions){
            std::cout <<version <<", ";
        }
        std::cout << " ]\n";
    }
    

    return 0;
}
