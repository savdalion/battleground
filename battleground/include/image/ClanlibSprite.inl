namespace battleground {


const CL_Size ClanlibSprite::mPreparedWindowSize(
    WIDTH_WINDOW, HEIGHT_WINDOW
);

std::unique_ptr< ManagerFrame >  ClanlibSprite::mManagerFrame(
    new ManagerFrame()
);



ClanlibSprite::ClanlibSprite(
    std::shared_ptr< Topology >  topology
) :
    mTopology( topology ),
    mCoord( 0, 0 ),
    mRotation( 0, 0 ),
    mSprite( new sprite_t() ),
    // �������� ������ ���� - ��. mWindowSize; mPreparedWindowSize ����������
    // ��� ���������������� ���������
    // @todo ������ ������������ ������� (������� ��������? ���������������
    //       �������?) �����������, � ����������� �� ������� ����. ������
    //       ������ ���� �� ��������.
    mWindowSize( WIDTH_WINDOW, HEIGHT_WINDOW ),
    mWindowScale(
        static_cast< float >( mWindowSize.width  ) /
            static_cast< float >( mPreparedWindowSize.width ),
        static_cast< float >( mWindowSize.height ) /
            static_cast< float >( mPreparedWindowSize.height )
    )
{
    assert( !mTopology.expired()
        && "�������� ����������� ���������." );
    assert( mTopology.lock()->visual()
        && "��������� ��������� ������ ���� ����������������." );
}




ClanlibSprite::~ClanlibSprite() {
}




const CL_DisplayWindow* ClanlibSprite::topology() const {
    return mTopology.lock()->visual();
}


CL_DisplayWindow* ClanlibSprite::topology() {
    return mTopology.lock()->visual();
}




void ClanlibSprite::drawSprite( enum UIDEvent e ) {
    auto s = sprite( e );
    assert( s
        && "������ ��� ��������� ������� �� ������." );
    auto gc = world()->get_gc();
    const typelib::coord2_t nc = fromPhysics( mCoord.x, mCoord.y );
    s->draw( gc, nc.x, nc.y );
    s->update();
}




void ClanlibSprite::addSprite(
    const std::string&             path,
    const std::string&             extension,
    const typelib::json::Variant*  animation
) {
#ifdef _DEBUG
    std::cout << "\n��������� '" << path << "' �� '" << extension << "'\n";
#endif

    const typelib::json::Variant& anim =
        animation ? *animation : typelib::json::Variant();

    // �������������� ��������� �� ��������� ��� �������
    const auto def = anim[ "" ];
    const auto defPingpong = def.at( "pingpong", false );
    const auto defLoop     = def.at( "loop", true );
    const auto defDelay    = def.at( "delay", 1000u );

    // �������� ������ ��� �������
    // # ������ ������� ������������� �� ������ �������.
    std::set< std::string >  event;
    typelib::file::listFolder( &event, path );
    assert( !event.empty()
        && "��� ������� �� ������� �� ������ �������. ���������� ����� �� ����� ���� ������." );
    for (auto etr = event.cbegin(); etr != event.cend(); ++etr) {
        const std::string& e = *etr;
        if ( boost::starts_with( e, "-" ) ) {
            // �����, ������������ �� '-', ����������
            continue;
        }

#ifdef _DEBUG
    std::cout << "\n�������������� ������ ��� ������� '" << e << "'\n";
#endif

        // ������ ��� �������
        CL_SpriteDescription ds;
        std::set< std::string >  frame;
        const std::string pathEvent = path + "/" + e;
        typelib::file::listFile( &frame, pathEvent, extension );
        assert( !frame.empty()
            && "��� ������� �� ������� �� ������ �������. ���������� ����� �� ����� ���� ������." );
        for (auto ftr = frame.cbegin(); ftr != frame.cend(); ++ftr) {
            const std::string& f = *ftr;
            const std::string pathFrame = pathEvent + "/" + f;
            const auto image = mManagerFrame->frame( pathFrame );
            ds.add_frame( *image );
        }

        // ��� ������ ��� ������� 'e'
        std::unique_ptr< CL_Sprite >  sprite(
            new CL_Sprite( ClanlibSprite::world()->get_gc(),  ds )
        );

        // �������� �������
        {
            bool pingpong = defPingpong;
            bool loop     = defLoop;
            size_t delay  = defDelay;
            if ( anim.has( e ) ) {
                const auto itDef = anim[ e.c_str() ];
                pingpong = itDef.at( "pingpong", pingpong );
                loop     = itDef.at( "loop", loop );
                delay    = itDef.at( "delay", delay );
            }
            sprite->set_play_pingpong( pingpong );
            sprite->set_play_loop( loop );
            sprite->set_delay( delay );
        }

        sprite->update();

        // ���������� ��������� ������
        const enum UIDEvent euid = convertEvent( e );
        addSprite( euid,  std::move( sprite ) );

#ifdef _DEBUG
        std::cout << "������ ��� ������� '" << e << "' ������.\n";
#endif

    } // for (auto etr = event.cbegin(); etr != event.cend(); ++etr)
}

    
    
    
void ClanlibSprite::addSprite(
    enum UIDEvent  e,
    std::unique_ptr< CL_Sprite >  s
) {
    assert( (e != NONE_EVENT)
        && "������������� ������� �� ������ ��������� �����." );
    assert( (mSprite->find( e ) == mSprite->end())
        && "����� ������� ��� ����. ��������� ���������." );

    // ������ ��������� ��� ������� - �� ������
    const int cx = s->get_width()  / 2;
    const int cy = s->get_height() / 2;
    s->set_alignment( origin_center );

    // ����� �������
    const auto nvs = needVisualSize();
    const typelib::size2_t scale(
        nvs.x / static_cast< float >( s->get_width()  ),
        nvs.y / static_cast< float >( s->get_height() )
    );
    s->set_scale( scale.x, scale.y );
    auto test = s->get_size();

    mSprite->insert( std::make_pair( e,  std::move( s ) ) );
}




void ClanlibSprite::drawCircle(
    CL_GraphicContext gc,
    float x, float y,
    float r,
    const CL_Colorf& c
) {
    const typelib::coord2_t nc = fromPhysics( x, y );
    CL_Draw::circle( gc, nc.x, nc.y, r, c );
    /* - @todo �������� �������.
    const float step = 2.0f * static_cast< float >( M_PI ) / 360.0f;
    for (float t = 0;  t < 2.0f * static_cast< float >( M_PI );  t += step) {
        const auto tx = r * cos( t );
        const auto ty = r * sin( t );
        CL_Draw::point( gc, tx + nc.x, ty + nc.y, CL_Colorf::darkseagreen );
    }
    */
}




void ClanlibSprite::drawCircle(
    CL_GraphicContext gc,
    float x, float y,
    float rMin, float rMax,
    const CL_Colorf& c
) {
    drawCircle( gc, x, y, rMin, c );
    drawCircle( gc, x, y, rMax, c );
}



} // battleground
