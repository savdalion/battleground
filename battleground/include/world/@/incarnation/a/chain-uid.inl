// Связывает зависимые элементы.
// # Вызывается после воплощения элементов.


#if 0
@todo ...
// КОЛЧАН воина Armand
{
    // колчан
    auto a = std::find_if(
        std::begin( characteristicQuiverContent ),
        std::begin( characteristicQuiverContent ) + QUIVER_COUNT,
        [] ( const Quiver& e ) {
            // найдём первый свободный колчан
            return (e.keeper == 0);
    } );
    assert( (a != (std::begin( characteristicQuiverContent ) + QUIVER_COUNT))
        && "Элемент (колчан) не найден." );

    // воин
    auto b = std::find_if(
        std::begin( characteristicWarriorContent ),
        std::begin( characteristicWarriorContent ) + WARRIOR_COUNT,
        [] ( const Warrior& e ) {
            // найдём первого воина
            return true;
    } );
    assert( (b != (std::begin( characteristicWarriorContent ) + WARRIOR_COUNT))
        && "Элемент (воин) не найден." );

    a->keeper = b->uid;
}
#endif
