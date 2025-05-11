
#include <memory>
#include "parser.h"
#include<iostream>


int main(int argc, char* argv[] ){
    std::unique_ptr<CMH::Parser> p = std::make_unique<CMH::JsonxParser>();
    p->load("../project_manifest.json");
    p->retrieve();
    if(argc >2){
        p->createDir(std::string(argv[2]));
    }else{
        p->createDir();
    }
    
}


