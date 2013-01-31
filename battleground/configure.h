#pragma once


#include <string>


namespace battleground {


/**
* Путь к ядрам файлам OpenCL.
*/
static const std::string PATH_CL_BATTLEGROUND =
    "D:/Projects/workspace/battleground/battleground/include";
static const std::string WORLD_PATH_CL_BATTLEGROUND =
    PATH_CL_BATTLEGROUND + "/world/@";



/**
* Настройки OpenCL.
*/
#define __CL_ENABLE_EXCEPTIONS


} // battleground
