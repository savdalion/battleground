// Прямые события от элементов портулана.

#include <_.cl>


/**
* Отрабатывает стратегию - прямые события.
*/
__kernel begin(
    // набор всех элементов портулана
    __global element_t*  e,
    // вектор завершённости *всех* действий *всех* стратегий этой
    // группы элементов
    __global progressAction_t*  pa,
    // действие в этой стратегии, с которого надо начать выполнение
    const enum ACTION  startAction,
    // действие, выполнить которое стратегии не хватило времени
    enum ACTION  stopAction,
    // текущее время в портулане
    const real_t  currentTime,
    // время, когда начала выполняться эта стратегия
    const real_t  startTime,
    // время, выделенное порте для выполнения этой стратегии
    const real_t  timestep,
    // стратегия может завершиться раньше заданного выше времени - остаток
    // записывается сюда
    // если это значение < 0.0, значит, стратегия завершена
    real_t  timerest,
    // зерно для генератора случ. чисел
    const uint  seed
) {
    // стратегия уже могла быть выполнена
    if (timerest < 0.0) {
#ifdef __DEBUG
        printf( "warrior / train / single-sword / turn"
            "(.) Call completed strategy. Lost perfomance.\n" );
        return;
#endif
    }

    const uint i = get_global_id( 0 );
    __global const warrior_t* element = &e[ i ];
    if ( warriorAbsent( element ) ) {
        return;
    }
    
    
    // подготавливаем генератор случайных чисел
    uint2 rstate = (uint2)( seed,  i );
    
    
    real_t dt = timestep;
    enum ACTION a = startAction;
    // будем двигаться по графу до тех пор, пока не исчерпаем заданный
    // лимит времени
    for ( ; (dt > 0.0) && (a != A_UNDEFINED); ) {

        // получим вероятность
        const real_t p = probability( &rseed );
        // действие уже может быть начато
        const real_t progressRest = 1.0 - pa[ i ][ a ];
        real_t durationActionAll = 0.0;
        real_t durationActionRest = 0.0;

        switch ( a ) {

            // Переходит в боевую стойку
            case A0 :
#ifdef __DEBUG
                printf( "warrior / train / single-sword / turn"
                    " A0\n" );
#endif
                // время действия узнали при формировании ядра из графа
                durationActionAll = 1.0;  // s
                // сколько времени надо для завершения этого действия
                durationActionRest = durationActionAll * progressRest;
                if (durationActionRest < dt) {
                    // времени хватает
                    // отмечаем д. как завершённое и берём следующее
                    pa[ i ][ a ] = 1.0;
                    dt -= durationActionRest;
                    // вероятности узнали при формировании ядра из графа
                    if (p < 0.25) {
                        a = A2;  // Ожидает
                    } else {
                        a = A8;  // Сосредотачивается на действии
                    }
                    
                } else {
                    // не хватает времени
                    // отмечаем д. как частично завершённое и прерываем цикл
                    pa[ i ][ a ] += dt / durationActionRest;
                    dt = -1.0;  // этот трюк порвёт 'for'
                }
                break;


            // Вращает меч
            case A1 :
#ifdef __DEBUG
                printf( "warrior / train / single-sword / turn"
                    " A1\n" );
#endif
                break;


            // Ожидает
            case A2 :
#ifdef __DEBUG
                printf( "warrior / train / single-sword / turn"
                    " A2\n" );
#endif
                break;


            // Переходит в вольную стойку
            case A3 :
#ifdef __DEBUG
                printf( "warrior / train / single-sword / turn"
                    " A3\n" );
#endif
                // это звено завершает стратегию
                // @see Прим. для A0.
                durationActionAll = 1.0;  // s
                durationActionRest = durationActionAll * progressRest;
                if (durationActionRest < dt) {
                    // времени хватает
                    pa[ i ][ a ] = 1.0;
                    dt -= durationActionRest;
                    // в этом звене - единственное действие: Out
                    // отрабатывается в конце
                    a = A_UNDEFINED;  // этот трюк порвёт 'for'

                } else {
                    // не хватает времени
                    pa[ i ][ a ] += dt / durationActionRest;
                    dt = -1.0;
                }
                break;


            // Подымает меч
            case A4 :
#ifdef __DEBUG
                printf( "warrior / train / single-sword / turn"
                    " A4\n" );
#endif
                break;


            // Решает сделать вращение мечом
            case A5 :
#ifdef __DEBUG
                printf( "warrior / train / single-sword / turn"
                    " A5\n" );
#endif
                break;


            // Роняет меч
            case A6 :
#ifdef __DEBUG
                printf( "warrior / train / single-sword / turn"
                    " A6\n" );
#endif
                break;


            // Ругается
            case A7 :
#ifdef __DEBUG
                printf( "warrior / train / single-sword / turn"
                    " A7\n" );
#endif
                break;


            // Сосредотачивается на действии
            case A8 :
#ifdef __DEBUG
                printf( "warrior / train / single-sword / turn"
                    " A8\n" );
#endif
                break;


            default:
#ifdef __DEBUG
                printf( "warrior / train / single-sword / turn"
                    "(!) Action is undefined.\n" );
#endif
                break;

        } // switch ( a )

    } // for ...
    
    
    // как стратегия отработала данное ей время
    // # Всё необходимое отметил switch выше.
    timerest = dt;
    stopAction = a;
}
