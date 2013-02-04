#pragma once

// @see ClanlibVisual

namespace battleground {


/**
* ”правл€ет спрайтами игры.
*/
class ManagerFrame {
public:
    /**
    * »звестные менеджеру фреймы (дл€ спрайтов).
    */
    typedef boost::unordered_map<
        std::string,
        std::unique_ptr< CL_PixelBuffer >
    >  knownFrame_t;




    ManagerFrame();




public:
    virtual ~ManagerFrame();




    /**
    * @return ”казатель на загруженный по указанному пути фрейм
    *         в формате ClanLib.
    *         nullptr, если фрейм загрузить на удалось.
    */
    CL_PixelBuffer* frame( const std::string& path );




private:
    knownFrame_t  mKnownFrame;
};


} // battleground








#include "ManagerFrame.inl"
