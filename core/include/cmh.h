#include <vector>
#include <unordered_map>
#include <fstream>

#include "cmh_API.h"
#include "cmh_Contants.h"

#ifdef CMH_XML
    #include "pugixml.hpp"
#endif

#ifdef CMH_JSON
    #include <nlohmann/json.hpp>
    using json = nlohmann::json;

#endif

class CMH
{
    
public:
    struct cmhData  
    {
    #if defined(CMH_XML)
        pugi::xml_document m_doc;
        pugi::xml_parse_result m_result;
        std::vector<std::string> m_path;
    #elif defined(CMH_JSON)
        json m_json;
        
    #endif
    };

    CMH()=default;
    ~CMH()=default;
    bool load(int argc, char* argv[]);
    const cmhData& get()const;

    

    
private:
    cmhData m_cmhdata = {};


};

