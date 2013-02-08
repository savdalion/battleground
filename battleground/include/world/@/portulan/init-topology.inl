// Инициализация топологии портулана.


// резервируем место для элементов в куче
// инициализируем структуры элементов нулями
// задаём длительность действий

// ВОИН
{
    characteristicWarriorContentPtr =
        createContent< characteristicWarrior_t, WARRIOR_COUNT >();
    strategyWarriorContentPtr =
        createContent< strategyWarrior_t, WARRIOR_COUNT >();
    for (size_t i = 0; i < WARRIOR_COUNT; ++i) {
        strategyWarrior_t& common = strategyWarriorContentPtr.get()[ i ];
        // Тренировка / С одноручным мечом / Вращение меча
        {
            strategyWarriorTurn_t& strategy =
                common.Training.SingleSword.Turn;
            da( strategy.Concentrate,  4, 5 );
            //da( strategy.DecisionTurnSword,  0, 0 );
            da( strategy.IntoCombatPosition,  1, 1 );
            da( strategy.IntoFreePosition,  1, 1 );
            da( strategy.PickUpSword,  3, 5 );
            //da( strategy.PlunkSword,  0, 0 );
            da( strategy.Swear,  1, 1 );
            da( strategy.TurnSword,  1, 1 );
            da( strategy.Wait,  2, 5 );
        }
    }
}




// ПОЛЕ БИТВЫ
{
    characteristicBattlegroundContentPtr =
        createContent< characteristicBattleground_t, BATTLEGROUND_COUNT >();
    strategyBattlegroundContentPtr =
        createContent< strategyBattleground_t, BATTLEGROUND_COUNT >();
}




// # Образы элементов декларируются движками образов. См. 'io'.




