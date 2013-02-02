#pragma once

#include "TrainingTest.h"


namespace battleground {
    namespace test {


/**
* Тестирование тренировки воина.
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

    // подготовка
    world()->engine()->incarnateSet( "a" );

    const auto p = world()->engine()->portulan();
    const auto pt = p->topology();


    // запускаем мир
    // задаём такое кол-во шагов, чтобы воин успел потренироваться
    static const int needStep = 10 * 100000;
    static const bool closeWindow = true;
    static const bool showPulse = true;
    world()->go< 1000, PULSE, needStep, closeWindow, showPulse >();

    // сколько пульсов отработал движок
    const auto PL = world()->engine()->live().pulselive();


    // проверяем результат

    // @todo ...
    ASSERT_TRUE( false ) << "Не реализовано.";

#endif
}


    } // test
} // battleground
