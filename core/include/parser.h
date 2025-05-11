
#include <fstream>

#include <experimental/filesystem>
#include "cmh_API.h"
#include "cmh_Contants.h"

#ifdef CMH_XML
    #include "pugixml.hpp"
#endif

#ifdef CMH_JSON
    #include <nlohmann/json.hpp>
    using json = nlohmann::json;

#endif
namespace fs = std::experimental::filesystem;

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
        virtual void createDir()=0;
        virtual void createDir(std::string)=0;
        virtual void createDirectories(const json& dirs, const fs::path& basePath)=0;
        virtual void createFile(const fs::path& filepath)=0;

    };
    
    class JsonxParser : public Parser {

    public:
        JsonxParser()=default;
        ~JsonxParser()=default;
        bool load(const std::string& filename);
        const ParsedData& get()const;
        virtual void retrieve();
        virtual void createDir();
        virtual void createDir(std::string);
        virtual void createDirectories(const json& dirs, const fs::path& basePath);
        virtual void createFile(const fs::path& filepath);

    private:
        ParsedData m_data = {};

    };


}
