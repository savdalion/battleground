#pragma once

#include "ClanlibManagerFrame.h"


// @see ClanlibVisual

namespace battleground {


/**
* Управляет спрайтами.
*/
class ManagerSprite {
public:
    /**
    * Известные менеджеру спрайты.
    */
    typedef std::string  keySprite_t;
    typedef std::map<
        keySprite_t,
        std::unique_ptr< CL_Sprite >
    >  knownSprite_t;

    /**
    * Здесь запоминаем пути к пиксельным образам для каждого спрайта: после
    * создания спрайта нам эти образы уже не получить (преобразуются в
    * текстуру Clanlib).
    */
    typedef std::vector< std::string >  path_t;
    typedef std::map< keySprite_t, path_t >  knownFrame_t;

    /**
    * Спрайты по состояниям элементов.
    */
    #include "../../world/@/io/ClanlibVisual/enum-sprite-by-state.inl"



    ManagerSprite( std::shared_ptr< CL_DisplayWindow > );




public:
    virtual ~ManagerSprite();




    /**
    * Связывает спрайт с заданным ключом.
    */
    void insert( const keySprite_t&,  const std::string& path );




    /**
    * Собирает спрайт из неск. спрайтов. Связывает его с заданным ключом.
    *
    * # Задаваемые в списке спрайты уже должны быть добавлены в mKnownSprite.
    */
    void insert( const keySprite_t&,  const std::vector< keySprite_t >& );




    /**
    * Методы для работы со спрайтами конкретных элементов портулана.
    */
    #include "../../world/@/io/ClanlibVisual/method-sprite-by-state.inl"




    /**
    * @return Указатель на спрайт в формате ClanLib.
    *         nullptr, если спрайт не найден.
    */
    CL_Sprite const* sprite( const keySprite_t& ) const;

    CL_Sprite* sprite( const keySprite_t& );




    inline const ManagerFrame* managerFrame() const {
        return mManagerFrame.get();
    }


    inline ManagerFrame* managerFrame() {
        return mManagerFrame.get();
    }




    /**
    * @return Указатель на загруженный по указанному пути фрейм
    *         в формате ClanLib.
    *         nullptr, если фрейм загрузить на удалось.
    */
    CL_PixelBuffer* frame( const std::string& path );




private:
    knownSprite_t  mKnownSprite;
    knownFrame_t   mKnownFrame;

    std::unique_ptr< ManagerFrame >  mManagerFrame;

    std::shared_ptr< CL_DisplayWindow >  mDisplayWindow;
};


} // battleground








#include "ClanlibManagerSprite.inl"
