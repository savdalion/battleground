// Спрайты по состояниям элементов.
// Храним, ссылаясь на спрайт по ключу из ManagerSprite::knownSprite_t.
// @todo optimize Если элемент не содержит спрайтов, не декларировать его здесь.


// СТРЕЛА
typedef std::pair< roughlyStateArrow_t, keySprite_t >
    statePairArrow_t;
typedef std::vector< statePairArrow_t >
    stateArrow_t;
stateArrow_t stateArrow;




// ПОЛЕ БИТВЫ
typedef std::pair< roughlyStateBattleground_t, keySprite_t >
    statePairBattleground_t;
typedef std::vector< statePairBattleground_t >
    stateBattleground_t;
stateBattleground_t stateBattleground;




// КОЛЧАН
typedef std::pair< roughlyStateQuiver_t, keySprite_t >
    statePairQuiver_t;
typedef std::vector< statePairQuiver_t >
    stateQuiver_t;
stateQuiver_t stateQuiver;




// ВОИН
typedef std::pair< roughlyStateWarrior_t, keySprite_t >
    statePairWarrior_t;
typedef std::vector< statePairWarrior_t >
    stateWarrior_t;
stateWarrior_t stateWarrior;
