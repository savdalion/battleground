#pragma once

#include <gvc.h>


namespace battleground {


/**
* Класс для работы с графом в формате Graphviz.
*
* @use Boost Graph Library > http://boost.org/doc/libs/1_52_0/libs/graph/doc/table_of_contents.html
*
* @todo optimize? Использовать Parallel Boost Graph Library для анализа графов.
*/
class Graph {
public:
    /**
    * @param file Путь к файлу с графом.
    */
    Graph( const std::string& file );


    virtual ~Graph();




    /**
    * @return Значение метки 'label' ребра 'edge' из кластера 'subgraph'.
    *
    * @param def Значение по умолчанию, если кластера | ребра | метки
    *        не найдено.
    */
    template< typename T >
    T labelEdge(
        const std::string& subgraph,
        const std::string& edge,
        const T& def
    ) const;




private:
    const std::string  mFile;
};


} // battleground






#include "Graph.inl"
