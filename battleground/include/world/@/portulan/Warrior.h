#pragma once

/**
* Вид: ВОИН.
*
* # Объект инициируется значениями по умолчанию. Эти значения могут быть
*   изменены при воплощении элемента в мире.
*
* @require struct.hcl
*/
struct Warrior {
    inline Warrior() {
        static const coord_t coord = { 0, 0, 0 };
        static const auto _coord = DEFAULT_MODIFICATOR_COORD_2K;

        static const direction_t direction = { 0, 0, 0 };
        static const auto _direction = DEFAULT_MODIFICATOR_DIRECTION_2K;

        static const bool_t sword = true;
        static const auto _sword = DEFAULT_MODIFICATOR_BOOL;

        static const number_t stability = 0.5f;
        static const auto _stability = DEFAULT_MODIFICATOR_REAL_2K;

        static const characteristicWarrior_t DEFAULT = {
            coord,      { _coord[ 0 ],      _coord[ 1 ] },
            direction,  { _direction[ 0 ],  _direction[ 1 ] },
            sword,      _sword,
            stability,  { _stability[ 0 ],  _stability[ 1 ] }
        };
        ch = DEFAULT;
    }

    inline Warrior( characteristicWarrior_t ch ) : ch( ch ) {
    }

    characteristicWarrior_t ch;
};
