// Воплощение элемента заданного видом и именем.
// @see Engine::incarnate( kind, name )


const auto uid = nextUID();


// загружаем граф
const std::string file =
    INCARNATION_WORLD_PATH_BATTLEGROUND +
    "/" + kind + "/" + name + ".gv";
const Graph graph( file );


static const std::string CCH = "clusterCharacteristic";


// ВОИН
if (kind == "warrior") {
    // @todo fine Позволить обращаться без приставки 'cluster'.
    const auto coord = graph.labelEdge( CCH, "координата", DEFAULT_COORD );
    const auto _coord = DEFAULT_MODIFICATOR_COORD_2K;

    const auto direction = graph.labelEdge( CCH, "направление", DEFAULT_DIRECTION );
    const auto _direction = DEFAULT_MODIFICATOR_DIRECTION_2K;

    const auto sword = graph.labelEdge( CCH, "меч", DEFAULT_BOOL );
    const auto _sword = DEFAULT_MODIFICATOR_BOOL;

    const auto stability = graph.labelEdge( CCH, "устойчивость", DEFAULT_REAL );
    const auto _stability = DEFAULT_MODIFICATOR_REAL_2K;

    const characteristicWarrior_t chara = {
        uid,
        coord,      { _coord[ 0 ],      _coord[ 1 ] },
        direction,  { _direction[ 0 ],  _direction[ 1 ] },
        sword,      _sword,
        stability,  { _stability[ 0 ],  _stability[ 1 ] }
    };

    const auto fn = [ &chara, this ] () {
        // найдём первую свободную ячейку этого вида и поместим туда элемент
        // # Ячейка элемента портулана считается свободной, если её UID == 0.
        auto itr = characteristicWarriorContentPtr.get();
        const auto itrEnd = itr + WARRIOR_COUNT;
        for ( ; itr != itrEnd; ++itr) {
            if (itr->uid == 0) {
                *itr = chara;
                return;
            }
        }
        throw porte::Exception( "All cells of portulan are filled." );
    };
    fn();

} else if (kind == "battleground") {
    //characteristicBattleground_t 
    // @todo ...

} else {
    throw porte::Exception( "Kind of element is undefined." );
}
