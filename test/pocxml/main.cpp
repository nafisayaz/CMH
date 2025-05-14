

#include <iostream>
#include <pugixml.hpp>

int main(){
    std::cout <<"hello world\n";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("../project_root.xml");
    if(!result){
        std::cout << result.description();
        return -1;
    }
    // doc.save(std::cout);
    std::cout << doc.child("gbs_root").child("project").child("name").first_child().value();
    
}

