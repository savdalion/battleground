#pragma once

#include "../../configure.h"
#include "../image/ClanlibVisualImage.h"
#include "../world/@/portulan/struct.hcl"


namespace battleground {

/**
* ������ ��� ������ � ���������� ���� �� C++.
* 
* @see structure::topology_t
*/
class Topology :
    public std::enable_shared_from_this< Topology >
{
public:
    Topology();




    virtual ~Topology();




private:
    /**
    * ����������� ����� ��� ��������� � ����.
    * �������������� ��������� T ������.
    */
    template< class T, size_t N >
    static inline std::unique_ptr< T >  createContent() {
        std::unique_ptr< T >  content( new T[ N ] );
        std::memset( content.get(),  0,  sizeof( T ) * N );
        return std::move( content );
    }




    // # ������������, ����� ������? �� �������������� � ��������. @todo?
public:
    // ���������� ���������� ��� ������ � OpenCL �
    // ��� �������� ������� ���������
    #include "../world/@/portulan/enum-topology.inl"
};


} // battleground






#include "Topology.inl"
