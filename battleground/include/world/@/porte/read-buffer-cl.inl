// Результат выполнения ядер OpenCL для C++.


auto pt = portulan()->topology();


// ВОИН
queueCL().enqueueReadBuffer(
    characteristicWarriorBCL,
    CL_TRUE,
    0,
    sizeof( characteristicWarrior_t ) * WARRIOR_COUNT,
    pt->characteristicWarriorContent.get()
);
queueCL().enqueueReadBuffer(
    strategyWarriorBCL,
    CL_TRUE,
    0,
    sizeof( strategyWarrior_t ) * WARRIOR_COUNT,
    pt->strategyWarriorContent.get()
);


// ПОЛЕ БИТВЫ
// @todo optimize Когда элементов группы мало, отдавать алгоритм для CPU.
queueCL().enqueueReadBuffer(
    characteristicBattlegroundBCL,
    CL_TRUE,
    0,
    sizeof( characteristicBattleground_t ) * BATTLEGROUND_COUNT,
    pt->characteristicBattlegroundContent.get()
);
queueCL().enqueueReadBuffer(
    strategyBattlegroundBCL,
    CL_TRUE,
    0,
    sizeof( strategyBattleground_t ) * BATTLEGROUND_COUNT,
    pt->strategyBattlegroundContent.get()
);


queueCL().finish();
