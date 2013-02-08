namespace battleground {


inline ClanlibVisual::ClanlibVisual(
    const option_t& o
) :
    mOption( o ),
    mDisplayWindow(),
    mManagerSprite(),
    mCurrentTime( 0 )
{
    // @source Example "SpritesRTS" from http://clanlib.org
    // @source Example "TileMap" from http://clanlib.org
	CL_SetupCore setup�ore;
	CL_SetupDisplay setupDisplay;
	#ifdef USE_SOFTWARE_RENDERER
		CL_SetupSWRender setupSWRender;
	#endif
	#ifdef USE_OPENGL_1
		CL_SetupGL1 setupGL1;
	#endif
	#ifdef USE_OPENGL_2
		CL_SetupGL setupGL;
	#endif

    CL_DisplayWindowDescription desc( "Battleground" );
    const auto width  = o.at( "width-window",  WIDTH_WINDOW );
    const auto height = o.at( "height-window", HEIGHT_WINDOW );
	desc.set_size( CL_Size( width, height ),  false );
	desc.set_allow_resize( false );
	mDisplayWindow = std::shared_ptr< CL_DisplayWindow >(
        new CL_DisplayWindow( desc )
    );

    std::unique_ptr< ManagerSprite >  ms(
        new ManagerSprite( mDisplayWindow )
    );
    mManagerSprite = std::move( ms );

    // # ����� �� ��������� "�������������� ������", ������ ����
    //   ������������ � ���������� - ClanlibManagerSprite.
}




inline ClanlibVisual::~ClanlibVisual() {
}




inline ClanlibVisual& ClanlibVisual::operator<<(
    const Portulan&  portulan
) {
    const auto& topology = portulan.topology();

    // ��������� �� ������ �������� ���������
    #include "../world/@/io/ClanlibVisual/draw.inl"

    mDisplayWindow->flip( 1 );
    CL_KeepAlive::process();

    return *this;
}






inline ClanlibVisual& ClanlibVisual::operator<<( const option_t& json ) {

    mOption = json;

    assert( false && "�� �����������" );

    return *this;
}





template<
    size_t frequence,
    int pulseN,
    int needStep,
    bool closeWindow,
    bool showPulse
>
inline void ClanlibVisual::wait( std::shared_ptr< Engine >  engine ) {

    auto gc = mDisplayWindow->get_gc();
    auto ic = mDisplayWindow->get_ic();
    CL_Font font( gc, "Tahoma", 16 );
    CL_BlendMode blendTransparent;
    int lastTime = CL_System::get_time();
    int countStep = 0;
    for ( ; ; ) {

        // ������� �� ESC
        if ( ic.get_keyboard().get_keycode( CL_KEY_ESCAPE ) ) {
            break;
        }

        // �������, ����� ���������� 'needStep' �������
        if (countStep >= needStep) {
            break;
        }

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
        const size_t fps = calcFPS( deltaTime );
#endif


        clear();


        // ������������� ��������
        *this << *engine->portulan();

#ifdef _DEBUG
        {
            std::ostringstream ss;
            ss << fps;
            //const auto s = CL_StringHelp::int_to_text( fps );
            font.draw_text( gc, 10, 20, ss.str(), CL_Colorf::lemonchiffon );
        }
#endif


        mDisplayWindow->flip( 1 );
        CL_KeepAlive::process();


        // ��������� ��� �� �������� ���-�� ������� �����
        engine->pulse( pulseN );


		mCurrentTime = CL_System::get_time();
        // 10 ms (100 hz)
		static const int mainLoopRate = 10;
		const int timeToSleep = mainLoopRate - (mCurrentTime - lastTime);
		if (timeToSleep > 0) {
            CL_System::sleep( timeToSleep );
        }

        ++countStep;

    } // for ( ; ; )
}






inline void ClanlibVisual::clear() {
    mDisplayWindow->get_gc().clear( CL_Colorf::darkgreen );
}




inline size_t ClanlibVisual::calcFPS( size_t frameTime ) {
	static size_t fpsResult = 0;
	static size_t fpsCounter = 0;
	static size_t totalTime = 0;
	
	totalTime += frameTime;
	if (totalTime >= 1000) {
		fpsResult = fpsCounter + 1;
		fpsCounter = totalTime = 0;
	}
	++fpsCounter;

	return fpsResult;
}


} // battleground
