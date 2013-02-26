#pragma once

#include "../configure.h"
#include <memory>
#include "porte/Engine.h"
#include "io/ClanlibVisual.h"


namespace battleground {


/**
* ����� ��� ������ � ������� �����.
* ������ � ������ ��� ���� ����: ����������, ����������, ����� � ��..
*/
class World :
    public std::enable_shared_from_this< World >
{
protected:
    World();




public:
    // ��� ������������� this->shared_from_this()
    static std::shared_ptr< World >  valueOf();


    virtual ~World();




    /**
    * @return ���� ����.
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
    * ��������� ���.
    *
    * @template frequence ��� ����� ����� ���������� ����� ������, ��.
    *           ���� == 0, ��������� �� ���������� (������ 'engine' �� ���
    *           �� ��������� �������).
    * @template pulseN ���������� �������, ������� ������ ��������� ������
    *           �� ������������ ����������.
    * @template needStep ������ ����� "����������".
    *           �� ���������� ��������� ���-�� ����� ���������� ������������
    *           ���������� ����� go().
    *           ���� (needStep <= 0), go() ����������� �� ������� ESC.
    * @template closeWindow ������� ���� ������������� ��� �������� ����������.
    * @template showPulse �������� ������� ����� ������ ���.
    */
    template<
        size_t frequence,
        int pulseN,
        int needStep,
        bool closeWindow,
        bool showPulse
    >
    void go( real_t timestep );




private:
    /**
    * ��������� ������� ����������� ����.
    */
	void onMouseDown( const CL_InputEvent&, const CL_InputState& );
	void onMouseMove( const CL_InputEvent&, const CL_InputState& );
	void onKeyboardDown( const CL_InputEvent&, const CL_InputState& );
	void onWindowClose();




private:
    /**
    * ��������. ����� ��� ����������.
    */
    std::shared_ptr< Portulan >  mPortulan;

    /**
    * ��������� ��� ���������.
    */
    std::shared_ptr< Engine >  mEngine;

    /**
    * ������������ ���.
    */
    std::shared_ptr< ClanlibVisual >  mVisual;

    /**
    * ������� �� ������ �� ����������� ����.
    */
    CL_Slot mSlotMouseDown;
    CL_Slot mSlotMouseMove;
    CL_Slot mSlotKeyboardDown;
    CL_Slot mSlotWindowClose;

    size_t mCurrentTime;
};



} // battleground








#include "World.inl"
