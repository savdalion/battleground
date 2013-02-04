#pragma once

#include "../../configure.h"
#include "../porte/Engine.h"
#include <typelib/typelib.h>
#include <boost/lexical_cast.hpp>

#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>

// Choose the target renderer
//#define USE_OPENGL_2
//#define USE_OPENGL_1
#define USE_SOFTWARE_RENDERER

#ifdef USE_SOFTWARE_RENDERER
#include <ClanLib/swrender.h>
#endif

#ifdef USE_OPENGL_1
#include <ClanLib/gl1.h>
#endif

#ifdef USE_OPENGL_2
#include <ClanLib/gl.h>
#endif

#include "ManagerSprite.h"
#include "../portulan/Portulan.h"


namespace battleground {


/**
* Визуализация мира (портулана) средствами Clanlib.
*
* @source http://clanlib.org
*/
class ClanlibVisual {
public:
    /**
    * Тип для задания опций визуализатору.
    */
    typedef typelib::json::Variant  option_t;




public:
    /**
    * Сразу открывает окно для визуализации.
    */
    explicit ClanlibVisual( const option_t& = option_t() );




    virtual ~ClanlibVisual();




    inline std::shared_ptr< const CL_DisplayWindow >  displayWindow() const {
        return mDisplayWindow;
    }


    inline std::shared_ptr< CL_DisplayWindow >  displayWindow() {
        return mDisplayWindow;
    }




    inline const ManagerSprite* managerSprite() const {
        return mManagerSprite.get();
    }


    inline ManagerSprite* managerSprite() {
        return mManagerSprite.get();
    }




    /**
    * Визуализирует портулан. Если окно визуализации ещё не было создано,
    * оно создаётся. Иначе, портулан рендерится в текущем окне.
    */
    virtual ClanlibVisual& operator<<( const Portulan& );




    /**
    * Обновляет опции визуализатора.
    */
    virtual ClanlibVisual& operator<<( const option_t& );




    /**
    * Ожидает закрытия окна визуализации.
    *
    * @template frequence Как часто будет вызываться пульс движка, мс.
    *           Если == 0, пульсации не происходит (движок 'engine' на мир
    *           не оказывает влияния).
    * @template pulseN Количество пульсов, которые выполним *до* визуализации.
    * @template needStep Скольк шагов "прокрутить".
    *           По прошествии заданного кол-ва шагов управление возвращается
    *           вызвавшему метод wait*().
    *           Если (needStep <= 0), wait*() выполняется до нажатия ESC.
    * @template closeWindow Закрыть окно визуализатора при возврате управления.
    * @template showPulse Печатать в консоль текущий пульс каждый шаг.
    */
    template<
        size_t frequence,
        int pulseN,
        int needStep,
        bool closeWindow,
        bool showPulse
    >
    void wait( std::shared_ptr< Engine > );




    /**
    * Очищает окно визуализатора.
    */
    virtual void clear();




protected:
    /**
    * @return Кадры в секунду (Frame Per Second).
    */
    static size_t calcFPS( size_t frameTime );




protected:
    /**
    * Опции визуализатора.
    */
    option_t mOption;

    /**
    * Окно визуализации.
    */
    std::shared_ptr< CL_DisplayWindow >  mDisplayWindow;

    static std::unique_ptr< ManagerSprite >  mManagerSprite;

    /**
    * Текущее время, мс.
    * #i Может использоваться для корректного тайминга.
    */
    int mCurrentTime;
};


} // battleground








#include "ClanlibVisual.inl"
