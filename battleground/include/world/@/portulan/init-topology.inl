// Инициализация топологии портулана.


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
