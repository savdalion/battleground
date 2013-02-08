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
    strategyWarriorBCL,
    CL_TRUE,
    0,
    sizeof( strategyWarrior_t ) * WARRIOR_COUNT,
    pt->strategyWarriorContentPtr.get()
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
    strategyBattlegroundBCL,
    CL_TRUE,
    0,
    sizeof( strategyBattleground_t ) * BATTLEGROUND_COUNT,
    pt->strategyBattlegroundContentPtr.get()
);


queueCL().finish();
