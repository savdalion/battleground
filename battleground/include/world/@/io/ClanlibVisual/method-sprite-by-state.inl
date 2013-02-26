// Методы для работы со спрайтами по состояниям элементов.


/**
* Связывает спрайт с состоянием элемента.
*
* # Спрайт уже должен быть в mKnownSprite.
*/

// ПОЛЕ БИТВЫ
inline void insert(
    const roughlyStateBattleground_t& state,
    const keySprite_t& ks,
    const std::vector< keySprite_t >  l
) {
    insert( ks, l );
    stateBattleground.push_back( std::make_pair( state, ks ) );
}




// ВОИН
inline void insert(
    const roughlyStateWarrior_t& state,
    const keySprite_t& ks,
    const std::vector< keySprite_t >  l
) {
    insert( ks, l );
    stateWarrior.push_back( std::make_pair( state, ks ) );
}




/**
* @return Спрайт согласно текущему состоянию элемента.
*/

// ПОЛЕ БИТВЫ
CL_Sprite* sprite(
    const characteristicBattleground_t&,
    const strategyBattleground_t&
) {
    return sprite( "battleground  Field" );
}




// ВОИН
inline CL_Sprite* sprite(
    const characteristicWarrior_t&  ch,
    const strategyWarrior_t&  st
) {
    return ch.sword ?
        sprite( "warrior  WarriorWithoutSword + SwordReady" ) :
        sprite( "warrior  WarriorWithoutSword - SwordReady" );
}




