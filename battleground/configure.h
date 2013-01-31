#pragma once


#include <string>


namespace battleground {


/**
* ���� � ����� ������ OpenCL.
*/
static const std::string PATH_BATTLEGROUND =
    "D:/Projects/workspace/battleground/battleground/include";
static const std::string WORLD_PATH_BATTLEGROUND =
    PATH_BATTLEGROUND + "/world";
static const std::string INCARNATION_WORLD_PATH_BATTLEGROUND =
    WORLD_PATH_BATTLEGROUND + "/incarnation";
static const std::string KIND_WORLD_PATH_BATTLEGROUND =
    WORLD_PATH_BATTLEGROUND + "/kind";
static const std::string CL_WORLD_PATH_BATTLEGROUND =
    WORLD_PATH_BATTLEGROUND + "/@";



/**
* ��������� OpenCL.
*/
#define __CL_ENABLE_EXCEPTIONS


} // battleground
