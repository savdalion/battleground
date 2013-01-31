// Инициализация буферов OpenCL.


    /**
    * Резервируем место для элементов в куче.
    * Инициализируем структуры элементов нулями.
    */
    characteristicWarriorContentPtr =
        createContent< characteristicWarrior_t, WARRIOR_COUNT >();
    actionWarriorContentPtr =
        createContent< actionWarrior_t, WARRIOR_COUNT >();


    characteristicBattlegroundContentPtr =
        createContent< characteristicBattleground_t, BATTLEGROUND_COUNT >();
    actionBattlegroundContentPtr =
        createContent< actionBattleground_t, BATTLEGROUND_COUNT >();




    /**
    * Подготавливаем память под параметры ядер OpenCL.
    */
    characteristicWarriorBCL = cl::Buffer(
        contextCL(),
        CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
        sizeof( characteristicWarrior_t ) * WARRIOR_COUNT,
        characteristicWarriorContentPtr.get(),
        &errorCL
    );
    actionWarriorBCL = cl::Buffer(
        contextCL(),
        CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
        sizeof( actionWarrior_t ) * WARRIOR_COUNT,
        actionWarriorContentPtr.get(),
        &errorCL
    );



    characteristicBattlegroundBCL = cl::Buffer(
        contextCL(),
        CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
        sizeof( characteristicBattleground_t ) * BATTLEGROUND_COUNT,
        characteristicBattlegroundContentPtr.get(),
        &errorCL
    );
    actionBattlegroundBCL = cl::Buffer(
        contextCL(),
        CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
        sizeof( actionBattleground_t ) * BATTLEGROUND_COUNT,
        actionBattlegroundContentPtr.get(),
        &errorCL
    );
