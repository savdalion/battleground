#include "../include/World.h"


namespace battleground {


inline World::World(
) :
    mPortulan( new Portulan() ),
    mEngine( new Engine( mPortulan ) ),
    mVisual( new ClanlibVisual() )
{
    // подключаем своих слушателей событий от игрока
    mVisual->displayWindow()->get_ic().get_mouse().sig_key_down()
        .connect( this, &World::onMouseDown );
    mVisual->displayWindow()->get_ic().get_mouse().sig_pointer_move()
        .connect( this, &World::onMouseMove );
    mVisual->displayWindow()->get_ic().get_keyboard().sig_key_down()
        .connect( this, &World::onKeyboardDown );
    mVisual->displayWindow()->sig_window_close()
        .connect( this, &World::onWindowClose );

    //mVisual->displayWindow()->hide_cursor();
}




inline std::shared_ptr< World >  World::valueOf() {
    return std::shared_ptr< World >( new World() );
}




inline World::~World() {
}




template<
    size_t frequence,
    int pulseN,
    int needStep,
    bool closeWindow,
    bool showPulse
>
inline void World::go() {
    visual()->wait< frequence, pulseN, needStep, closeWindow, showPulse >( mEngine );
}




inline void World::onMouseDown( const CL_InputEvent& ie, const CL_InputState& is ) {
    // @todo ...
}




inline void World::onMouseMove( const CL_InputEvent& ie, const CL_InputState& is ) {
    // @todo ...
}




inline void World::onKeyboardDown( const CL_InputEvent& ie, const CL_InputState& is ) {
    // @todo ...
}




inline void World::onWindowClose() {
}


} // battleground
