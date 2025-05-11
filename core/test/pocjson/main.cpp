#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

// Load JSON file function
json load_json(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open JSON file: " + file_path);
    }
    json j;
    file >> j;
    return j;
}

// Test fixture class
class ProjectManifestTest : public ::testing::Test {
protected:
    json project_json;

    void SetUp() override {
        project_json = load_json("project_manifest.json");
    }
};

// **Test if JSON file loads successfully**
TEST_F(ProjectManifestTest, JSONFileLoads) {
    EXPECT_FALSE(project_json.empty());
}

// **Test if required keys exist**
TEST_F(ProjectManifestTest, ContainsRequiredKeys) {
    EXPECT_TRUE(project_json.contains("project"));
    EXPECT_TRUE(project_json.contains("directories"));
}

// **Test if 'project' key is a string**
TEST_F(ProjectManifestTest, ProjectKeyIsString) {
    ASSERT_TRUE(project_json["project"].is_string());
}

// **Test if 'directories' is an array**
TEST_F(ProjectManifestTest, DirectoriesIsArray) {
    ASSERT_TRUE(project_json["directories"].is_array());
}

// **Test if 'directories' contains valid sub-directories**
TEST_F(ProjectManifestTest, DirectoriesHaveValidSubDirectories) {
    for (const auto& dir : project_json["directories"]) {
        EXPECT_TRUE(dir.contains("name"));
        EXPECT_TRUE(dir.contains("sub-directories"));
        EXPECT_TRUE(dir["name"].is_string());
        EXPECT_TRUE(dir["sub-directories"].is_array());
    }
}

// // **Test if JSON structure is valid**
// TEST_F(ProjectManifestTest, ValidateJSONStructure) {
//     ASSERT_NO_THROW([](){
//         json test_json = {
//             {"project", "MinimalProject"},
//             {"directories", {
//                 {{"name", "src"}, {"sub-directories", json::array()}},
//                 {{"name", "include"}, {"sub-directories", json::array()}}
//             }}
//         };
//     }());
// }

// **Negative Test: Missing required keys**
TEST(ProjectManifestNegativeTest, MissingRequiredKeys) {
    json invalid_json = {
        {"directories", json::array()}  // Missing "project"
    };
    EXPECT_FALSE(invalid_json.contains("project"));
}

// **Negative Test: Incorrect Data Types**
TEST(ProjectManifestNegativeTest, IncorrectDataTypes) {
    json invalid_json = {
        {"project", 123},  // Should be a string
        {"directories", "not an array"}  // Should be an array
    };
    EXPECT_FALSE(invalid_json["project"].is_string());
    EXPECT_FALSE(invalid_json["directories"].is_array());
}

