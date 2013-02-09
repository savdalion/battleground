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

#include "image/ClanlibManagerSprite.h"
#include "../portulan/Portulan.h"


namespace battleground {


/**
* ������������ ���� (���������) ���������� Clanlib.
*
* @source http://clanlib.org
*/
class ClanlibVisual {
public:
    /**
    * ��� ��� ������� ����� �������������.
    */
    typedef typelib::json::Variant  option_t;




public:
    /**
    * ����� ��������� ���� ��� ������������.
    */
    explicit ClanlibVisual( const option_t& = option_t() );




    virtual ~ClanlibVisual();




    inline std::shared_ptr< const CL_DisplayWindow >  displayWindow() const {
        return mDisplayWindow;
    }


    inline std::shared_ptr< CL_DisplayWindow >  displayWindow() {
        return mDisplayWindow;
    }




    inline CL_GraphicContext const&  gc() const {
        return mDisplayWindow->get_gc();
    }


    inline CL_GraphicContext&  gc() {
        return mDisplayWindow->get_gc();
    }




    inline CL_InputContext const&  ic() const {
        return mDisplayWindow->get_ic();
    }


    inline CL_InputContext&  ic() {
        return mDisplayWindow->get_ic();
    }




    inline const ManagerSprite* managerSprite() const {
        return mManagerSprite.get();
    }


    inline ManagerSprite* managerSprite() {
        return mManagerSprite.get();
    }




    /**
    * ������������� ��������. ���� ���� ������������ ��� �� ���� �������,
    * ��� ��������. �����, �������� ���������� � ������� ����.
    */
    virtual ClanlibVisual& operator<<( const Portulan& );




    /**
    * ��������� ����� �������������.
    */
    virtual ClanlibVisual& operator<<( const option_t& );




    /**
    * ������� �������� ���� ������������.
    *
    * @template frequence ��� ����� ����� ���������� ����� ������, ��.
    *           ���� == 0, ��������� �� ���������� (������ 'engine' �� ���
    *           �� ��������� �������).
    * @template pulseN ���������� �������, ������� �������� *��* ������������.
    * @template needStep ������ ����� "����������".
    *           �� ���������� ��������� ���-�� ����� ���������� ������������
    *           ���������� ����� wait*().
    *           ���� (needStep <= 0), wait*() ����������� �� ������� ESC.
    * @template closeWindow ������� ���� ������������� ��� �������� ����������.
    * @template showPulse �������� � ������� ������� ����� ������ ���.
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
    * ������� ���� �������������.
    */
    virtual void clear();




    /**
    * @return ��������������� ��� ������������ � ClanLib ����������.
    *
    * @param x, y  ���������� ���������� �������� ������: (0, 0) = �����.
    *              ��������� � ������������ ���. ����.
    */
    template< typename T1, typename T2 >
    static typelib::coord2_t fromPhysics( T1 x, T2 y );




    /**
    * @return ����� � ������� (Frame Per Second).
    */
    static size_t calcFPS( size_t frameTime );




protected:
    /**
    * ����� �������������.
    */
    option_t mOption;

    /**
    * ���� ������������.
    */
    std::shared_ptr< CL_DisplayWindow >  mDisplayWindow;

    std::unique_ptr< ManagerSprite >  mManagerSprite;

    /**
    * ������� �����, ��.
    * #i ����� �������������� ��� ����������� ��������.
    */
    int mCurrentTime;
};


} // battleground








#include "ClanlibVisual.inl"
