#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>

#ifdef CMH_XML
    #include "pugixml.hpp"
#endif

#ifdef CMH_JSON
    #include <nlohmann/json.hpp>
    using json = nlohmann::json;
#endif

namespace CMH {

    // Base Interface for Parsed Data
    class IParsedData {
    public:
        virtual ~IParsedData() = default;
        virtual void print() const = 0; // Debug function
    };

    // XML Parsed Data
    #ifdef CMH_XML
    class XmlParsedData : public IParsedData {
    public:
        pugi::xml_document m_doc;
        pugi::xml_parse_result m_result;

        void print() const override {
            std::cout << "XML Parsed Data Loaded Successfully.\n";
        }
    };
    #endif

    // JSON Parsed Data
    #ifdef CMH_JSON
    class JsonParsedData : public IParsedData {
    public:
        json m_json;

        void print() const override {
            std::cout << "JSON Parsed Data Loaded Successfully.\n";
        }
    };
    #endif

    // Parser Interface
    class IParser {
    public:
        virtual ~IParser() = default;
        virtual bool load(const std::string& filename) = 0;
        virtual const IParsedData& get() const = 0;
        virtual bool retrieve() = 0;
    };

    // Base Parser Class
    class Parser : public IParser {
    public:
        Parser() = default;
        virtual ~Parser() = default;
        
        virtual bool load(const std::string& filename) = 0;
        virtual const IParsedData& get() const override { return *m_data; }
        virtual bool retrieve() = 0;

    protected:
        std::unique_ptr<IParsedData> m_data;
    };

    // XML Parser Implementation
    #ifdef CMH_XML
    class XmlParser : public Parser {
    public:
        bool load(const std::string& filename) override {
            auto data = std::make_unique<XmlParsedData>();
            pugi::xml_parse_result result = data->m_doc.load_file(filename.c_str());
            if (!result) return false;
            
            data->m_result = result;
            m_data = std::move(data);
            return true;
        }

        bool retrieve() override {
            // Implement XML-specific retrieval logic if needed
            return true;
        }
    };
    #endif

    // JSON Parser Implementation
    #ifdef CMH_JSON
    class JsonParser : public Parser {
    public:
        bool load(const std::string& filename) override {
            std::ifstream file(filename);
            if (!file.is_open()) return false;

            auto data = std::make_unique<JsonParsedData>();
            file >> data->m_json;

            m_data = std::move(data);
            return true;
        }

        bool retrieve() override {
            // Implement JSON-specific retrieval logic if needed
            return true;
        }
    };
    #endif

    // Factory for Creating Parsers
    class ParserFactory {
    public:
        static std::unique_ptr<IParser> createParser(const std::string& type) {
            #ifdef CMH_XML
            if (type == "xml") {
                return std::make_unique<XmlParser>();
            }
            #endif

            #ifdef CMH_JSON
            if (type == "json") {
                return std::make_unique<JsonParser>();
            }
            #endif

            return nullptr; // Unknown type
        }
    };

    // Manager to Handle Multiple Parsers at Runtime
    class ParserManager {
    private:
        std::unordered_map<std::string, std::unique_ptr<IParser>> m_parsers;

    public:
        void addParser(const std::string& type) {
            auto parser = ParserFactory::createParser(type);
            if (parser) {
                m_parsers[type] = std::move(parser);
            }
        }

        IParser* getParser(const std::string& type) {
            if (m_parsers.find(type) != m_parsers.end()) {
                return m_parsers[type].get();
            }
            return nullptr;
        }
    };

} // namespace CMH

// ============================
//        MAIN FUNCTION
// ============================

int main() {
    CMH::ParserManager manager;
    
    // Add both XML and JSON parsers (if enabled)
    #ifdef CMH_XML
    manager.addParser("xml");
    #endif
    #ifdef CMH_JSON
    manager.addParser("json");
    #endif

    // Load an XML file
    #ifdef CMH_XML
    CMH::IParser* xmlParser = manager.getParser("xml");
    if (xmlParser && xmlParser->load("data.xml")) {
        xmlParser->retrieve();
        xmlParser->get().print();
    } else {
        std::cout << "Failed to load XML file.\n";
    }
    #endif

    // Load a JSON file
    #ifdef CMH_JSON
    CMH::IParser* jsonParser = manager.getParser("json");
    if (jsonParser && jsonParser->load("data.json")) {
        jsonParser->retrieve();
        jsonParser->get().print();
    } else {
        std::cout << "Failed to load JSON file.\n";
    }
    #endif

    return 0;
}
