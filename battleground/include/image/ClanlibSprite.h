#pragma once

#include "ClanlibManagerFrame.h"


namespace battleground {


/**
* Визуальный образ в формате Clanlib, зарегистрированный для портулана.
*
* @see http://clanlib.org
*/
class ClanlibSprite {
public:
    /**
    * Спрайты сгруппированы по именам.
    * Каждое имя может иметь один спрайт (образ для визуализации).
    */
    typedef std::map<
        std::string,
        std::unique_ptr< CL_Sprite >
    > sprite_t;




protected:
    ClanlibSprite( std::shared_ptr< Topology > );



    virtual ~ClanlibSprite();




public:
    const CL_DisplayWindow* world() const;


    CL_DisplayWindow* world();




    inline const ManagerFrame* managerFrame() const {
        return mManagerFrame.get();
    }


    inline ManagerFrame* managerFrame() {
        return mManagerFrame.get();
    }




    inline sprite_t const* sprite() const {
        return mSprite.get();
    }




    /**
    * @return Спрайт для заданного действия.
    *         nullptr, если спрайт для действия не найден.
    */
    inline CL_Sprite* sprite( const std::string&  action ) {
        auto ftr = mSprite->find( action );
        return (ftr == mSprite->end()) ? nullptr : ftr->second.get();
    }



    /**
    * Отображает спрайт для заданного действия.
    */
    void drawSprite( const std::string&  action );




    /**
    * Добавляет спрайты, собирая их по фреймам типа 'extension' из 'path',
    * учитывая настройки 'animation'.
    *
    * # Фреймы спрайтов сгруппированы по папкам событий - см. допустимые
    *   названия в Event.
    * # Фреймы и спрайты должны быть одного размера.
    */
    void addSprite(
        const std::string&             path,
        const std::string&             extension,
        const typelib::json::Variant*  animation = nullptr
    );




    /**
    * Добавляет конкретный спрайт.
    */
    void addSprite(
       const std::string&  action,
        std::unique_ptr< CL_Sprite >
    );





    /**
    * @return Координаты образа.
    */
    template< typename T >
    inline void coord( T x, T y ) {
        coord( coord_t( x, y ) );
    };


    inline const typelib::coord2_t& coord() const {
        return mCoord;
    };


    inline void coord( const typelib::coord2_t& c ) {
        mCoord = c;
    };




    /**
    * @return Углы поворота элемента по XY в радианах.
    */
    template< typename T >
    inline void rotation( T x, T y ) {
        rotation( rotation_t( x, y ) );
    };


    inline const typelib::coord2_t& rotation( const typelib::coord2_t& c ) const {
        return mRotation;
    };


    inline void rotation( const typelib::coord2_t& r ) {
        mRotation = r;
    };



    inline bool operator==( const ClanlibSprite& b ) const {
        // достаточно сравнить спрайты
        return (*mSprite == *b.sprite());
    }




    /**
    * @return Преобразованные для визуализации в Clanlib координаты.
    *
    * @param x, y  Абсолютные координаты игрового движка: (0, 0) = центр.
    *              Совпадают с координатами физ. мира.
    */
    template< typename T1, typename T2 >
    static inline typelib::coord2_t fromPhysics( T1 x, T2 y ) {
        static const typelib::coord2_t NORMA(
            static_cast< float >( CENTER_WINDOW_WIDTH  ),
            static_cast< float >( CENTER_WINDOW_HEIGHT )
        );
        return typelib::coord2_t(
            static_cast< float >( x ) + NORMA.x,
            NORMA.y + static_cast< float >( y )
        );
    }




private:
    std::weak_ptr< Topology >  mTopology;

    typelib::coord2_t  mCoord;
    typelib::coord2_t  mRotation;

    // @see addSprite(), drawSprite()
    std::unique_ptr< sprite_t >  mSprite;

    /**
    * Размер окна для которого вычислены координаты
    * областей (mPreparedWindowSize) и рабочий размер
    * окна (mWindowSize).
    */
    static const CL_Size  mPreparedWindowSize;
    const CL_Size  mWindowSize;
    const CL_Sizef mWindowScale;

    static std::unique_ptr< ManagerFrame >  mManagerFrame;
};



} // battleground








#include "ClanlibSprite.inl"
