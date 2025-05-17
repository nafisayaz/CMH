// cmh.h
#pragma once

#include "cmh_API.h"
#include "cmh_Contants.h"
#include "systemConfig.h"

// Feature-based includes
#ifdef CMH_XML
    #include "pugixml.hpp"
#endif

#ifdef CMH_JSON
    #include "Parser.h"
    #include "jsonParser.h"
#endif

#ifdef CMH_TOML
    #include "tomlParser.h"
#endif

