// Воплощение элементов набора 'a'.
// @see method-incarnate-set.inl
// @see method-incarnate-element.inl
// @see Папку world/@/incarnation.
// # Обработка графов вынесена по максимуму в утилиту формирования кода мира.
//   Здесь - результат её работы.


// ВОИН Armand
{
    const coord_t coord = { 0, 0, 0 };
    const auto _coord = DEFAULT_MODIFICATOR_COORD_2K;

    const direction_t direction = { 0, 0, 0 };
    const auto _direction = DEFAULT_MODIFICATOR_DIRECTION_2K;

    const bool_t sword = true;
    const auto _sword = DEFAULT_MODIFICATOR_BOOL;

    const real_t stability = 0.9f;
    const auto _stability = DEFAULT_MODIFICATOR_REAL_2K;

    const characteristicWarrior_t ch = {
        0,  true,
        coord,      { _coord[ 0 ],      _coord[ 1 ] },
        direction,  { _direction[ 0 ],  _direction[ 1 ] },
        sword,      _sword,
        stability,  { _stability[ 0 ],  _stability[ 1 ] }
    };
    incarnateWarrior( ch );
}
