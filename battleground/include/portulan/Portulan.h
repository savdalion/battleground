#pragma once

#include "Topology.h"


namespace battleground {


/**
* Структура мира (статика).
*/
class Portulan :
    public std::enable_shared_from_this< Portulan >
{
public:

    inline Portulan(
    ) :
        mTopology( new Topology() )
    {
    }




    inline virtual ~Portulan() {
    }




    inline std::shared_ptr< const Topology > topology() const {
        return mTopology;
    }


    inline std::shared_ptr< Topology > topology() {
        return mTopology;
    }




    /**
    * Визуализирует портулан с помощью 'visualizer'.
    *
    * # 'visualizer' должен реализовывать метод operator<<().
    */
    template< class V >
    inline void draw( V* visualizer ) const {
        *visualizer << *this;
    }




private:
    /**
    * Топология портулана.
    */
    std::shared_ptr< Topology >  mTopology;
};


} // battleground
