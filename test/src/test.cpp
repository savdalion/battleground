#include "../include/StdAfx.h"
#include "../include/configure.h"
#include <typelib/typelib.h>

#include "../include/world/WarriorTraining.h"


/**
* ������������ ������� 'battleground'.
*/
int main( int argc, char** argv ) {

    using namespace battleground;

    namespace tc = typelib::constant::physics;


    setlocale( LC_ALL, "Russian" );
    // ��� ����������� '.' ������ ','
    setlocale( LC_NUMERIC, "C" );



    ::testing::InitGoogleTest( &argc, argv );
    ::testing::FLAGS_gtest_death_test_style = "fast";
    int result = 0;
    try {
        result = RUN_ALL_TESTS();
    } catch ( ... ) {
        // @todo fine ��������� assert() � ��������� - ��������� ����:
        //       ��������� ����� ������ � �������. �������� assert'� ��
        //       exception?
    }




    std::cout << std::endl << "^" << std::endl;
    std::cin.ignore();

    return 0;

} // main()
