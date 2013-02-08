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
    world()->engine()->incarnateSet( "a" );

    const auto p = world()->engine()->portulan();
    const auto pt = p->topology();


    // ��������� ���
    // ����� ����� ���-�� �����, ����� ���� ����� ���������������
    static const int needStep = 10 * 100000;
    static const bool closeWindow = true;
    static const bool showPulse = true;
    world()->go< 1000, PULSE, needStep, closeWindow, showPulse >( TIMESTEP );

    // ������� ������� ��������� ������
    const auto PL = world()->engine()->live().pulselive();


    // ��������� ���������

    // @todo ...
    ASSERT_TRUE( false ) << "�� �����������.";

#endif
}


    } // test
} // battleground
