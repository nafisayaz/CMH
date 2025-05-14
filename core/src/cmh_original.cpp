

#include "cmh.h"
#include "help.h"
#include "utility/path.h"


bool CMH::load(int argc, char* argv[]) {
    if (argc < 2) {
        help();
        std::exit(EXIT_SUCCESS);
    }

    std::string file_path = xPath(argv[1], PROJECT_ROOT);  

#ifdef CMH_XML
    m_cmhdata.m_result = m_cmhdata.m_doc.load_file(file_path.c_str());
    return m_cmhdata.m_result;
#endif

#ifdef CMH_JSON
    std::ifstream file(file_path);
    if (!file) {
        throw std::runtime_error("Could not open JSON file: " + file_path);
    }

    file >> m_cmhdata.m_json;
    return !m_cmhdata.m_json.empty();
#endif

    throw std::runtime_error("No valid data format defined. Define CMH_XML or CMH_JSON.");
}

const CMH::cmhData& CMH::get()const{
    return m_cmhdata;
}

