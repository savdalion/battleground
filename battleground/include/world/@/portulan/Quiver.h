#pragma once

/**
* Вид: КОЛЧАН.
*
* @see Warrior
*/
struct Quiver {
    inline Quiver() {
        static const integer_t capacity   = 5;
        static const integer_t countArrow = 5;
        static const uid_t keeper = 0;

        static const characteristicQuiver_t DEFAULT = {
            capacity, countArrow, keeper
        };
        ch = DEFAULT;
    }

    inline Quiver( characteristicQuiver_t ch ) : ch( ch ) {
    }

    characteristicQuiver_t ch;
};
