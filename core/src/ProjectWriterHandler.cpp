#include <iostream>
#include <fstream>
#include <algorithm> 
#include <cctype>   
#include "ProjectWriterHandler.h"


void cmh::ProjectWriterHandler::writeInFile(const std::string& dirName, const fs::path& filename, const std::string& projectName){
    if(fs::exists(filename)){
        if(dirName == "include"){
            writeInHeaderFile(filename);
        }else if(dirName == "src"){
            writeInSourceFile(filename, projectName);
        }else{
            std::cerr <<"err: " << dirName <<" is invalid to write" <<"\n";
        }
    }
}

void cmh::ProjectWriterHandler::writeInHeaderFile(const fs::path& filename){
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }

    std::string fileStr = filename.stem().string();

    std::string guard = fileStr + "_H";
    std::transform(guard.begin(), guard.end(), guard.begin(), ::toupper);
    outfile << "// Header: " << fileStr<<".h" << "\n\n";
    // outfile <<"#ifndef " << "__" << guard << "__" <<"\n";
    // outfile <<"#define "<< "__" << guard << "__" <<"\n\n";
    outfile << "#pragma once\n\n";
    outfile << "class " << fileStr << " {\n";
    outfile << "public:\n    " << fileStr << "();\n    ~" << fileStr << "();\n";
    outfile << "    void say();" << "\n";
    outfile << "};\n";
}

void cmh::ProjectWriterHandler::writeInSourceFile(const fs::path& filename, const std::string& projectName){
     std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }

    std::string fileStr = filename.stem().string();

    // std::string guard = fileStr + "_H";
    // std::transform(guard.begin(), guard.end(), guard.begin(), ::toupper);
    outfile << "// SOURCE: " << fileStr<<".cpp" << "\n\n";
    outfile << "#include <" << fileStr<<".h>" << "\n\n";
    outfile << fileStr << "::" << fileStr << "(){}\n";
    outfile << fileStr << "::~" << fileStr << "(){}\n\n";
    outfile << "void " << fileStr << "::say(){" << "\n";
    outfile << "    std::cout << \"Hello from " << projectName << "\" << std::endl;\n";
    outfile << "}\n\n";
}

