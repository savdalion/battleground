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
    // @todo ...



    // покажем результат
    // @todo ...
    

    // запускаем мир
    // задаём такое кол-во шагов, чтобы воин успел потренироваться
    // @todo ...


    // проверяем результат

    // @todo ...
    ASSERT_TRUE( false ) << "Не реализовано.";

#endif
}


    } // test
} // battleground
