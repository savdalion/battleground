// Инициализация буферов OpenCL.


auto pt = portulan()->topology();


/**
* Подготавливаем память под параметры ядер OpenCL.
*/
characteristicWarriorBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( characteristicWarrior_t ) * WARRIOR_COUNT,
    pt->characteristicWarriorContentPtr.get(),
    &errorCL
);
actionWarriorBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( actionWarrior_t ) * WARRIOR_COUNT,
    pt->actionWarriorContentPtr.get(),
    &errorCL
);



characteristicBattlegroundBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( characteristicBattleground_t ) * BATTLEGROUND_COUNT,
    pt->characteristicBattlegroundContentPtr.get(),
    &errorCL
);
actionBattlegroundBCL = cl::Buffer(
    contextCL(),
    CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
    sizeof( actionBattleground_t ) * BATTLEGROUND_COUNT,
    pt->actionBattlegroundContentPtr.get(),
    &errorCL
);
