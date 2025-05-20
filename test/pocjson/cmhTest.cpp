#include<iostream>
#include <memory>
#include "cmh.h"

int main(int argc, char* argv[] ){
    
    
    // std::unique_ptr<CMH::System> system = std::make_unique<CMH::SystemInit>();
    // if(argc == 2 and std::string(argv[1])==std::string("init")){
    //     system->init();
    // }

    // std::unique_ptr<CMH::Parser> parser = std::make_unique<CMH::JsonxParser>();
    // parser->load("../project_manifest.json");
    // parser->retrieve();
    // if(argc == 3 and std::string(argv[1])==std::string("create")){
    //     parser->createDir(std::string(argv[2]));
    // }

    // if(argc == 1){
    //     parser->createDir();
    // }
    
    std::unique_ptr<CMH::Config> config_json = std::make_unique<CMH::LocalConfig>();
    config_json->load("../local-config.json");
    std::cout << config_json->get() << std::endl;

    // std::unique_ptr<CMH::ConfigManager> config_toml = std::make_unique<CMH::ConfigTOML>();
    // std::filesystem::path relative_path = "../local_configuration.toml";
    // std::cout << std::filesystem::absolute(relative_path) << std::endl;
    // config_toml->load(std::filesystem::absolute(relative_path));
    // std::cout << config_toml->getProject();
    // config_toml->getCompiler();



}


