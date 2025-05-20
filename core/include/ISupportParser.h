// File: include/ISupportParser.h

#include <string>
#include <vector>
#include <map>


struct Support {

    struct OSVersion {
        std::string name;
        std::vector<std::string> versions;
    };

    struct CompilerVersions {
        std::vector<std::string> gcc;
        std::vector<std::string> clang;
        std::vector<std::string> apple_clang;
    };

    struct CompilerFlags {
        std::vector<std::string> general;
        std::vector<std::string> optimization;
        std::vector<std::string> debugging;
        std::vector<std::string> language_standards;
        std::vector<std::string> warnings;
        std::vector<std::string> linking;
    };

    struct Architecture
    {
        std::vector<std::string> arch;
    };
    
    struct BuildType
    {
        std::vector<std::string> build_type;
    };

    std::vector<OSVersion> m_OS;
    CompilerVersions m_CompilerVersion;
    CompilerFlags m_CompilerFlags;
    Architecture m_Arch;
    BuildType m_BuildType;

};

namespace cmh{

    class ISupportParser {
    public:
        virtual ~ISupportParser() = default;
        virtual bool parse() = 0; // yml parse() 
        virtual const Support& getSupport() const = 0;
        virtual const std::vector<Support::OSVersion>& getOSVersion() const = 0;
        virtual const Support::CompilerVersions& getCompilerVersion() const = 0;
        virtual const Support::CompilerFlags& getCompilerFlags() const = 0;
        virtual const Support::Architecture& getArchitecture() const = 0;
        virtual const Support::BuildType& getBuildType() const = 0;
        virtual std::string getLastError() const = 0;
    };

} // namespace cmh::