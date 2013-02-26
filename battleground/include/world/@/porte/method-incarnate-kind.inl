// Все методы для воплощения элементов.
// @see incarnate-element.inl
// # Обработка графов вынесена по максимуму в утилиту формирования кода мира.
//   Здесь - результат её работы.
// @require wrapper.h


// СТРЕЛА
inline void Engine::incarnateArrow(
    const Arrow& kind,
    uid_t uid = 0
) {
    auto& pt = portulan()->topology();
    base_t* bp = pt->baseArrowContent.get();
    for ( ; bp->incarnate; ++bp) {
    }
    const size_t i =
        std::distance( pt->baseArrowContent.get(), bp );
    if (i >= ARROW_COUNT) {
        throw porte::Exception( "All cells of portulan for 'arrow' are filled." );
    }
    pt->characteristicArrowContent.get()[ i ] = kind.ch;
    const base_t base = {
        (uid == 0) ? nextUID() : uid,
        true
    };
    pt->baseArrowContent.get()[ i ] = base;
}




// ПОЛЕ БИТВЫ
inline void Engine::incarnateBattleground(
    const Battleground& kind,
    uid_t uid = 0
) {
    auto& pt = portulan()->topology();
    base_t* bp = pt->baseBattlegroundContent.get();
    for ( ; bp->incarnate; ++bp) {
    }
    const size_t i =
        std::distance( pt->baseBattlegroundContent.get(), bp );
    if (i >= BATTLEGROUND_COUNT) {
        throw porte::Exception( "All cells of portulan for 'battleground' are filled." );
    }
    pt->characteristicBattlegroundContent.get()[ i ] = kind.ch;
    const base_t base = {
        (uid == 0) ? nextUID() : uid,
        true
    };
    pt->baseBattlegroundContent.get()[ i ] = base;
}




// КОЛЧАН
inline void Engine::incarnateQuiver(
    const Quiver& kind,
    uid_t uid = 0
) {
    auto& pt = portulan()->topology();
    base_t* bp = pt->baseQuiverContent.get();
    for ( ; bp->incarnate; ++bp) {
    }
    const size_t i =
        std::distance( pt->baseQuiverContent.get(), bp );
    if (i >= QUIVER_COUNT) {
        throw porte::Exception( "All cells of portulan for 'quiver' are filled." );
    }
    pt->characteristicQuiverContent.get()[ i ] = kind.ch;
    const base_t base = {
        (uid == 0) ? nextUID() : uid,
        true
    };
    pt->baseQuiverContent.get()[ i ] = base;
}




// ВОИН
inline void Engine::incarnateWarrior(
    const Warrior& kind,
    uid_t uid = 0
) {
    // найдём первую свободную ячейку этого вида и поместим туда элемент
    // # Ячейка элемента портулана считается свободной, когда incarnate == false.
    auto& pt = portulan()->topology();
    base_t* bp = pt->baseWarriorContent.get();
    for ( ; bp->incarnate; ++bp) {
    }
    const size_t i =
        std::distance( pt->baseWarriorContent.get(), bp );
    if (i >= WARRIOR_COUNT) {
        throw porte::Exception( "All cells of portulan for 'warrior' are filled." );
    }
    pt->characteristicWarriorContent.get()[ i ] = kind.ch;
    const base_t base = {
        (uid == 0) ? nextUID() : uid,
        true
    };
    pt->baseWarriorContent.get()[ i ] = base;
}
