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
    const keySprite_t& ks,
    const std::string& path
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
    CL_PixelBuffer ir;

    for (auto itr = l.cbegin(); itr != l.cend(); ++itr) {
        auto str = mKnownSprite.find( *itr );
        if (str == mKnownSprite.end()) {
            throw porte::Exception( "Sprite '" + *itr + "' is not found in known sprite." );
        }
        const CL_Sprite* sprite = str->second.get();
        ASSERT( (sprite->get_frame_count() == 1)
            && "Умеем объединять только однофреймовые спрайты. @todo" );

        // получаем фрейм спрайта
        // # Фреймы спрайта предусмотрительно запомнили в insert() / mKnownFrame.
#ifdef _DEBUG
        std::cout << "  Фрейм '" << *itr << "'" << std::endl;
#endif
        auto ktr = mKnownFrame.find( *itr );
        ASSERT( (ktr != mKnownFrame.end())
            && "Не найдены фреймы для спрайта. Целостность нарушена." );
        ASSERT( !ktr->second->is_null()
            && "Фрейм пуст. Целостность нарушена." );
        CL_PixelBuffer& image = *ktr->second;
        ir = mManagerFrame->merge( ir, image );
    }

    CL_SpriteDescription sd;
    sd.add_frame( ir );
    std::unique_ptr< CL_Sprite >
        sprite( new CL_Sprite( mDisplayWindow->get_gc(),  sd ) );
    // устанавливаем центр спрайта
    sprite->set_alignment(
        CL_Origin(),
        -sprite->get_width() / 2,
        -sprite->get_height() / 2
    );
    mKnownSprite.insert( std::make_pair( ks, std::move( sprite ) ) );

    // запоминаем фрейм (понадобится для составных спрайтов)
    std::unique_ptr< CL_PixelBuffer >  irPtr(
        new CL_PixelBuffer( ir.copy() )
    );
    mKnownFrame.insert( std::make_pair( ks, std::move( irPtr ) ) );
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


} // battleground
