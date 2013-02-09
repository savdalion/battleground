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
    typedef std::map<
        keySprite_t,
        std::unique_ptr< CL_PixelBuffer >
    >  knownFrame_t;

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
    void insert(
        const keySprite_t&,
        const std::string&  path,
        const typelib::json::Variant&  options = typelib::json::Variant()
    );




    /**
    * �������� ������ �� ����. ��������. ��������� ��� � �������� ������.
    *
    * # ���������� � ������ ������� ��� ������ ���� ��������� � mKnownSprite.
    */
    void insert( const keySprite_t&,  const std::vector< keySprite_t >& );




    /**
    * @return ��������� �� ������ � ������� ClanLib.
    *         nullptr, ���� ������ �� ������.
    */
    CL_Sprite const* sprite( const keySprite_t& ) const;

    CL_Sprite* sprite( const keySprite_t& );




    /**
    * ������ ��� ������ �� ��������� ���������� ��������� ���������.
    */
    #include "../../world/@/io/ClanlibVisual/method-sprite-by-state.inl"




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




    /**
    * ���������� �������.
    */
    static CL_Sprite merge(
        CL_GraphicContext&,
        CL_Sprite& a,  CL_Sprite& b
    );




private:
    knownSprite_t  mKnownSprite;
    knownFrame_t   mKnownFrame;

    std::unique_ptr< ManagerFrame >  mManagerFrame;

    std::shared_ptr< CL_DisplayWindow >  mDisplayWindow;
};


} // battleground








#include "ClanlibManagerSprite.inl"
