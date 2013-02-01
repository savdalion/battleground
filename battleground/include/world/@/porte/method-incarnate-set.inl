// Метод для воплощения элементов заданного набора.
// # Метод декларирован полностью здесь для сохранения аналогии с
//   'method-incarnate-element.inl', где имена и тело методов - результат
//   генерации мира по графам.
// @see incarnate-element.inl
// # Обработка графов вынесена по максимуму в утилиту формирования кода мира.
//   Здесь - результат её работы.


inline void Engine::incarnateSet(
    const std::string& set
) {
    // набор 'a'
    if (set == "a") {
        #include "../incarnation/a/incarnate-element.inl"

    } else {
        throw porte::Exception( "Set for incarnate is undefined." );
    }

} // inline void Engine::incarnateSet




