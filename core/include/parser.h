
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

namespace CMH{

    struct ParsedData  
    {
    #if defined(CMH_XML)
        pugi::xml_document m_doc;
        pugi::xml_parse_result m_result;
    #elif defined(CMH_JSON)
        json m_json;
    #endif
    };

    void print(const json& directories, int indent);
    void print();

    class Parser{

    public:
        virtual bool load(const std::string& filename)=0;
        virtual const ParsedData& get()const=0;
        virtual void retrieve()=0;

    };
    
    class JsonxParser : public Parser {

    public:
        JsonxParser()=default;
        ~JsonxParser()=default;
        bool load(const std::string& filename);
        const ParsedData& get()const;
        virtual void retrieve();


    private:
        ParsedData m_data = {};

    };


}
