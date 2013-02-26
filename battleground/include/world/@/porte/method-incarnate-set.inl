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
        //#include "../incarnation/a/arrow.inl"
        #include "../incarnation/a/battleground.inl"
        #include "../incarnation/a/quiver.inl"
        #include "../incarnation/a/warrior.inl"
        // связываем воплощённые элементы
        #include "../incarnation/a/chain-uid.inl"

    } else {
        throw porte::Exception( "Set for incarnate is undefined." );
    }


    // после подключения набора обновим буферы OpenCL
    #include "update-buffer-cl.inl"

} // inline void Engine::incarnateSet




