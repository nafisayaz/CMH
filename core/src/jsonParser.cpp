

#include "jsonParser.h"
#include "help.h"
#include "utility/path.h"


bool CMH::JsonxParser::load(const std::string& filename) {
    if(!filename.size()) {
        help();
        std::exit(EXIT_SUCCESS);
    }

#ifdef CMH_XML
    m_data.m_result = m_data.m_doc.load_file(filename.c_str());
    return m_data.m_result;
#endif

#ifdef CMH_JSON
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open JSON file: " + filename);
    }

    file >> m_data.m_json;
    return !m_data.m_json.empty();
#endif

    throw std::runtime_error("No valid data format defined. Define CMH_XML or CMH_JSON.");
}

const CMH::ParsedData& CMH::JsonxParser::get()const{
    return m_data;
}


void CMH::JsonxParser::retrieve(){
#ifdef CMH_JSON
    if (m_data.m_json.contains("project")) {
        std::cout << "Project: " << m_data.m_json["project"]["name"]<< "\n";
        std::cout << "version: " << m_data.m_json["project"]["version"]<< "\n";
    }

    if (m_data.m_json.contains("directories")) {
        CMH::print(m_data.m_json["directories"], 2);
    }
#endif

}

void CMH::print(const json& directories, int indent) {
    for (const auto& dir : directories) {
        std::cout << std::string(indent, ' ') << "- " << dir["name"] << "\n";
        if (dir.contains("sub-directories") && !dir["sub-directories"].empty()) {
            print(dir["sub-directories"], indent + 2);
        }
    }
}

void CMH::JsonxParser::createFile(const fs::path& filepath) {
    std::ofstream ofs(filepath);
    if (ofs) {
        std::cout << "Created file: " << filepath << std::endl;
    } else {
        std::cerr << "Failed to create file: " << filepath << std::endl;
    }
}

void CMH::JsonxParser::createDir(){

    std::string project_name = m_data.m_json["project"]["name"];
    std::string project_language = m_data.m_json["project"]["language"];

    fs::path baseDir = fs::current_path() / project_name;

    if (!fs::exists(baseDir)) {
        fs::create_directory(baseDir);
        std::cout << "Created project directory: " << baseDir << std::endl;
    }

    for (const auto& file : m_data.m_json["project"]["filename"]) {
        createFile(baseDir / (file.get<std::string>() + ".cpp"));
    }

    createDirectories(m_data.m_json["directories"], baseDir);
}

void CMH::JsonxParser::createDir(std::string project_name){

    fs::path baseDir = fs::current_path() / project_name;

    if (!fs::exists(baseDir)) {
        fs::create_directory(baseDir);
        std::cout << "Created project directory: " << baseDir << std::endl;
    }

    for (const auto& file : m_data.m_json["project"]["filename"]) {
        createFile(baseDir / (file.get<std::string>() + ".cpp"));
    }

    createDirectories(m_data.m_json["directories"], baseDir);
}

void CMH::JsonxParser::createDirectories(const json& dirs, const fs::path& basePath){

    for (const auto& dir : dirs) {
        fs::path dirPath = basePath / dir["name"].get<std::string>();
        if (!fs::exists(dirPath)) {
            fs::create_directory(dirPath);
            std::cout << "Created directory: " << dirPath << std::endl;
        }

        for (const auto& file : dir["filename"]) {
            std::string ext = (dir["name"].get<std::string>() == "include") ? ".hpp" : ".cpp";
            createFile(dirPath / (file.get<std::string>() + ext));
        }

        if (dir.contains("sub-directories")) {
            createDirectories(dir["sub-directories"], dirPath);
        }
    }

}

bool CMH::LocalConfig::load(const std::string& filename) {
    if(!filename.size()) {
        help();
        std::exit(EXIT_SUCCESS);
    }

#ifdef CMH_XML
    m_data.m_result = m_data.m_doc.load_file(filename.c_str());
    return m_data.m_result;
#endif

#ifdef CMH_JSON
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open JSON file: " + filename);
    }

    file >> m_data.m_json;
    return !m_data.m_json.empty();
#endif

    throw std::runtime_error("No valid data format defined. Define CMH_XML or CMH_JSON.");
}

const CMH::ConfigData& CMH::LocalConfig::get()const{
    return m_data;
}

