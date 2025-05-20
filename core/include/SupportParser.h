// File: include/SupportParser.h

#include <string>
#include <vector>

/* YML-CPP */
#include <yaml-cpp/yaml.h>

#include "ISupportParser.h"


namespace cmh{

    class SupportParser : public ISupportParser {
    public:
        explicit SupportParser(const std::string& path);
        bool parse() override; // yml parse() 
        const Support& getSupport() const override;
        const std::vector<Support::OSVersion>& getOSVersion() const override;
        const Support::CompilerVersions& getCompilerVersion() const override;
        const Support::CompilerFlags& getCompilerFlags() const override;
        const Support::Architecture& getArchitecture() const override;
        const Support::BuildType& getBuildType() const override;
        std::string getLastError() const override;
    private:
    /*PRIVATE FUNCTIONS*/
        void parseOSVersion(const YAML::Node& Node);
        void parseCompilerVersion(const YAML::Node& Node);
        void parseCompilerFlags(const YAML::Node& Node);
        void parseArchitecture(const YAML::Node& Node);
        void parseBuildType(const YAML::Node& Node);

    /* DATA MEMBERS*/
        const std::string m_path;
        std::string m_lastError;
        Support m_Support;

    };

} // namespace cmh::