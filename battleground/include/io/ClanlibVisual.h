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




protected:
    //virtual void draw( const ... );




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


    /**
    * ������� �����, ��.
    * #i ����� �������������� ��� ����������� ��������.
    */
    int mCurrentTime;
};


} // battleground








#include "ClanlibVisual.inl"
