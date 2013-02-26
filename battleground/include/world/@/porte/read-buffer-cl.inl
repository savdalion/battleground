// Результат выполнения ядер OpenCL для C++.


// СТРЕЛА
queueCL().enqueueReadBuffer(
    baseArrowBCL,
    CL_TRUE,
    0,
    sizeof( base_t ) * ARROW_OPTIMIZE_COUNT,
    pt->baseArrowContent.get()
);
queueCL().enqueueReadBuffer(
    characteristicArrowBCL,
    CL_TRUE,
    0,
    sizeof( characteristicArrow_t ) * ARROW_OPTIMIZE_COUNT,
    pt->characteristicArrowContent.get()
);
queueCL().enqueueReadBuffer(
    strategyArrowBCL,
    CL_TRUE,
    0,
    sizeof( strategyArrow_t ) * ARROW_OPTIMIZE_COUNT,
    pt->strategyArrowContent.get()
);




// ПОЛЕ БИТВЫ
// @todo optimize Когда элементов группы мало, отдавать алгоритм для CPU.
queueCL().enqueueReadBuffer(
    baseBattlegroundBCL,
    CL_TRUE,
    0,
    sizeof( base_t ) * BATTLEGROUND_OPTIMIZE_COUNT,
    pt->baseBattlegroundContent.get()
);
queueCL().enqueueReadBuffer(
    characteristicBattlegroundBCL,
    CL_TRUE,
    0,
    sizeof( characteristicBattleground_t ) * BATTLEGROUND_OPTIMIZE_COUNT,
    pt->characteristicBattlegroundContent.get()
);
queueCL().enqueueReadBuffer(
    strategyBattlegroundBCL,
    CL_TRUE,
    0,
    sizeof( strategyBattleground_t ) * BATTLEGROUND_OPTIMIZE_COUNT,
    pt->strategyBattlegroundContent.get()
);




// КОЛЧАН
queueCL().enqueueReadBuffer(
    baseQuiverBCL,
    CL_TRUE,
    0,
    sizeof( base_t ) * QUIVER_OPTIMIZE_COUNT,
    pt->baseQuiverContent.get()
);
queueCL().enqueueReadBuffer(
    characteristicQuiverBCL,
    CL_TRUE,
    0,
    sizeof( characteristicQuiver_t ) * QUIVER_OPTIMIZE_COUNT,
    pt->characteristicQuiverContent.get()
);
queueCL().enqueueReadBuffer(
    strategyQuiverBCL,
    CL_TRUE,
    0,
    sizeof( strategyQuiver_t ) * QUIVER_OPTIMIZE_COUNT,
    pt->strategyQuiverContent.get()
);




// ВОИН
queueCL().enqueueReadBuffer(
    baseWarriorBCL,
    CL_TRUE,
    0,
    sizeof( base_t ) * WARRIOR_OPTIMIZE_COUNT,
    pt->baseWarriorContent.get()
);
queueCL().enqueueReadBuffer(
    characteristicWarriorBCL,
    CL_TRUE,
    0,
    sizeof( characteristicWarrior_t ) * WARRIOR_OPTIMIZE_COUNT,
    pt->characteristicWarriorContent.get()
);
queueCL().enqueueReadBuffer(
    strategyWarriorBCL,
    CL_TRUE,
    0,
    sizeof( strategyWarrior_t ) * WARRIOR_OPTIMIZE_COUNT,
    pt->strategyWarriorContent.get()
);




queueCL().finish();
