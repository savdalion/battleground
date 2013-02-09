// Спрайты по состояниям элементов.
// Храним, ссылаясь на спрайт по ключу из ManagerSprite::knownSprite_t.
// @todo optimize Если элемент не содержит спрайтов, не декларировать его здесь.


// ВОИН
typedef std::pair< roughlyStateWarrior_t, keySprite_t >
    statePairWarrior_t;
typedef std::vector< statePairWarrior_t >
    stateWarrior_t;
stateWarrior_t stateWarrior;


// ПОЛЕ БИТВЫ
typedef std::pair< roughlyStateBattleground_t, keySprite_t >
    statePairBattleground_t;
typedef std::vector< statePairBattleground_t >
    stateBattleground_t;
stateBattleground_t stateBattleground;
