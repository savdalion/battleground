#pragma once

#include "TrainingTest.h"


namespace battleground {
    namespace test {


/**
* ������������ ���������� �����.
*/
class WarriorTT : public TrainingTest {
protected:
    inline WarriorTT(
    ) {
    }




    virtual inline ~WarriorTT() {
    }




    /**
    * @virtual TrainingTest
    */
    virtual inline void SetUp() {
    }

};







TEST_F( WarriorTT,  SingleWarriorSingleStrategy_TrainingSingleSwordTurn ) {
#if 1

    // ����������
    engine()->incarnateSet( "a" );

    const auto pt = engine()->portulan()->topology();



    // ������� ���������
    // @todo ...
    

    // ��������� ���
    // ����� ����� ���-�� �����, ����� ���� ����� ���������������
    // @todo ...


    // ��������� ���������

    // @todo ...
    ASSERT_TRUE( false ) << "�� �����������.";

#endif
}


    } // test
} // battleground
