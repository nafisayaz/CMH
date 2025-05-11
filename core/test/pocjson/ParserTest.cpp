
#include <memory>
#include "parser.h"


int main(){
    std::unique_ptr<CMH::Parser> p = std::make_unique<CMH::JsonxParser>();
    p->load("../project_manifest.json");
    p->retrieve();
}


