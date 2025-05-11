#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>


bool fileExists(const std::string& path) {
    if(std::filesystem::exists(std::filesystem::path{path})){
        std::cerr << "Error: File not found : " << path << '\n';
        return false;
    }
    return true;
}

std::string xPath(std::string_view path, std::string_view filename){
    std::string fpath = std::string(path) + std::string(filename);
    if(!fileExists(fpath)){
        std::cerr << "Error: File not found : " << fpath << '\n';
    }
    return fpath;
    
}
