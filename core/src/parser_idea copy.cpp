#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>

// External Dependencies
#include "pugixml.hpp"
#include <nlohmann/json.hpp>
#include "yaml-cpp/yaml.h" // YAML parser

using json = nlohmann::json;

namespace CMH {

    // Base Interface for Parsed Data
    class IParsedData {
    public:
        virtual ~IParsedData() = default;
    };

    // Concrete Parsed Data for XML
    class XmlParsedData : public IParsedData {
    public:
        pugi::xml_document m_doc;
        pugi::xml_node getRoot() const { return m_doc.document_element(); }
    };

    // Concrete Parsed Data for JSON
    class JsonParsedData : public IParsedData {
    public:
        json m_json;
        const json& getJson() const { return m_json; }
    };

    // Concrete Parsed Data for YAML
    class YamlParsedData : public IParsedData {
    public:
        YAML::Node m_yaml;
        YAML::Node getYaml() const { return m_yaml; }
    };

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
    class XmlParser : public Parser {
    public:
        bool load(const std::string& filename) override {
            auto data = std::make_unique<XmlParsedData>();
            if (!data->m_doc.load_file(filename.c_str())) return false;
            m_data = std::move(data);
            return true;
        }

        bool retrieve() override { return true; }
    };

    // JSON Parser Implementation
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

        bool retrieve() override { return true; }
    };

    // YAML Parser Implementation
    class YamlParser : public Parser {
    public:
        bool load(const std::string& filename) override {
            auto data = std::make_unique<YamlParsedData>();
            try {
                data->m_yaml = YAML::LoadFile(filename);
            } catch (const std::exception&) {
                return false;
            }
            m_data = std::move(data);
            return true;
        }

        bool retrieve() override { return true; }
    };

    // Factory for Creating Parsers (No Macros, Fully Extensible)
    class ParserFactory {
    public:
        using ParserCreator = std::function<std::unique_ptr<IParser>()>;

        static ParserFactory& getInstance() {
            static ParserFactory instance;
            return instance;
        }

        void registerParser(const std::string& type, ParserCreator creator) {
            m_creators[type] = creator;
        }

        std::unique_ptr<IParser> createParser(const std::string& type) {
            if (m_creators.find(type) != m_creators.end()) {
                return m_creators[type]();
            }
            return nullptr; // Unknown type
        }

    private:
        std::unordered_map<std::string, ParserCreator> m_creators;
    };

    // Parser Registration (No Need for Macros)
    struct ParserRegistration {
        ParserRegistration() {
            auto& factory = ParserFactory::getInstance();
            factory.registerParser("xml", []() { return std::make_unique<XmlParser>(); });
            factory.registerParser("json", []() { return std::make_unique<JsonParser>(); });
            factory.registerParser("yaml", []() { return std::make_unique<YamlParser>(); });
        }
    };

    // Ensure parsers are registered at startup
    static ParserRegistration registration;

} // namespace CMH

// ============================
//        MAIN FUNCTION
// ============================

int main() {
    auto& factory = CMH::ParserFactory::getInstance();

    std::vector<std::string> formats = {"xml", "json", "yaml"};
    std::vector<std::string> files = {"data.xml", "data.json", "data.yaml"};

    for (size_t i = 0; i < formats.size(); ++i) {
        auto parser = factory.createParser(formats[i]);
        if (parser && parser->load(files[i])) {
            parser->retrieve();

            if (formats[i] == "xml") {
                auto& data = dynamic_cast<const CMH::XmlParsedData&>(parser->get());
                std::cout << "XML Root Node Name: " << data.getRoot().name() << "\n";
            }
            else if (formats[i] == "json") {
                auto& data = dynamic_cast<const CMH::JsonParsedData&>(parser->get());
                std::cout << "JSON Object Size: " << data.getJson().size() << "\n";
            }
            else if (formats[i] == "yaml") {
                auto& data = dynamic_cast<const CMH::YamlParsedData&>(parser->get());
                std::cout << "YAML Parsed Successfully.\n";
            }
        } else {
            std::cout << "Failed to load " << formats[i] << " file.\n";
        }
    }

    return 0;
}
