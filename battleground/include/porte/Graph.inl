namespace battleground {


inline Graph::Graph(
    const std::string& file
) :
    //mFile( file )
    // @test
    mFile( INCARNATION_WORLD_PATH_BATTLEGROUND + "/test.gv" )
{
    assert( !mFile.empty()
        && "���� �� ������." );

    if ( !boost::filesystem::exists( mFile ) ) {
        throw porte::Exception( "File '" + mFile + "' is not found." );
    }

    // ������ ���� � ������� Graphviz
    FILE* fp = std::fopen( mFile.c_str(), "r" );
    if ( !fp ) {
        throw porte::Exception( "File '" + mFile + "' is not open." );
    }
    GVC_t* gvc = gvContext();
    gvc = gvContext();
    graph_t* g = agread( fp );

    gvLayout( gvc, g, "dot" );
    gvRender( gvc, g, "plain", stdout );
    gvFreeLayout( gvc, g );
    agclose( g );

    // @todo ����������� ������ ������ � Graphviz, ��� GTest.

}




inline Graph::~Graph() {
}




template< typename T >
inline T Graph::labelEdge(
    const std::string& subgraph,
    const std::string& node,
    const T& def
) const {
    return T();
}


} // battleground
