// Инициализация буферов OpenCL.

    
auto pt = mPortulan.lock()->topology();


/**
* Подготавливаем память под параметры ядер OpenCL.
*/
characteristicWarriorBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( characteristicWarrior_t ) * WARRIOR_COUNT,
    pt->characteristicWarriorContent.get(),
    &errorCL
);
strategyWarriorBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( strategyWarrior_t ) * WARRIOR_COUNT,
    pt->strategyWarriorContent.get(),
    &errorCL
);



characteristicBattlegroundBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( characteristicBattleground_t ) * BATTLEGROUND_COUNT,
    pt->characteristicBattlegroundContent.get(),
    &errorCL
);
strategyBattlegroundBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( strategyBattleground_t ) * BATTLEGROUND_COUNT,
    pt->strategyBattlegroundContent.get(),
    &errorCL
);
