/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : main.cpp
* Creation Date : 12-10-2015

* Created By :  Shiro
       _____
       .'/L|__`.
      / =[_]O|` \
      |"+_____":|
    __:='|____`-:__
   ||[] ||====| []||
   ||[] | |=| | []||
   |:||_|=|U| |_||:|
   |:|||]_=_ =[_||:| LS
   | |||] [_][]C|| |
   | ||-'"""""`-|| |
   /|\\_\_|_|_/_//|\
  |___|   /|\   |___|  
  `---'  |___|  `---'  
         `---'
          R2D2
_._._._._._._._._._._._._._._._._._._._._.*/

#include <iostream>
#include <cstdlib>
#include <boost/graph/graph_archetypes.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/directed_graph.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost\graph\dijkstra_shortest_paths.hpp>
#include <boost\graph\kruskal_min_spanning_tree.hpp>
#include <boost\graph\directed_graph.hpp>
#include <boost\graph\depth_first_search.hpp>
#include <boost\config.hpp>
#include <boost\graph\breadth_first_search.hpp>
#include <boost\graph\prim_minimum_spanning_tree.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>
#include <utility>
#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace boost;
using namespace std;

int main()
{
    typedef property<edge_weight_t, int> EdgeWeight; //definimos el peso de las aristas
    typedef adjacency_list<listS, vecS, directedS, no_property, EdgeWeight > grafo; //definimos que propiedades tiene el grafo
    typedef grafo::edge_descriptor Edge; //defines la descipcion de la arista
    grafo g;

//agregamos las aristas
    add_edge(1, 4, 8, g);
    add_edge(1,3,8,g);
    add_edge(3,2,7,g);
    add_edge(3,10,4,g);
    add_edge(3,5,8,g);
    add_edge(2,5,7,g);
    add_edge(5,6,9,g);
    add_edge(6,13,4,g);
    add_edge(13,14,6,g);
    add_edge(14,13,2,g);
    add_edge(11,12,6,g);
    add_edge(12,11,8,g);
    add_edge(12,9,2,g);
    add_edge(9,12,4,g);
    add_edge(9,10,2,g);
    add_edge(10,6,6,g);
    add_edge(10,3,10,g);
    add_edge(4,5,1,g);
    add_edge(4,7,3,g);
    add_edge(4,8,2,g);
    add_edge(7,4,6,g);
    add_edge(8,9,3,g);
    
    typedef property_map<grafo, vertex_index_t>::type indexMap; //definimos un mapa indexeado de los vertices
    IndexMap index = get(vertex_index, g);
    cout << "aristas = ";
    graph_traits<grafo>::edge_iterator ei, ei_end; //tener un iterador que pase por casa arista para que pueda imprimir

    for(tie(ei,ei_end)=edges(g)/*separa el numero de aristas en ei, ei_end*/; ei != ei_end /*mientras ei no alcance el final*/; ++ei)
    {
        cout << "(" << index[source(*ei,g)] << "," << index[target(*ei,g)] << ")" << endl; /*imprimimos...*/
    }
    
    cout << "Busqueda Cubells" << endl << endl;
    default_dfs_vistor v;//el tutorial dijo
    depth_first_search(g, visitor(v));/*busqueda profunda 1*/
    
    cout << "Busqueda de Amplitud" << endl << endl;
    grafo::vertex_descriptor a = vertex(1,g);//asignamos una variable con los datos del primer vertice del grafo
    default_bfs_visitor b; //Otra vez el tutorial :P
    breadth_first_search(g, a, visitor(b));/*hacemos otra busqueda pero ahora de amplitud*/

    cout << "Algoritmo de Prim!" << endl << endl;
    vector <graph_traits<grafo>::vertex_descriptor> p(num_vertices(g));/*guardas en un vector las descripciones de los vertices por cada parte del grafo*/
    prim_minimum_spanning_tree(g, &p[0]); /*ejecutamos facilito y rapido Prim*/

    property_map<grafo, edge_weight_t>::type weight = get(edge_weight, g);/*mapa de propiedades*/
    vector<Edge> spanning_tree;

    cout << "Algoritmo de Kruskal" << endl << endl;
    kruskal_minimum_spanning_tree(g, back_inserter(spanning_tree));/*Ahora asi de facil kruskal*/

    cout << "Imprimir las aristas en el MST: " << endl;
    for(vector<Edge>::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ei++)
        cout << source(*ei,g) << " <--> " << target(*ei,g) << "con peso: " << weight[*ei] << endl;

    cout << "Algoritmo de Dijkstra" << endl << endl;
    vector<graph_traits<grafo>::vertex_descriptor> pp(num_vertices(g));/*vector con descripcion de cada vertice*/
    vector<int> d(num_vertices(g); /*vector con el numero de vertices*/
    graph_traits<grafo>::vertex_descriptor s = vertex(a,g);/*descripcion del vertice en turno*/

    dijkstra_shortest_paths(g, s, predecessor_map(make_iterator_property_map(pp.begin(), get(vertex_index, g))).distance_map(make_iterator_property_map(d.begin(), get(vertex_index,g))));/*asi se llama dijkstra o.o*/

    char name[] = "ABCDEFGHIJKLMNO";
    cout << "las distancias y los padres son: " << endl;
    graph_traits<grafo>::vertex_iterator vi, vend;
    for(tie(vi,vend) = vertices(g); vi != vend; ++vi)
        cout << "Distancia(" << name[*vi] << ")= " << d[*vi] << ", parent(" << name[*vi] << ")= " << name[p[*vi]] << endl;


    cout << "Algoritmo de Floyd Warshall" << endl << endl;

    const int V = 14;
    vector<int>dd(V,(numeric_limits<int>::max)()); /*vector con los boundrie limits*/
    int D[V][V];/*para los pares*/
    johnson_all_pairs_shortest_paths(g, D, distance_map(&d[0]));/*Llamas Floyd Warshall con nombre alternativo porque... boost puede*/

    cout << "      ";
    for(int i = 0; i <V; ++i)
        cout << setw(5) << k;
    cout << endl;

    for(int j = 0; j < V; ++j)
    {
        cout << setw(3) << j << " -> ";
        for(int k = 0; k < V; ++k)
        {
            if(D[j][k] == (numeric_limits<int>::max)())
                cout << setw(5) << "info";
            else
                cout << setw(5) << D[j][k];
        }
        cout << endl;
    }

    /*Eliminamos aristas y vertices!!*/
    
    cout << "Borrando" << endl << endl;
    graph_traits<grafo>::vertex_iterator vii, vii_end, next;
    tie(vii,vii_end) = vertices(g);
    tie(ei, ei_end) = edges(g);
    for(next = vii; vii != vii_end; vii = next)
    {
        ++next;
        remove_edge(source(*ei,g), target(*ei,g),g);
        remove_vertex(*vii, g);
        break;
    }

    /*impresion despues de borrar*/
    cout << "Despues del borrado" << endl; << endl;
    for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        cout << "(" << index[spurce(*ei, g)] << "," << index[target(*ei,g)] << ")";
    cout << endl;

    cin.get();
    return 0;
}
