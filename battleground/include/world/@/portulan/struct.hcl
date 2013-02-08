// Портулан для OpenCL.
// @require Для С++: CL/cl.hpp.
// @require Для OpenCL: restruct.hcl.


// # Типы данных С++ переопределены в restruct.hcl.
// # Здесь определяем некоторые "особые" для C++.

// # Для булева типа нельзя использовать cl_bool, если хотим видеть
//   в структуре естественный bool вместо unsigned int от OpenCL.
typedef bool  bool_t;

typedef cl_float    real_t;
typedef cl_float2   real2_t;
typedef cl_float3   real3_t;
typedef cl_float4   real4_t;

typedef real3_t  coord_t;
typedef real3_t  direction_t;
typedef real3_t  extent_t;




/**
* Уникальный в *рамках мира* идентификатор элемента.
*/
typedef cl_int  uid_t;



/**
* Модификаторы характеристик.
*/
// булевый модификатор - это инверсия, если модификатор принял значение true
typedef bool  _bool_t;

// модификатор числа - это пара значенй
//   1 для прибавления к базовой характеристике
//   2 для умножения на базовую характеристику
typedef real_t   _real_t[ 2 ];
typedef real3_t  _real3_t[ 2 ];

typedef real3_t  _coord_t[ 2 ];

// модификатор направления - это углы поворота по 3 коорд. осям относительно
// текущего направления с теми же правилами, что для модификатора числа;
// разница только в расчётной формуле относит. базового значения: здесь
// второе значение - это % (непер) поворота на 360: 0 градусов = 1.0 (0%),
// плюс - против часовой, минус - по часовой
typedef real3_t  _direction_t[ 2 ];

typedef real3_t  _extent_t[ 2 ];




/**
* Статистика выполнения действия или стратегии.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * На сколько действие (или стратегия) выполнено.
    *
    * # Лежит в диапазоне [ <= 0.0 не выполняется .. выполняется .. >= 1.0 выполнено ].
    */
    real_t progress;

    /**
    * Сколько раз было завершено действие (или стратегия).
    */
    cl_uint count;

} statisticsDo_t;





/**
* Действие.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Длительность действия, c.
    * Задаётся в виде диапазона значений.
    */
    real_t duration[ 2 ];

    statisticsDo_t statistics;

} action_t;




/**
* Немного констант.
*
* @todo optimize Вынести в #define при компиляции ядра.
*/
const bool_t DEFAULT_BOOL = false;
const _bool_t DEFAULT_MODIFICATOR_BOOL = false;

const real_t  DEFAULT_REAL = 0;
const _real_t DEFAULT_MODIFICATOR_REAL_2K = { { 0 },  { 1 } };

const real3_t  DEFAULT_REAL3 = { 0, 0, 0 };
const _real3_t DEFAULT_MODIFICATOR_REAL3_2K = { { 0, 0, 0 },  { 1, 1, 1 } };

const coord_t  DEFAULT_COORD = { 0, 0, 0 };
const _coord_t DEFAULT_MODIFICATOR_COORD_2K = { { 0, 0, 0 },  { 1, 1, 1 } };

const direction_t  DEFAULT_DIRECTION = { 0, 0, 0 };
const _direction_t DEFAULT_MODIFICATOR_DIRECTION_2K = { { 0, 0, 0 },  { 1, 1, 1 } };

const extent_t  DEFAULT_EXTENT = { 0, 0, 0 };
const _extent_t DEFAULT_MODIFICATOR_EXTENT_2K = { { 0, 0, 0 },  { 1, 1, 1 } };




/**
* Виды элементов мира.
*
* # Разбиты на "характеристики" и "действия" для оптимизации
*   чтения/записи OpenCL.
* # Упорядочены по алфавиту.
*/
// ВОИН
typedef struct __attribute__ ((packed)) {
    // обязательные
    uid_t uid;

    // дополнительные
    coord_t   coord;
    _coord_t  _coord;

    direction_t   direction;
    _direction_t  _direction;

    bool_t   sword;
    _bool_t  _sword;

    real_t   stability;
    _real_t  _stability;

} characteristicWarrior_t;


/**
* Стратегии воина.
*/
// Тренировка / С одноручным мечом / Вращение меча
typedef struct __attribute__ ((packed)) {
    action_t  Concentrate;
    action_t  DecisionTurnSword;
    action_t  IntoCombatPosition;
    action_t  IntoFreePosition;
    action_t  PickUpSword;
    action_t  PlunkSword;
    action_t  Swear;
    action_t  TurnSword;
    action_t  Wait;
} strategyWarriorTurn_t;


typedef struct __attribute__ ((packed)) {
    strategyWarriorTurn_t Turn;
    statisticsDo_t statistics;
} strategyWarriorSingleSword_t;


typedef struct __attribute__ ((packed)) {
    strategyWarriorSingleSword_t SingleSword;
    statisticsDo_t statistics;
} strategyWarriorTraining_t;


typedef struct __attribute__ ((packed)) {
    strategyWarriorTraining_t Training;
    statisticsDo_t statistics;
} strategyWarrior_t;


/**
* Примерное состояние элемента портулана.
* Помогает, например, выбрать спрайт, наиболее подходящий этому состоянию.
*
* # Хранится в виде пар значений, декларирующих диапазон для проверки.
*/
typedef struct __attribute__ ((packed)) {
    characteristicWarrior_t  characteristic[ 2 ];
    strategyWarrior_t        strategy[ 2 ];
} roughlyStateWarrior_t;




// ПОЛЕ БИТВЫ
typedef struct __attribute__ ((packed)) {
    // обязательные
    uid_t uid;

    // дополнительные
    extent_t   extent;
    _extent_t  _extent;

} characteristicBattleground_t;


typedef struct __attribute__ ((packed)) {
    action_t  CancelCoord;
    action_t  VerifyCoord;
} strategyBattlegroundCommon_t;


typedef struct __attribute__ ((packed)) {
    strategyBattlegroundCommon_t Common;
    statisticsDo_t statistics;
} strategyBattleground_t;


typedef struct __attribute__ ((packed)) {
    characteristicBattleground_t  characteristic[ 2 ];
    strategyBattleground_t        strategy[ 2 ];
} roughlyStateBattleground_t;




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
* Общее кол-во получено из графов 'incarnation'.
* @todo optimize fine Выравнивать кол-ва для оптимального быстродействия OpenCL.
*/
const cl_uint WARRIOR_COUNT = 100;
typedef characteristicWarrior_t*  characteristicWarriorContent_t;
typedef strategyWarrior_t*  strategyWarriorContent_t;

const cl_uint BATTLEGROUND_COUNT = 1;
typedef characteristicBattleground_t*  characteristicBattlegroundContent_t;
typedef strategyBattleground_t*  strategyBattlegroundContent_t;




/**
* Порция времени, выделяемая на стратегию, с.
*
* @todo optimize Передавать ядрам define-константы при компиляции ( -D ).
*/
const real_t TIMESTEP = 1.0;
