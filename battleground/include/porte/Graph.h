#pragma once

#include <gvc.h>


namespace battleground {


/**
* ����� ��� ������ � ������ � ������� Graphviz.
*
* @use Boost Graph Library > http://boost.org/doc/libs/1_52_0/libs/graph/doc/table_of_contents.html
*
* @todo optimize? ������������ Parallel Boost Graph Library ��� ������� ������.
*/
class Graph {
public:
    /**
    * @param file ���� � ����� � ������.
    */
    Graph( const std::string& file );


    virtual ~Graph();




    /**
    * @return �������� ����� 'label' ����� 'edge' �� �������� 'subgraph'.
    *
    * @param def �������� �� ���������, ���� �������� | ����� | �����
    *        �� �������.
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
