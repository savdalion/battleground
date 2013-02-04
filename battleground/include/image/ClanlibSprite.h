#pragma once

#include "ClanlibManagerFrame.h"


namespace battleground {


/**
* ���������� ����� � ������� Clanlib, ������������������ ��� ���������.
*
* @see http://clanlib.org
*/
class ClanlibSprite {
public:
    /**
    * ������� ������������� �� ������.
    * ������ ��� ����� ����� ���� ������ (����� ��� ������������).
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
    * @return ������ ��� ��������� ��������.
    *         nullptr, ���� ������ ��� �������� �� ������.
    */
    inline CL_Sprite* sprite( const std::string&  action ) {
        auto ftr = mSprite->find( action );
        return (ftr == mSprite->end()) ? nullptr : ftr->second.get();
    }



    /**
    * ���������� ������ ��� ��������� ��������.
    */
    void drawSprite( const std::string&  action );




    /**
    * ��������� �������, ������� �� �� ������� ���� 'extension' �� 'path',
    * �������� ��������� 'animation'.
    *
    * # ������ �������� ������������� �� ������ ������� - ��. ����������
    *   �������� � Event.
    * # ������ � ������� ������ ���� ������ �������.
    */
    void addSprite(
        const std::string&             path,
        const std::string&             extension,
        const typelib::json::Variant*  animation = nullptr
    );




    /**
    * ��������� ���������� ������.
    */
    void addSprite(
       const std::string&  action,
        std::unique_ptr< CL_Sprite >
    );





    /**
    * @return ���������� ������.
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
    * @return ���� �������� �������� �� XY � ��������.
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
        // ���������� �������� �������
        return (*mSprite == *b.sprite());
    }




    /**
    * @return ��������������� ��� ������������ � Clanlib ����������.
    *
    * @param x, y  ���������� ���������� �������� ������: (0, 0) = �����.
    *              ��������� � ������������ ���. ����.
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
    * ������ ���� ��� �������� ��������� ����������
    * �������� (mPreparedWindowSize) � ������� ������
    * ���� (mWindowSize).
    */
    static const CL_Size  mPreparedWindowSize;
    const CL_Size  mWindowSize;
    const CL_Sizef mWindowScale;

    static std::unique_ptr< ManagerFrame >  mManagerFrame;
};



} // battleground








#include "ClanlibSprite.inl"
