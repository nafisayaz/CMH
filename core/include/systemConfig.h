#pragma once
#include <iostream>
#include <filesystem>

namespace CMH {
    class System
    {
    
    public:
         System(/* args */)=default;
        ~System()=default;
        virtual bool initHome()=0;
        virtual std::filesystem::path findRoot(const std::filesystem::path&, const std::string& )=0;
        virtual bool init()=0;

    private:
        /* data */

    };

    class SystemInit: public System
    {
    
    public:
        SystemInit(/* args */)=default;
        ~SystemInit()=default;
        bool initHome()override;
        std::filesystem::path findRoot(const std::filesystem::path&, const std::string& )override;
        bool init()override;
        
    private:
        /* data */

    };
    

} // namespace config