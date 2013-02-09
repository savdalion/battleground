namespace battleground {

    
inline ManagerFrame::ManagerFrame() {
}




inline ManagerFrame::~ManagerFrame() {
}




inline CL_PixelBuffer* ManagerFrame::frame(
    const std::string& path
) {
    ASSERT( !path.empty()
        && "���� � ������ �� ������." );

    // ��������� ���
    auto ftr = mKnownFrame.find( path );
    if (ftr != mKnownFrame.end()) {
        return ftr->second.get();
    }

    // � ���� ����� ����������� ���, ���������
#ifdef _DEBUG
        std::cout << "  ����� '" << path << "' .. ";
#endif
        const int posExtension = path.find( '.' );
        const std::string extension =
            (posExtension == std::string::npos)
                ? "" : path.substr( posExtension );
        const bool support =
            (extension == ".png")
         || (extension == ".jpg")
        ;
        if ( !support ) {
            ASSERT( false
                && "���� ��� ����������� �� ��������������." );
            return nullptr;
        }

        const auto image =
            (extension == ".png") ? CL_PNGProvider::load( path ) :
            (extension == ".jpg") ? CL_JPEGProvider::load( path ) :
            // #! �������� ���� �� �������� ��� ClanLib-2.3.6 / Windows 7.
            CL_ImageProviderFactory::load( path );
#ifdef _DEBUG
        std::cout << " OK" << std::endl;
#endif

        // ��������
        std::unique_ptr< CL_PixelBuffer >  imagePtr(
            new CL_PixelBuffer( image.copy() )
        );
        ftr = mKnownFrame.insert(
            std::make_pair( path,  std::move( imagePtr ) )
        ).first;

        return ftr->second.get();
}




inline CL_PixelBuffer ManagerFrame::merge(
    CL_PixelBuffer& a,
    CL_PixelBuffer& b
) const {
    //const CL_Size sizeA = a.get_size();
    if ( a.is_null() ) {
        return b;
    }

    return a;

    /* - @todo
    CL_PixelBuffer r = a;
    CL_Color cs[ 256 ];
    for (int y = 0; y < a.get_height(); ++y) {
        for (int x = 0; x < a.get_width(); ++x) {
            if ( (x >= b.get_width()) || (y >= b.get_height()) ) {
                continue;
            }
            const CL_Colorf colorA = a.get_pixel( x, y );
            const CL_Colorf colorB = b.get_pixel( x, y );
            // ���������
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
