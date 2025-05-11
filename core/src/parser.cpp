

#include "parser.h"
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
        std::cout << "Project: " << m_data.m_json["project"] << "\n";
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



