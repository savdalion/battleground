// Визуализация элемента 'ПОЛЕ БИТВЫ' с помощью Clanlib.
// @see ClanlibVisual::operator<<()


for (size_t i = 0; i < BATTLEGROUND_COUNT; ++i) {
    const characteristicBattleground_t& ch =
        pt->characteristicBattlegroundContent.get()[ i ];
    if ( !ch.incarnate ) {
        // # Пустой элемент - признак конца списка.
        break;
    }

    const strategyBattleground_t& st =
        pt->strategyBattlegroundContent.get()[ i ];
    CL_Sprite* s = managerSprite()->sprite( ch, st );
    const typelib::coord2_t nc =
        fromPhysics( 0, 0 );
    s->draw( gc(), nc.x, nc.y );
    s->update();

} // for (size_t i = 0; i < BATTLEGROUND_COUNT; ++i)



