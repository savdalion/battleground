#pragma once


#include <string>


namespace battleground {


// #! ��������� OpenCL � C++ ������ ���� ����������� �������.
//    ������ �������� ����� �������� �� ���������, ������� ��������
//    ��������� ��������� � ������� "���������".
#pragma pack( 1 )


/**
* # ��������� ������������ �. �., ����� �� ����������� �� ��� ���������
*   � ��� OpenCL. ������� ��� ����. �����������.
*/
#ifndef __constant
#define __constant const
#endif

#ifndef __global
#define __global /*nothing*/
#endif

// ������������ ��� VC++ �� ���������
#define __attribute__(x) /*nothing*/




/**
* ����.
*/
static const std::string PATH_BATTLEGROUND =
    "D:/Projects/workspace/battleground/battleground/include";
static const std::string WORLD_PATH_BATTLEGROUND =
    PATH_BATTLEGROUND + "/world";

static const std::string IMAGE_WORLD_PATH_BATTLEGROUND =
    WORLD_PATH_BATTLEGROUND + "/image";
static const std::string VISUAL_IMAGE_WORLD_PATH_BATTLEGROUND =
    IMAGE_WORLD_PATH_BATTLEGROUND + "/visual";

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




/**
* ������ ���� ����, �������� �������� ������������� ��������, ���.
*/
static const int WIDTH_WINDOW  = 1024;
static const int HEIGHT_WINDOW = 768;
static const float WINDOW_K_WIDTH_HEIGHT =
    static_cast< float >( WIDTH_WINDOW ) /
    static_cast< float >( HEIGHT_WINDOW );




/**
* �������� ������ ��������� ����������� ���� ������������ �����������, ���.
*/
static const int CENTER_WINDOW_WIDTH  = WIDTH_WINDOW  / 2;
static const int CENTER_WINDOW_HEIGHT = HEIGHT_WINDOW / 2;




/**
* ������������ ��������� ���. � ���. �����.
*/
static const typelib::coord2_t NORMA_COORD(
    CENTER_WINDOW_WIDTH,  CENTER_WINDOW_HEIGHT
);




/**
* ������������ � ����������� ���������� ����������� ����, ���.
*
* # ��� ���������� � ������� �������� ������������ ���. ���� ����.
* # ����������� ������������ ����
*     - ���������� 2D-���, ��� ������: X - ������, Y - ����
*     - ���������� 3D-���: X - �����, Y - �����, Z - �����
*/
static const int MIN_X_VISUAL_COORD = -WIDTH_WINDOW  / 2;
static const int MAX_X_VISUAL_COORD =  WIDTH_WINDOW  / 2;
static const int MIN_Y_VISUAL_COORD = -HEIGHT_WINDOW / 2;
static const int MAX_Y_VISUAL_COORD =  HEIGHT_WINDOW / 2;



/**
* ������������ ������� ���������� �� ������ ���� (�� ������ �� ����).
*/
static const float MAX_VISUAL_CENTER_DISTANCE =
    typelib::vector2_t( MAX_X_VISUAL_COORD, MAX_Y_VISUAL_COORD ).length();




/**
* �� ������� ������ ����� ������� "����������� �����".
* ��� ������ - ��� ���� �������� �������������.
*/
static const size_t APPROXIMATE_TIMESTEP = 5;




/**
* ��� �������.
*/
#define ASSERT(e) ((void) (( e ) ? 0 : THROW_ASSERT( #e, __FILE__, __LINE__ )))
#define THROW_ASSERT( e, file, line ) ( (void)std::printf( "%s:%u: failed assertion '%s'\n", file, line, e ),\
    throw std::runtime_error( std::string( file ) + boost::lexical_cast< std::string >( line ) + ": failed assertion " + e ) )


} // battleground
