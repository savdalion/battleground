namespace battleground {

    
inline ManagerSprite::ManagerSprite(
    std::shared_ptr< CL_DisplayWindow >  displayWindow
) :
    mManagerFrame( new ManagerFrame() ),
    mDisplayWindow( displayWindow )
{
    assert( mDisplayWindow
        && "CL_DisplayWindow необходимо указать для формирования спрайта." );

    // # Заполняем структуру здесь, чтобы не создавать "пробрасывающие методы"
    //   в ClanlibVisual.
    #include "../../world/@/io/ClanlibVisual/init-sprite.inl"
}




inline ManagerSprite::~ManagerSprite() {
    bool test = true;
}




void ManagerSprite::insert(
    const keySprite_t& ks,
    const std::string& path
) {
    CL_SpriteDescription sd;
    const std::string p =
        VISUAL_IMAGE_WORLD_PATH_BATTLEGROUND + "/" + path;
    const auto image = *mManagerFrame->frame( p );
    sd.add_frame( image );
    std::unique_ptr< CL_Sprite >
        sprite( new CL_Sprite( mDisplayWindow->get_gc(),  sd ) );
    mKnownSprite.insert( std::make_pair( ks, std::move( sprite ) ) );

    // запоминаем фреймы (понадобятся для составных спрайтов)
    auto ftr = mKnownFrame.insert( std::make_pair( ks, path_t() ) ).first;
    ftr->second.push_back( p );
};




inline void ManagerSprite::insert(
    const keySprite_t& ks,
    const std::vector< keySprite_t >&  l
) {
    // объединяем спрайты из 'l' в один
    CL_PixelBuffer ir;

    // фреймы спрайта предусмотрительно запомнили в insert() / mKnownFrame
    auto ktr = mKnownFrame.find( ks );
    assert( (ktr != mKnownFrame.end())
        && "Не найдены фреймы для спрайта. Целостность нарушена." );
    assert( !ktr->second.empty()
        && "Набор фреймов пуст. Целостность нарушена." );
    // см. assert-todo ниже
    const std::string path = ktr->second.front();

    for (auto itr = l.cbegin(); itr != l.cend(); ++itr) {
        auto str = mKnownSprite.find( *itr );
        if (str == mKnownSprite.end()) {
            throw porte::Exception( "Sprite '" + *itr + "' is not found in known sprite." );
        }
        const CL_Sprite* sprite = str->second.get();
        assert( (sprite->get_frame_count() == 1)
            && "Умеем работать только с однофреймовым спрайтом. @todo" );
        CL_PixelBuffer image = *mManagerFrame->frame( path );
        ir = mManagerFrame->merge( ir, image );
    }

    CL_SpriteDescription sd;
    sd.add_frame( ir );
    std::unique_ptr< CL_Sprite >
        sprite( new CL_Sprite( mDisplayWindow->get_gc(),  sd ) );
    mKnownSprite.insert( std::make_pair( ks, std::move( sprite ) ) );

    // запоминаем фреймы (понадобятся для "ещё более составных" спрайтов)
    auto ftr = mKnownFrame.insert( std::make_pair( ks, path_t() ) ).first;
    ftr->second.push_back( path );
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
