namespace battleground {

    
inline ManagerSprite::ManagerSprite(
    std::shared_ptr< CL_DisplayWindow >  displayWindow
) :
    mManagerFrame( new ManagerFrame() ),
    mDisplayWindow( displayWindow )
{
    ASSERT( mDisplayWindow
        && "CL_DisplayWindow необходимо указать для формирования спрайта." );

    // # Заполняем структуру здесь, чтобы не создавать "пробрасывающие методы"
    //   в ClanlibVisual.
    #include "../../world/@/io/ClanlibVisual/init-sprite.inl"
}




inline ManagerSprite::~ManagerSprite() {
}




void ManagerSprite::insert(
    const keySprite_t&  ks,
    const std::string&  path,
    const typelib::json::Variant&  o
) {
#ifdef _DEBUG
        std::cout << "Простой спрайт '" << ks << "'" << std::endl;
#endif

    CL_SpriteDescription sd;
    const std::string p =
        VISUAL_IMAGE_WORLD_PATH_BATTLEGROUND + "/" + path;
    const auto image = *mManagerFrame->frame( p );
    sd.add_frame( image );
    std::unique_ptr< CL_Sprite >
        sprite( new CL_Sprite( mDisplayWindow->get_gc(),  sd ) );
    // устанавливаем центр спрайта
    sprite->set_alignment(
        CL_Origin(),
        -sprite->get_width() / 2,
        -sprite->get_height() / 2
    );

    // опции спрайта
    const auto alpha = o.at( "alpha", 1.0f );
    sprite->set_alpha( alpha );

    mKnownSprite.insert( std::make_pair( ks, std::move( sprite ) ) );

    // запоминаем фрейм (понадобится для составных спрайтов)
    std::unique_ptr< CL_PixelBuffer >  imagePtr(
        new CL_PixelBuffer( image.copy() )
    );
    mKnownFrame.insert( std::make_pair( ks, std::move( imagePtr ) ) );
};




inline void ManagerSprite::insert(
    const keySprite_t& ks,
    const std::vector< keySprite_t >&  l
) {
#ifdef _DEBUG
        std::cout << "Составной спрайт '" << ks << "'" << std::endl;
#endif

    // объединяем спрайты из 'l' в один
    CL_Sprite ir;
    for (auto itr = l.cbegin(); itr != l.cend(); ++itr) {
        auto str = mKnownSprite.find( *itr );
        if (str == mKnownSprite.end()) {
            throw porte::Exception( "Sprite '" + *itr + "' is not found in known sprite." );
        }
        CL_Sprite* s = str->second.get();
        ASSERT( (s->get_frame_count() == 1)
            && "Умеем объединять только однофреймовые спрайты. @todo" );

        ir = merge( mDisplayWindow->get_gc(), ir, *s );
    }

    // устанавливаем центр спрайта
    ir.set_alignment(
        CL_Origin(),
        -ir.get_width() / 2,
        -ir.get_height() / 2
    );
    mKnownSprite.insert( std::make_pair( ks,  new CL_Sprite( ir ) ) );
}




inline CL_Sprite const* ManagerSprite::sprite(
    const keySprite_t& ks
) const {
    return sprite( ks );
}




inline CL_Sprite* ManagerSprite::sprite(
    const keySprite_t& ks
) {
    const auto ftr = mKnownSprite.find( ks );
    return (ftr == mKnownSprite.end()) ? nullptr : ftr->second.get();
}




inline CL_Sprite ManagerSprite::merge(
    CL_GraphicContext& gc,
    CL_Sprite& a,  CL_Sprite& b
) {
    if ( a.is_null() ) {
        return b;
    }

    return a;

    /* - @todo ...
    a.draw( gc, 0, 0 );
    a.update();
    b.draw( gc, 0, 0 );
    b.update();

    const CL_PixelBuffer p = gc.get_pixeldata(
        CL_Rect( 0, 0, a.get_width(), a.get_height() )
    );
    CL_SpriteDescription sd;
    sd.add_frame( p );
    CL_Sprite r( gc, sd );
    r.update();

    return r;
    */

    /*
    CL_PixelBuffer r = a;
    CL_Color cs[ 256 ];
    for (int y = 0; y < a.get_height(); ++y) {
        for (int x = 0; x < a.get_width(); ++x) {
            if ( (x >= b.get_width()) || (y >= b.get_height()) ) {
                continue;
            }
            const CL_Colorf colorA = a.get_pixel( x, y );
            const CL_Colorf colorB = b.get_pixel( x, y );
            // смешиваем
            // @source http://en.wikipedia.org/wiki/Alpha_compositing
            const float red =
                colorA.get_red() * (1 - colorB.get_alpha()) +
                    colorB.get_red() * colorB.get_alpha();
            const float green =
                colorA.get_green() * (1 - colorB.get_alpha()) +
                    colorB.get_green() * colorB.get_alpha();
            const float blue =
                colorA.get_blue() * (1 - colorB.get_alpha()) +
                    colorB.get_blue() * colorB.get_alpha();

            const CL_Colorf color( red, green, blue );
            r.set_colorkey(
        }
    }
    return r;
    */
}


} // battleground
