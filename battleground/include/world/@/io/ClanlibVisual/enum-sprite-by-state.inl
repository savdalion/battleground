// Спрайты по состояниям элементов.
// Храним, ссылаясь на спрайт по ключу из ManagerSprite::knownSprite_t.
// @todo optimize Если элемент не содержит спрайтов, не декларировать его здесь.


// ВОИН
typedef std::pair< roughlyStateWarrior_t, keySprite_t >
    stateNamePairWarrior_t;
typedef std::vector< stateNamePairWarrior_t >
    stateNameWarrior_t;
stateNameWarrior_t stateNameWarrior;


// ПОЛЕ БИТВЫ
typedef std::pair< roughlyStateBattleground_t, keySprite_t >
    stateNamePairBattleground_t;
typedef std::vector< stateNamePairBattleground_t >
    stateNameBattleground_t;
stateNameBattleground_t stateNameBattleground;
