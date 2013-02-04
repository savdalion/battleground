// Инициализация топологии портулана.


// резервируем место для элементов в куче
// инициализируем структуры элементов нулями
characteristicWarriorContentPtr =
    createContent< characteristicWarrior_t, WARRIOR_COUNT >();
actionWarriorContentPtr =
    createContent< actionWarrior_t, WARRIOR_COUNT >();


characteristicBattlegroundContentPtr =
    createContent< characteristicBattleground_t, BATTLEGROUND_COUNT >();
actionBattlegroundContentPtr =
    createContent< actionBattleground_t, BATTLEGROUND_COUNT >();




// образы элементов

// визуальный образ - ВОИН
{
    std::unique_ptr< ClanlibVisualImage >  image(
        new ClanlibVisualImage()
    );

    visualImageWarriorContent
}
