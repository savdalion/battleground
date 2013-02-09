// Воплощение элементов набора 'a'.
// @see incarnation/a/warrior.inl


// ПОЛЕ БИТВЫ Revival
{
    const extent_t extent = { 0, 0, 0 };
    const auto _extent = DEFAULT_MODIFICATOR_EXTENT_2K;

    const characteristicBattleground_t ch = {
        0,  true,
        extent,  { _extent[ 0 ], _extent[ 1 ] }
    };
    incarnateBattleground( ch );
}
