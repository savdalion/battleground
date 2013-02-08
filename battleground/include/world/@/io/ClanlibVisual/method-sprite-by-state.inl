// Методы для работы со спрайтами по состояниям элементов.


/**
* Связывает спрайт с состоянием элемента.
*
* # Спрайт уже должен быть в mKnownSprite.
*/

// ВОИН
inline void insert(
    const roughlyStateWarrior_t& state,
    const keySprite_t& ks
) {
    assert( (mKnownSprite.find( ks ) != mKnownSprite.end())
        && "Спрайт уже должен быть в mKnownSprite." );
    stateNameWarrior.push_back( std::make_pair( state, ks ) );
}




// ПОЛЕ БИТВЫ
inline void insert(
    const roughlyStateBattleground_t& state,
    const keySprite_t& ks
) {
    assert( (mKnownSprite.find( ks ) != mKnownSprite.end())
        && "Спрайт уже должен быть в mKnownSprite." );
    stateNameBattleground.push_back( std::make_pair( state, ks ) );
}




/**
* @return Спрайт согласно текущему состоянию элемента.
*/

// ВОИН
inline CL_Sprite* sprite(
    const characteristicWarrior_t&,
    const strategyWarrior_t&
) {
    // @todo ...
    return nullptr;
}




// ПОЛЕ БИТВЫ
CL_Sprite* sprite(
    const characteristicBattleground_t&,
    const strategyBattleground_t&
) {
    // @todo ...
    return nullptr;
}
