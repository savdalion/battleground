// Результат выполнения ядер OpenCL для C++.


auto pt = portulan()->topology();


// ВОИН
queueCL().enqueueReadBuffer(
    characteristicWarriorBCL,
    CL_TRUE,
    0,
    sizeof( characteristicWarrior_t ) * WARRIOR_COUNT,
    pt->characteristicWarriorContentPtr.get()
);
queueCL().enqueueReadBuffer(
    actionWarriorBCL,
    CL_TRUE,
    0,
    sizeof( actionWarrior_t ) * WARRIOR_COUNT,
    pt->actionWarriorContentPtr.get()
);


// ПОЛЕ БИТВЫ
// @todo optimize Когда элементов группы мало, отдавать алгоритм для CPU.
queueCL().enqueueReadBuffer(
    characteristicBattlegroundBCL,
    CL_TRUE,
    0,
    sizeof( characteristicBattleground_t ) * BATTLEGROUND_COUNT,
    pt->characteristicBattlegroundContentPtr.get()
);
queueCL().enqueueReadBuffer(
    actionBattlegroundBCL,
    CL_TRUE,
    0,
    sizeof( actionBattleground_t ) * BATTLEGROUND_COUNT,
    pt->actionBattlegroundContentPtr.get()
);


queueCL().finish();
