#pragma once

/**
* Вид: СТРЕЛА.
*
* @see Warrior
*/
struct Arrow {
    inline Arrow() {
        static const coord_t coord = {};
        static const vector_t velocity = {};

        static const characteristicArrow_t DEFAULT = {
            coord, velocity
        };
        ch = DEFAULT;
    }

    inline Arrow( characteristicArrow_t ch ) : ch( ch ) {
    }

    characteristicArrow_t ch;
};
