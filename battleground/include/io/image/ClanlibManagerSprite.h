#pragma once

#include "ClanlibManagerFrame.h"


// @see ClanlibVisual

namespace battleground {


/**
* ��������� ���������.
*/
class ManagerSprite {
public:
    /**
    * ��������� ��������� �������.
    */
    typedef std::string  keySprite_t;
    typedef std::map<
        keySprite_t,
        std::unique_ptr< CL_Sprite >
    >  knownSprite_t;

    /**
    * ����� ���������� ���� � ���������� ������� ��� ������� �������: �����
    * �������� ������� ��� ��� ������ ��� �� �������� (������������� �
    * �������� Clanlib).
    */
    typedef std::vector< std::string >  path_t;
    typedef std::map< keySprite_t, path_t >  knownFrame_t;

    /**
    * ������� �� ���������� ���������.
    */
    #include "../../world/@/io/ClanlibVisual/enum-sprite-by-state.inl"



    ManagerSprite( std::shared_ptr< CL_DisplayWindow > );




public:
    virtual ~ManagerSprite();




    /**
    * ��������� ������ � �������� ������.
    */
    void insert( const keySprite_t&,  const std::string& path );




    /**
    * �������� ������ �� ����. ��������. ��������� ��� � �������� ������.
    *
    * # ���������� � ������ ������� ��� ������ ���� ��������� � mKnownSprite.
    */
    void insert( const keySprite_t&,  const std::vector< keySprite_t >& );




    /**
    * ������ ��� ������ �� ��������� ���������� ��������� ���������.
    */
    #include "../../world/@/io/ClanlibVisual/method-sprite-by-state.inl"




    /**
    * @return ��������� �� ������ � ������� ClanLib.
    *         nullptr, ���� ������ �� ������.
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
    * @return ��������� �� ����������� �� ���������� ���� �����
    *         � ������� ClanLib.
    *         nullptr, ���� ����� ��������� �� �������.
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
