// Все методы для воплощения элементов.
// @see incarnate-element.inl
// # Обработка графов вынесена по максимуму в утилиту формирования кода мира.
//   Здесь - результат её работы.


// ВОИН
inline void Engine::incarnateWarrior(
    const characteristicWarrior_t& chara
) {
    // найдём первую свободную ячейку этого вида и поместим туда элемент
    // # Ячейка элемента портулана считается свободной, если её UID == 0.
    auto& pt = portulan()->topology();
    auto itr = pt->characteristicWarriorContent.get();
    const auto itrEnd = itr + WARRIOR_COUNT;
    for ( ; itr != itrEnd; ++itr) {
        if (itr->uid == 0) {
            *itr = chara;
            // # Задаём UID, если в структуре он не задан.
            if (chara.uid == 0) { itr->uid = nextUID(); }
            return;
        }
    }
    throw porte::Exception( "All cells of portulan for 'warrior' are filled." );
}




// ПОЛЕ БИТВЫ
inline void Engine::incarnateBattleground(
    const characteristicBattleground_t& chara
) {
    // найдём первую свободную ячейку этого вида и поместим туда элемент
    // # Ячейка элемента портулана считается свободной, если её UID == 0.
    auto& pt = portulan()->topology();
    auto itr = pt->characteristicBattlegroundContent.get();
    const auto itrEnd = itr + BATTLEGROUND_COUNT;
    for ( ; itr != itrEnd; ++itr) {
        if (itr->uid == 0) {
            *itr = chara;
            // # Задаём UID, если в структуре он не задан.
            if (chara.uid == 0) { itr->uid = nextUID(); }
            return;
        }
    }
    throw porte::Exception( "All cells of portulan for 'battleground' are filled." );
}




