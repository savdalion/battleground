#pragma once

#include "../configure.h"
#include <memory>
#include "porte/Engine.h"
#include "io/ClanlibVisual.h"


namespace battleground {


/**
* Класс для работы с игровым миром.
* Создаёт и хранит все миры игры: физический, визуальный, аудио и пр..
*/
class World :
    public std::enable_shared_from_this< World >
{
protected:
    World();




public:
    // Для инициализации this->shared_from_this()
    static std::shared_ptr< World >  valueOf();


    virtual ~World();




    /**
    * @return Миры мира.
    */
    inline const std::shared_ptr< const Portulan >  portulan() const {
        return mPortulan;
    }


    inline std::shared_ptr< Portulan >  portulan() {
        return mPortulan;
    }


    inline const std::shared_ptr< const Engine >  engine() const {
        return mEngine;
    }


    inline std::shared_ptr< Engine >  engine() {
        return mEngine;
    }


    inline const std::shared_ptr< const ClanlibVisual >  visual() const {
        return mVisual;
    }


    inline std::shared_ptr< ClanlibVisual >  visual() {
        return mVisual;
    }




    /**
    * Запускает мир.
    *
    * @template frequence Как часто будет вызываться пульс движка, мс.
    *           Если == 0, пульсации не происходит (движок 'engine' на мир
    *           не оказывает влияния).
    * @template pulseN Количество пульсов, которые должен выполнить движок
    *           до визуализации результата.
    * @template needStep Скольк шагов "прокрутить".
    *           По прошествии заданного кол-ва шагов управление возвращается
    *           вызвавшему метод go().
    *           Если (needStep <= 0), go() выполняется до нажатия ESC.
    * @template closeWindow Закрыть окно визуализатора при возврате управления.
    * @template showPulse Печатать текущий пульс каждый шаг.
    */
    template<
        size_t frequence,
        int pulseN,
        int needStep,
        bool closeWindow,
        bool showPulse
    >
    void go();




private:
    /**
    * Слушатели событий визуального мира.
    */
	void onMouseDown( const CL_InputEvent&, const CL_InputState& );
	void onMouseMove( const CL_InputEvent&, const CL_InputState& );
	void onKeyboardDown( const CL_InputEvent&, const CL_InputState& );
	void onWindowClose();




private:
    /**
    * Портулан. Здесь мир начинается.
    */
    std::shared_ptr< Portulan >  mPortulan;

    /**
    * Двигатель для портулана.
    */
    std::shared_ptr< Engine >  mEngine;

    /**
    * Отображаемый мир.
    */
    std::shared_ptr< ClanlibVisual >  mVisual;
};



} // battleground








#include "World.inl"
