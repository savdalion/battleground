namespace battleground {


World::World(
) :
    mPortulan( new Portulan() ),
    mEngine( new Engine( mPortulan ) ),
    // ���������� ���
    mVisual( new ClanlibVisual() ),
    // @todo ��� ������
    mCurrentTime( 0 )
{
    // ���������� ���������� ������� �� ������
    mVisual->ic().get_mouse().sig_key_down()
    .connect( this, &World::onMouseDown );

    mVisual->ic().get_mouse().sig_pointer_move()
    .connect( this, &World::onMouseMove );

    mVisual->ic().get_keyboard().sig_key_down()
    .connect( this, &World::onKeyboardDown );

    mVisual->displayWindow()->sig_window_close()
    .connect( this, &World::onWindowClose );

    //mVisual->displayWindow()->hide_cursor();
}




std::shared_ptr< World >  World::valueOf() {
    return std::shared_ptr< World >( new World() );
}




World::~World() {
}




template<
    size_t frequence,
    int pulseN,
    int needStep,
    bool closeWindow,
    bool showPulse
>
void World::go( real_t timestep ) {

    //auto it = this->shared_from_this();

    // ����������
    auto gc = mVisual->gc();
    auto ic = mVisual->ic();
    CL_Font font( gc, "Tahoma", 16 );
    CL_BlendMode blendTransparent;
    int lastTime = CL_System::get_time();
    while ( !ic.get_keyboard().get_keycode( CL_KEY_ESCAPE ) ) {

        // @source http://clanlib.org/wiki/MainDocs:Timing
		mCurrentTime = CL_System::get_time();
		int deltaTime = mCurrentTime - lastTime;
        // ���: ���� ���������� ����� �������������
		if (deltaTime > 1000) { deltaTime = 1000; }
        // 'deltaTimeMs' ����� ������������ ��� ����������� ��������
		//const float deltaTimeMs = static_cast< float >( deltaTime );
        lastTime = mCurrentTime;

#ifdef _DEBUG
        // ��� FPS
        // @source http://clanlib.org/docs/clanlib-0.8.0/Overview/tipsandtricks.html
        const size_t fps = ClanlibVisual::calcFPS( deltaTime );
#endif

        gc.clear( CL_Colorf::aquamarine );
        *mVisual << *mPortulan;
        mEngine->pulse( timestep );

#ifdef _DEBUG
        {
            std::ostringstream ss;
            ss << fps;
            font.draw_text( gc, 10, 20, ss.str(), CL_Colorf::lemonchiffon );
        }
#endif

		mCurrentTime = CL_System::get_time();
        // 10 ms (100 hz)
		static const int mainLoopRate = 10;
		const int timeToSleep = mainLoopRate - (mCurrentTime - lastTime);
		if (timeToSleep > 0) {
            CL_System::sleep( timeToSleep );
        }
    }

}




void World::onMouseDown( const CL_InputEvent& ie, const CL_InputState& is ) {
}




void World::onMouseMove( const CL_InputEvent& ie, const CL_InputState& is ) {
}




void World::onKeyboardDown( const CL_InputEvent& ie, const CL_InputState& is ) {
}




void World::onWindowClose() {
}


} // battleground
