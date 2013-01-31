// Портулан для OpenCL.
// @require Для С++: CL/cl.hpp.
// @require Для OpenCL: restruct.hcl.


// # Типы данных С++ переопределены в restruct.hcl.
// # Здесь определяем некоторые "особые" для C++.
typedef cl_float    real_t;
typedef cl_float2   real2_t;
typedef cl_float3   real3_t;
typedef cl_float4   real4_t;

typedef real3_t  direction_t;




/**
* Модификаторы характеристик.
*/
// булевый модификатор - это инверсия, если модификатор принял значение false
typedef cl_bool  _bool;

// модификатор числа - это пара значенй
//   1 для прибавления к базовой характеристике
//   2 для умножения на базовую характеристику
typedef real_t  _real_t;
typedef real3_t  _real3_t[ 2 ];

// модификатор направления - это углы поворота по 3 коорд. осям относительно
// текущего направления с теми же правилами, что для модификатора числа;
// разница только в расчётной формуле относит. базового значения: здесь
// второе значение - это % поворота на 360: 360 = 1.0 (100%), плюс - против
// часовой, минус - по часовой
typedef real3_t  _direction_t[ 2 ];




/**
* Действие элемента.
* # Лежит в диапазоне [ 0.0 не выполняется .. 0.n выполняется .. 1.0 выполнено ].
*/
typedef real_t action_t;




/**
* Группы элементов мира.
*
* # Разбиты на "характеристики" и "действия" для оптимизации чтения/записи
*   OpenCL.
* # Упорядочены по алфавиту.
*/
// ВОИН
typedef struct {
    real3_t   coord;
    _real3_t  _coord;

    direction_t   direction;
    _direction_t  _direction;

    cl_bool   sword;
    _bool  _sword;

    real_t  stability;
    _real_t  _stability;

} characteristicWarrior_t;


typedef struct {
    action_t  turnSword;
    action_t  wait;
    action_t  intoCombatPosition;
    action_t  intoFreePosition;
    action_t  pickUpSword;
    action_t  decisionTurnSword;
    action_t  plunkSword;
    action_t  swear;
    action_t  concentrate;
} actionWarrior_t;




// ПОЛЕ БИТВЫ
typedef struct {
    real3_t   size;
    _real3_t  _size;
} characteristicBattleground_t;


typedef struct {
    action_t  verifyCoord;
    action_t  cancelCoord;
} actionBattleground_t;




/**
* Общая структура для всех элементов портулана.
*//* - Отказ. в пользу отдельных структур, чтобы не усложнять пилотную стадию.
       @todo optimize Посмотреть в сторону одной структуры для всех элементов.
typedef struct {
    warrior_t       warrior;
    battleground_t  battleground;
} element_t;
*/




/**
* Элементы портулана по группам.
* Общее кол-во получено из графов.
* @todo optimize fine Выравнивать структуры для оптимального быстродействия OpenCL.
*/
const cl_uint WARRIOR_COUNT = 100;
typedef characteristicWarrior_t*  characteristicWarriorContent_t;
typedef actionWarrior_t*  actionWarriorContent_t;

const cl_uint BATTLEGROUND_COUNT = 1;
typedef characteristicBattleground_t*  characteristicBattlegroundContent_t;
typedef actionBattleground_t*  actionBattlegroundContent_t;




/**
* Порция времени, выделяемая на стратегию, с.
*
* @todo optimize Передавать ядрам define-константы при компиляции ( -D ).
*/
const real_t TIMESTEP = 1.0;
