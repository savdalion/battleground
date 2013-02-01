// Результат выполнения ядер OpenCL для C++.


// ВОИН
queueCL().enqueueReadBuffer(
    characteristicWarriorBCL,
    CL_TRUE,
    0,
    sizeof( characteristicWarrior_t ) * WARRIOR_COUNT,
    characteristicWarriorContentPtr.get()
);
queueCL().enqueueReadBuffer(
    actionWarriorBCL,
    CL_TRUE,
    0,
    sizeof( actionWarrior_t ) * WARRIOR_COUNT,
    actionWarriorContentPtr.get()
);


// ПОЛЕ БИТВЫ
// @todo optimize Когда элементов группы мало, отдавать алгоритм для CPU.
queueCL().enqueueReadBuffer(
    characteristicBattlegroundBCL,
    CL_TRUE,
    0,
    sizeof( characteristicBattleground_t ) * BATTLEGROUND_COUNT,
    characteristicBattlegroundContentPtr.get()
);
queueCL().enqueueReadBuffer(
    actionBattlegroundBCL,
    CL_TRUE,
    0,
    sizeof( actionBattleground_t ) * BATTLEGROUND_COUNT,
    actionBattlegroundContentPtr.get()
);


queueCL().finish();
