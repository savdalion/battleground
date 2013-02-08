#pragma once

// @see ClanlibVisual

namespace battleground {


/**
* Управляет фреймами спрайтов.
*/
class ManagerFrame {
public:
    /**
    * Известные менеджеру фреймы (для спрайтов).
    */
    typedef std::map<
        std::string,
        std::unique_ptr< CL_PixelBuffer >
    >  knownFrame_t;




    ManagerFrame();




public:
    virtual ~ManagerFrame();




    /**
    * @return Указатель на загруженный по указанному пути фрейм
    *         в формате ClanLib.
    *         nullptr, если фрейм загрузить на удалось.
    */
    CL_PixelBuffer* frame( const std::string& path );




    /**
    * Объединяет фреймы.
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
