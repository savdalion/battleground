// Инициализация буферов OpenCL.

    
auto& pt = mPortulan.lock()->topology();


/**
* Подготавливаем память под параметры ядер OpenCL.
*/
// СТРЕЛА
baseArrowBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( base_t ) * ARROW_OPTIMIZE_COUNT,
    pt->baseArrowContent.get(),
    &errorCL
);
characteristicArrowBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( characteristicArrow_t ) * ARROW_OPTIMIZE_COUNT,
    pt->characteristicArrowContent.get(),
    &errorCL
);
strategyArrowBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( strategyArrow_t ) * ARROW_OPTIMIZE_COUNT,
    pt->strategyArrowContent.get(),
    &errorCL
);




// ПОЛЕ БИТВЫ
baseBattlegroundBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( base_t ) * BATTLEGROUND_OPTIMIZE_COUNT,
    pt->baseBattlegroundContent.get(),
    &errorCL
);
characteristicBattlegroundBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( characteristicBattleground_t ) * BATTLEGROUND_OPTIMIZE_COUNT,
    pt->characteristicBattlegroundContent.get(),
    &errorCL
);
strategyBattlegroundBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( strategyBattleground_t ) * BATTLEGROUND_OPTIMIZE_COUNT,
    pt->strategyBattlegroundContent.get(),
    &errorCL
);




// КОЛЧАН
baseQuiverBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( base_t ) * QUIVER_OPTIMIZE_COUNT,
    pt->baseQuiverContent.get(),
    &errorCL
);
characteristicQuiverBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( characteristicQuiver_t ) * QUIVER_OPTIMIZE_COUNT,
    pt->characteristicQuiverContent.get(),
    &errorCL
);
strategyQuiverBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( strategyQuiver_t ) * QUIVER_OPTIMIZE_COUNT,
    pt->strategyQuiverContent.get(),
    &errorCL
);




// ВОИН
baseWarriorBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( base_t ) * WARRIOR_OPTIMIZE_COUNT,
    pt->baseWarriorContent.get(),
    &errorCL
);
characteristicWarriorBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( characteristicWarrior_t ) * WARRIOR_OPTIMIZE_COUNT,
    pt->characteristicWarriorContent.get(),
    &errorCL
);
strategyWarriorBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( strategyWarrior_t ) * WARRIOR_OPTIMIZE_COUNT,
    pt->strategyWarriorContent.get(),
    &errorCL
);
