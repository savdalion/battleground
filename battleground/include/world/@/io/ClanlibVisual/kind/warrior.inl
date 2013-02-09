// Визуализация элемента 'ВОИН' с помощью Clanlib.
// @see ClanlibVisual::operator<<()


for (size_t i = 0; i < WARRIOR_COUNT; ++i) {
    const characteristicWarrior_t& ch =
        pt->characteristicWarriorContent.get()[ i ];
    if ( !ch.incarnate ) {
        // # Пустой элемент - признак конца списка.
        break;
    }

    const strategyWarrior_t& st =
        pt->strategyWarriorContent.get()[ i ];
    CL_Sprite* s = managerSprite()->sprite( ch, st );
    const typelib::coord2_t nc =
        fromPhysics( ch.coord.s[ 0 ],  ch.coord.s[ 1 ] );
    s->draw( gc(), nc.x, nc.y );
    s->update();

} // for (size_t i = 0; i < WARRIOR_COUNT; ++i)



