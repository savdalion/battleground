#pragma once

// @see ClanlibVisual

namespace battleground {


/**
* ��������� ��������� ����.
*/
class ManagerFrame {
public:
    /**
    * ��������� ��������� ������ (��� ��������).
    */
    typedef boost::unordered_map<
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




private:
    knownFrame_t  mKnownFrame;
};


} // battleground








#include "ManagerFrame.inl"
