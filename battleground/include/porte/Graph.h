#pragma once

#include <boost/graph/graphviz.hpp>


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

    typedef boost::property<
        boost::vertex_name_t,
        std::string,
        boost::property< boost::vertex_color_t, float >
    > vertex_pt;
    typedef boost::property< boost::edge_weight_t, double >  edge_pt;
    typedef boost::property< boost::graph_name_t, std::string >  graph_pt;
    typedef boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::directedS,
        vertex_pt,
        edge_pt,
        graph_pt
    > graph_t;

    graph_t mGraph;
};


} // battleground






#include "Graph.inl"
