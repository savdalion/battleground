// Прямые события от элемента портулана ВОИН.
// Движение / Шагом / В заданном направлении

#include <pragma.hcl>
#include <restruct.hcl>
#include <portulan/struct.hcl>


/**
* Отрабатывает стратегию - прямые события.
*/
__kernel direct(
    __global baseContent_t*  bc,
    __global characteristicWarriorContent_t*  cc,
    //__global strategyWarriorContent_t*  sc,
    __global shortTermMemoryWarriorContent_t*  stmc,
    
    // время, выделенное для выполнения этой стратегии
    const real_t  dt,
    // стратегия может завершиться раньше заданного времени - остаток времени
    // пишется сюда
    real_t  timerest,
    // текущее время в порте
    const real_t  currentTime,
    // время порте, когда начала выполняться эта стратегия
    const real_t  startTime,

    // зерно для генератора случ. чисел
    const uint  seed
) {
    // находим данные о тек. состоянии стратегии в кратковременной памяти
    // @todo ...


    // элемент для отработки
    const uint i = get_global_id( 0 );
    __global const baseContent_t* base = &bc[ i ];
    if ( !base.incarnate ) {
        return;
    }


    // подготавливаем генератор случайных чисел
    uint2 rstate = (uint2)( seed,  i );


    // @todo ...

}
