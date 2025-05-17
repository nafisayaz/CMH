#include <gtest/gtest.h>
#include <memory>
#include <fstream>
#include <filesystem>

#include "Parser.h"

namespace fs = std::filesystem;

class ParserTest : public ::testing::Test {
protected:
    std::string validJson = R"json(
    {
        "project": {
            "name": "AwesomeApp",
            "version": "2.1.0",
            "language": "C++",
            "filename": ["main"]
        },
        "directories": [
            {
                "name": "include",
                "filename": ["greet"],
                "sub-directories": []
            },
            {
                "name": "src",
                "filename": ["greet"],
                "sub-directories": []
            }
        ]
    }
    )json";

    std::string tempFile;

    void SetUp() override {
        tempFile = "test_manifest.json";
        std::ofstream out(tempFile);
        out << validJson;
    }

    void TearDown() override {
        fs::remove(tempFile);
    }
};

TEST_F(ParserTest, ParsesValidManifestCorrectly) {
    std::unique_ptr<IParser> parser = std::make_unique<JsonProjectManifestParser>(tempFile);
    ASSERT_TRUE(parser->parse()) << "Parsing should succeed";

    const ProjectInfo& project = parser->getProjectInfo();
    EXPECT_EQ(project.name, "AwesomeApp");
    EXPECT_EQ(project.version, "2.1.0");
    EXPECT_EQ(project.language, "C++");
    ASSERT_EQ(project.filenames.size(), 1);
    EXPECT_EQ(project.filenames[0], "main");

    const auto& dirs = parser->getDirectories();
    ASSERT_EQ(dirs.size(), 2);
    EXPECT_EQ(dirs[0].name, "include");
    EXPECT_EQ(dirs[1].name, "src");
}

TEST_F(ParserTest, FailsOnMissingProjectField) {
    std::string brokenJson = R"({"directories":[]})";
    std::ofstream out(tempFile);
    out << brokenJson;

    std::unique_ptr<IParser> parser = std::make_unique<JsonProjectManifestParser>(tempFile);
    EXPECT_FALSE(parser->parse());
    EXPECT_FALSE(parser->getLastError().empty());
}

TEST_F(ParserTest, HandlesNonexistentFileGracefully) {
    std::unique_ptr<IParser> parser = std::make_unique<JsonProjectManifestParser>("nonexistent.json");
    EXPECT_FALSE(parser->parse());
    EXPECT_FALSE(parser->getLastError().empty());
}
