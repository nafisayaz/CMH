#pragma once

#include <fstream>
#include <iostream>

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
        friend std::ostream& operator<<(std::ostream& os, const ParsedData& parsedData) {
            os << parsedData.m_json.dump(4); // Pretty print with indent of 4 spaces
            return os;
        }
    #endif
    };

    struct ConfigData  
    {
    #if defined(CMH_XML)
        pugi::xml_document m_doc;
        pugi::xml_parse_result m_result;
    #elif defined(CMH_JSON)
        json m_json;
         // Friend function to allow access to private members if needed
        friend std::ostream& operator<<(std::ostream& os, const ConfigData& configData) {
            os << configData.m_json.dump(4); // Pretty print with indent of 4 spaces
            return os;
        }

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
        void retrieve()override;
        void createDir()override;
        void createDir(std::string)override;
        void createDirectories(const json& dirs, const fs::path& basePath)override;
        void createFile(const fs::path& filepath)override;

    private:
        ParsedData m_data = {};

    };

    class Config
    {
   
    public:
        Config()=default;
        ~Config()=default;
        virtual bool load(const std::string& filename)=0;
        virtual const ConfigData& get()const=0;
        
    
    private:
        /* data */
    };
    
    class LocalConfig : public Config
    {
   
    public:
        LocalConfig()=default;
        ~LocalConfig()=default;
        virtual bool load(const std::string& filename);
        virtual const ConfigData& get()const;
        
    
    private:
        ConfigData m_data = {};
        
    };


}
