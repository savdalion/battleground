// Инициализация топологии портулана.


// резервируем место для элементов в куче
// инициализируем структуры элементов нулями
// задаём длительность действий


// СТРЕЛА
{
    baseArrowContent =
        createContent< base_t, ARROW_OPTIMIZE_COUNT >();
    characteristicArrowContent =
        createContent< characteristicArrow_t, ARROW_OPTIMIZE_COUNT >();
    strategyArrowContent =
        createContent< strategyArrow_t, ARROW_OPTIMIZE_COUNT >();
}




// ПОЛЕ БИТВЫ
{
    baseBattlegroundContent =
        createContent< base_t, BATTLEGROUND_OPTIMIZE_COUNT >();
    characteristicBattlegroundContent =
        createContent< characteristicBattleground_t, BATTLEGROUND_OPTIMIZE_COUNT >();
    strategyBattlegroundContent =
        createContent< strategyBattleground_t, BATTLEGROUND_OPTIMIZE_COUNT >();
}




// КОЛЧАН
{
    baseQuiverContent =
        createContent< base_t, QUIVER_OPTIMIZE_COUNT >();
    characteristicQuiverContent =
        createContent< characteristicQuiver_t, QUIVER_OPTIMIZE_COUNT >();
    strategyQuiverContent =
        createContent< strategyQuiver_t, QUIVER_OPTIMIZE_COUNT >();
}




// ВОИН
{
    baseWarriorContent =
        createContent< base_t, WARRIOR_OPTIMIZE_COUNT >();
    characteristicWarriorContent =
        createContent< characteristicWarrior_t, WARRIOR_OPTIMIZE_COUNT >();
    strategyWarriorContent =
        createContent< strategyWarrior_t, WARRIOR_OPTIMIZE_COUNT >();
    /* - # Стратегии инициируем в начале их выполнения. См. press.inl.
    for (size_t i = 0; i < WARRIOR_OPTIMIZE_COUNT; ++i) {
        strategyWarrior_t& strategy = strategyWarriorContent.get()[ i ];
        // Движение / Шагом / В заданном направлении
        {
            auto& s = strategy.MoveWalkDirection;
            da( s.Move,  1 );
        }
        // Тренировка / С одноручным мечом / Вращение меча
        {
            auto& s = strategy.TrainingSingleSwordTurn;
            da( s.Concentrate,  4, 5 );
            //da( s.DecisionTurnSword,  0 );
            da( s.IntoCombatPosition,  1 );
            da( s.IntoFreePosition,  1 );
            da( s.PickUpSword,  3, 5 );
            //da( s.PlunkSword,  0 );
            da( s.Swear,  1 );
            da( s.TurnSword,  1 );
            da( s.Wait,  2, 5 );
        }
    }
    */
    shortTermMemoryWarriorContent = createContent<
        shortTermMemoryWarrior_t,
        WARRIOR_SIZE_SHORT_TERM_MEMORY * WARRIOR_OPTIMIZE_COUNT
    >();
}




// # Образы элементов декларируются движками образов. См. 'io'.




