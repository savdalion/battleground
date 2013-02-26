// Визуализация элемента 'ВОИН' с помощью Clanlib.
// @see ClanlibVisual::operator<<()


for (base_t* bp = pt->baseWarriorContent.get(); bp->incarnate; ++bp) {
    const size_t i =
        std::distance( pt->baseWarriorContent.get(), bp );

    const characteristicWarrior_t& ch =
        pt->characteristicWarriorContent.get()[ i ];
    const strategyWarrior_t& st =
        pt->strategyWarriorContent.get()[ i ];

    CL_Sprite* s = managerSprite()->sprite( ch, st );
    const typelib::coord2_t nc =
        fromPhysics( ch.coord.s[ 0 ],  -ch.coord.s[ 1 ] ) -
        GRID_NORMA_COORD;
    s->draw( gc(), nc.x, nc.y );
    s->update();

} // for (base_t* bp = ...



