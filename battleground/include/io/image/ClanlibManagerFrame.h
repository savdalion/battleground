#pragma once

// @see ClanlibVisual

namespace battleground {


/**
* ��������� �������� ��������.
*/
class ManagerFrame {
public:
    /**
    * ��������� ��������� ������ (��� ��������).
    */
    typedef std::map<
        std::string,
        std::unique_ptr< CL_PixelBuffer >
    >  knownFrame_t;




    ManagerFrame();




public:
    virtual ~ManagerFrame();




    /**
    * @return ��������� �� ����������� �� ���������� ���� �����
    *         � ������� ClanLib.
    *         nullptr, ���� ����� ��������� �� �������.
    */
    CL_PixelBuffer* frame( const std::string& path );




    /**
    * ���������� ������.
    */
    CL_PixelBuffer ManagerFrame::merge(
        CL_PixelBuffer& a,
        CL_PixelBuffer& b
    ) const;




private:
    knownFrame_t  mKnownFrame;
};


} // battleground







#include "ClanlibManagerFrame.inl"
