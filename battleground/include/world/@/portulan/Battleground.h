#pragma once

/**
* Вид: ПОЛЕ БИТВЫ.
*
* @see Warrior
*/
struct Battleground {
    inline Battleground() {
        const extent_t extent = { 0, 0, 0 };
        const auto _extent = DEFAULT_MODIFICATOR_EXTENT_2K;

        const characteristicBattleground_t DEFAULT = {
            extent,  { _extent[ 0 ], _extent[ 1 ] }
        };
        ch = DEFAULT;
    }

    inline Battleground( characteristicBattleground_t ch ) : ch( ch ) {
    }

    characteristicBattleground_t ch;
};
