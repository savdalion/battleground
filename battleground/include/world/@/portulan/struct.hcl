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

typedef real_t   number_t;
typedef cl_int   integer_t;
typedef real3_t  coord_t;
typedef real3_t  vector_t;
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
typedef number_t   _number_t[ 2 ];
typedef integer_t  _integer_t[ 2 ];

typedef real_t     _real_t[ 2 ];
typedef real3_t    _real3_t[ 2 ];

typedef real3_t    _coord_t[ 2 ];

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
    number_t progress;

    /**
    * Сколько раз было завершено действие или стратегия.
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
    number_t  duration[ 2 ];

    statisticsDo_t  statistics;

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

const number_t  DEFAULT_NUMBER = 0;
const _number_t DEFAULT_MODIFICATOR_NUMBER_2K = { { 0 },  { 1 } };

const real3_t  DEFAULT_REAL3 = { 0, 0, 0 };
const _real3_t DEFAULT_MODIFICATOR_REAL3_2K = { { 0, 0, 0 },  { 1, 1, 1 } };

const coord_t  DEFAULT_COORD = { 0, 0, 0 };
const _coord_t DEFAULT_MODIFICATOR_COORD_2K = { { 0, 0, 0 },  { 1, 1, 1 } };

const direction_t  DEFAULT_DIRECTION = { 0, 0, 0 };
const _direction_t DEFAULT_MODIFICATOR_DIRECTION_2K = { { 0, 0, 0 },  { 1, 1, 1 } };

const extent_t  DEFAULT_EXTENT = { 0, 0, 0 };
const _extent_t DEFAULT_MODIFICATOR_EXTENT_2K = { { 0, 0, 0 },  { 1, 1, 1 } };




/**
* Базовая информация об элементах мира.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Уникальный в рамках мира идентификатор элемента.
    */
    uid_t uid;

    /**
    * Признак, что элемент существует.
    *
    * // # false - признак конца списка.
    */
    bool incarnate;

} base_t;




/**
* Виды элементов мира.
*
* # Разбиты на "характеристики" и "действия" для оптимизации
*   чтения/записи OpenCL.
* # Упорядочены по алфавиту.
*/
// ВОИН
typedef struct __attribute__ ((packed)) {
    coord_t   coord;
    _coord_t  _coord;

    direction_t   direction;
    _direction_t  _direction;

    bool_t   sword;
    _bool_t  _sword;

    number_t   stability;
    _number_t  _stability;

} characteristicWarrior_t;




/**
* Шаблон для перечислений *_ACTION_* (см. ниже).
*/
enum ACTION {
    ACTION_NONE = 0
};




/**
* Стратегии воина.
*/

/**
* Перечисление известных Воину стратегий.
* # Записываются стратегии нижних уровней иерархии (те, что содержат действия).
*/
enum STRATEGY_WARRIOR {
    STRATEGY_WARRIOR_NONE = 0,
    
    STRATEGY_WARRIOR_MOVE_WALK_DIRECTION,
    STRATEGY_WARRIOR_SHOOT_BOW,
    STRATEGY_WARRIOR_TRAINING_SINGLE_SWORD_TURN,
    
    STRATEGY_WARRIOR_last
};


// Движение / Шагом / В заданном направлении
enum MOVE_WALK_DIRECTION_ACTION_WARRIOR {
    MOVE_WALK_DIRECTION_ACTION_WARRIOR_NONE = 0,
    
    MOVE_WALK_DIRECTION_ACTION_WARRIOR_Move,
    
    MOVE_WALK_DIRECTION_ACTION_WARRIOR_last
};




typedef struct __attribute__ ((packed)) {
    action_t  Move;
    statisticsDo_t  statistics;
    // входящие параметры стратегии
    direction_t  directionVector;
    number_t     distance;
    // внутренние переменные стратегии
    number_t     completeDistance;
    direction_t  lastMove;
    
} strategyWarriorMoveWalkDirection_t;




// Выстрел / Из лука
enum SHOOT_BOW_ACTION_WARRIOR {
    SHOOT_BOW_ACTION_WARRIOR_NONE = 0,
    
    SHOOT_BOW_ACTION_WARRIOR_TakeArrowFromQuiver,
    SHOOT_BOW_ACTION_WARRIOR_Nock,
    SHOOT_BOW_ACTION_WARRIOR_Aim,
    SHOOT_BOW_ACTION_WARRIOR_HaveShot,
    
    SHOOT_BOW_ACTION_WARRIOR_last
};




typedef struct __attribute__ ((packed)) {
    action_t  TakeArrowFromQuiver;
    action_t  Nock;
    action_t  Aim;
    action_t  HaveShot;
    statisticsDo_t  statistics;
    // входящие параметры стратегии
    coord_t  selfCoord;
    coord_t  target;
    uid_t    quiver;
    // внутренние переменные стратегии
    direction_t  direction;
    number_t     velocity;
    vector_t     vd;
    // текущее действие в стратегии
    enum SHOOT_BOW_ACTION_WARRIOR current;
    
} strategyWarriorShootBow_t;




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
    statisticsDo_t  statistics;
    // входящие параметры стратегии
    number_t  durationTraining;
    
} strategyWarriorTrainingSingleSwordTurn_t;


// все известные Воину стратегии
typedef struct __attribute__ ((packed)) {
    strategyWarriorMoveWalkDirection_t        MoveWalkDirection;
    strategyWarriorShootBow_t                 ShootBow;
    strategyWarriorTrainingSingleSwordTurn_t  TrainingSingleSwordTurn;
    
} strategyWarrior_t;


// определение минимального размера ячейки памяти для хранения одной стратегии
typedef union __attribute__ ((packed)) {
    strategyWarriorMoveWalkDirection_t        MoveWalkDirection;
    strategyWarriorShootBow_t                 ShootBow;
    strategyWarriorTrainingSingleSwordTurn_t  TrainingSingleSwordTurn;
    
} cellDataStrategyWarrior_t;


/**
* Кратковременная память для хранения стратегий.
*
* # Окончание списка определяет ячейка со strategy == STRATEGY_*_NONE.
* # Память хранит указатель на след. действие в контексте стратегии.
* # Если ук. на след. действие == *_ACTION_*_NONE, стратегия только
*   начала выполняться. Если == *_ACTION_*_last, стратегия завершена.
*/
const cl_uint SHORT_TERM_MEMORY_SIZE = 5 + 1;
typedef struct __attribute__ ((packed)) {
    enum STRATEGY_WARRIOR      strategy;
    cellDataStrategyWarrior_t  cell;
    
    /**
    * След. действие для выполнения в рамках стратегии.
    * Одно из перечислений *_ACTION_*.
    */
    enum ACTION  next;
    
} cellStrategyWarrior_t;


typedef struct __attribute__ ((packed)) {
    cellStrategyWarrior_t  content[ SHORT_TERM_MEMORY_SIZE ];
} shortTermMemoryWarrior_t;


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




// КОЛЧАН
typedef struct __attribute__ ((packed)) {
    integer_t  capacity;
    integer_t  countArrow;
    uid_t      keeper;
} characteristicQuiver_t;


typedef struct __attribute__ ((packed)) {
    action_t  Give;
} strategyQuiverGiveArrow_t;

typedef struct __attribute__ ((packed)) {
    action_t  Take;
} strategyQuiverTakeArrow_t;


typedef struct __attribute__ ((packed)) {
    strategyQuiverGiveArrow_t GiveArrow;
    strategyQuiverTakeArrow_t TakeArrow;
    statisticsDo_t statistics;
} strategyQuiver_t;


typedef struct __attribute__ ((packed)) {
    characteristicQuiver_t  characteristic[ 2 ];
    strategyQuiver_t        strategy[ 2 ];
} roughlyStateQuiver_t;




// СТРЕЛА
typedef struct __attribute__ ((packed)) {
    coord_t   coord;
    vector_t  velocity;
} characteristicArrow_t;


typedef struct __attribute__ ((packed)) {
    action_t  Go;
} strategyArrowMoveFly_t;


typedef struct __attribute__ ((packed)) {
    strategyArrowMoveFly_t Fly;
    statisticsDo_t statistics;
} strategyArrow_t;


typedef struct __attribute__ ((packed)) {
    characteristicArrow_t  characteristic[ 2 ];
    strategyArrow_t        strategy[ 2 ];
} roughlyStateArrow_t;




/**
* Общая структура для всех элементов портулана.
*//* - Отказ в пользу отдельных структур, чтобы не усложнять пилотную стадию.
       @todo optimize Посмотреть в сторону одной структуры для всех элементов.
typedef struct {
    warrior_t       warrior;
    battleground_t  battleground;
} element_t;
*/




/**
* Элементы портулана по группам.
* Общее кол-во получено из 'incarnation'.
*
* # Длину списка элементов задаёт элемент с uid == 0.
* # Выравниваем кол-ва для оптимального быстродействия OpenCL.
*/
const cl_uint ALIGN_SIZE = 64;

const cl_uint WARRIOR_COUNT = 100;
const cl_uint WARRIOR_OPTIMIZE_COUNT =
    (1 + WARRIOR_COUNT / ALIGN_SIZE) * ALIGN_SIZE;
typedef characteristicWarrior_t*   characteristicWarriorContent_t;
typedef strategyWarrior_t*         strategyWarriorContent_t;
const cl_uint WARRIOR_SIZE_SHORT_TERM_MEMORY = 5;
typedef shortTermMemoryWarrior_t*  shortTermMemoryWarriorContent_t;


const cl_uint BATTLEGROUND_COUNT = 1;
const cl_uint BATTLEGROUND_OPTIMIZE_COUNT =
    (1 + BATTLEGROUND_COUNT / ALIGN_SIZE) * ALIGN_SIZE;
typedef characteristicBattleground_t*  characteristicBattlegroundContent_t;
typedef strategyBattleground_t*        strategyBattlegroundContent_t;


const cl_uint QUIVER_COUNT = 1;
const cl_uint QUIVER_OPTIMIZE_COUNT =
    (1 + QUIVER_COUNT / ALIGN_SIZE) * ALIGN_SIZE;
typedef characteristicQuiver_t*  characteristicQuiverContent_t;
typedef strategyQuiver_t*        strategyQuiverContent_t;


const cl_uint ARROW_COUNT = 1000;
const cl_uint ARROW_OPTIMIZE_COUNT =
    (1 + ARROW_COUNT / ALIGN_SIZE) * ALIGN_SIZE;
typedef characteristicArrow_t*  characteristicArrowContent_t;
typedef strategyArrow_t*        strategyArrowContent_t;




/**
* Порция времени, выделяемая на стратегию, с.
*
* @todo optimize Передавать ядрам define-константы при компиляции ( -D ).
*/
const real_t TIMESTEP = 1.0;
