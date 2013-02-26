// Визуализация элемента 'ПОЛЕ БИТВЫ' с помощью Clanlib.
// @see ClanlibVisual::operator<<()


for (base_t* bp = pt->baseBattlegroundContent.get(); bp->incarnate; ++bp) {
    const size_t i =
        std::distance( pt->baseBattlegroundContent.get(), bp );

    const characteristicBattleground_t& ch =
        pt->characteristicBattlegroundContent.get()[ i ];
    const strategyBattleground_t& st =
        pt->strategyBattlegroundContent.get()[ i ];

    CL_Sprite* s = managerSprite()->sprite( ch, st );
    const typelib::coord2_t nc = fromPhysics( 0, 0 );
    s->draw( gc(), nc.x, nc.y );
    s->update();

} // for (base_t* bp = ...



