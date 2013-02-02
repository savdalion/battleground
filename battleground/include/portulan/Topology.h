#pragma once

#include "../../configure.h"
#include "../world/@/portulan/struct.hcl"


namespace battleground {

/**
* Обёртка для работы с топологией мира на C++.
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
    * Резервирует место для элементов в куче.
    * Инициализирует структуру T нулями.
    */
    template< class T, size_t N >
    static inline std::unique_ptr< T >  createContent() {
        std::unique_ptr< T >  content( new T[ N ] );
        std::memset( content.get(),  0,  sizeof( T ) * N );
        return std::move( content );
    }




    // # Общедоступны, чтобы сейчас? не заморачиваться с методами. @todo?
public:
    // подключаем переменные для обмена с OpenCL
    #include "../world/@/portulan/enum-topology.inl"

};


} // battleground






#include "Topology.inl"
