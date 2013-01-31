namespace battleground {


inline Graph::Graph(
    const std::string& file
) :
    mFile( file )
{
    assert( !mFile.empty()
        && "Файл не указан." );

    if ( !boost::filesystem::exists( mFile ) ) {
        throw porte::Exception( "File '" + mFile + "' is not found." );
    }

    std::ifstream  in( mFile.c_str() );
    if ( !in.is_open() ) {
        throw porte::Exception( "File '" + mFile + "' is not open." );
    }
    
    boost::dynamic_properties dp;
    const bool statusRead =
        boost::read_graphviz( in, mGraph, dp, "node_id" );
    if ( !statusRead ) {
        throw porte::Exception( "Don't read graph '" + mFile + "'." );
    }

    in.close();
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
