namespace battleground {


inline Topology::Topology() {
    // инициируем топологию
    #include "../world/@/portulan/init-topology.inl"
}




inline Topology::~Topology() {
}


} // battleground
