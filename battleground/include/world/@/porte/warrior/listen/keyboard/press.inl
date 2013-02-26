// Слушатель нажатий клавиш клавиатуры для Воина.
// @see World::onKeyboardDown()


if ( (ie.id == CL_KEY_RIGHT) || (ie.id == CL_KEY_NUMPAD6) ) {
    // воин получает стратегию движения вправо

    // @test
    std::cout << "Вправо\n";

    // # Управляемый воин у нас один, и он - первый в списке.
    const size_t i = 0;

    const size_t firstFreeCell = 0;
    auto& mc = pt->shortTermMemoryWarriorContent.get()[ i ].content[ firstFreeCell ];
    mc.strategy = STRATEGY_WARRIOR_MOVE_WALK_DIRECTION;
    strategyWarriorMoveWalkDirection_t s = {};
    Topology::da( s.Move,  1 );
    static const direction_t DIRECTION = { 1, 0, 0 };
    s.directionVector = DIRECTION;
    s.distance = 2.0f;
    mc.cell.MoveWalkDirection = s;

} else if (ie.id == CL_KEY_SPACE) {
    // воин получает стратегию выстрела из лука

    // @test
    std::cout << "Выстрел из лука\n";

    // характеристика элемента
    // # Управляемый воин у нас один, и он - первый в списке.
    const size_t i = 0;
    auto& ch = pt->characteristicWarriorContent.get()[ i ];

    // память
    const size_t firstFreeCell = 0;
    auto& mc = pt->shortTermMemoryWarriorContent.get()[ i ].content[ firstFreeCell ];
    
    // стратегия
    mc.strategy = STRATEGY_WARRIOR_SHOOT_BOW;
    strategyWarriorShootBow_t s = {};
    // длительность действий
    Topology::da( s.TakeArrowFromQuiver,  1 );
    Topology::da( s.Nock,                 2 );
    Topology::da( s.Aim,                  2 );
    Topology::da( s.HaveShot,             0.1 );
    // входящие параметры
    s.selfCoord = ch.coord;
    // @todo Брать реальные координаты мыши.
    const coord_t MOUSE_COORD = { 0, 0, 0 };
    s.target = MOUSE_COORD;
    // @todo Искать принадлежащий воину колчан.
    s.quiver = 1;
    // внутренние переменные
    // # Инициируем только те, что отличаются от 0.

    // помещаем иницированную стратегию в память
    mc.cell.ShootBow = s;
}
