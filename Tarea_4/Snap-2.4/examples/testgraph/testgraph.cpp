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
#include <fstream>
#include "stdafx.h"

/*LLORANDO SANGRE!!!*/

std::ofstream dormir;

void kuz(PNGraph g)//GraphML
{
    dormir.open("archivo.graphml");
    /*Aquí usamos el formato que pide GraphML*/
    dormir << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\"\n\t xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\t xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns\n\thttp://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
    dormir << "\n <graph id=\"G\" edgedefault=\"directed\">\n";

    for(PNGraph::TObj::TNodeI nodo = g->BegNI(); nodo < g->EndNI(); nodo++)
        dormir << "<node id=\"" << nodo.GetId() << "\"/>\n";

    for(PNGraph::TObj::TEdgeI vertice = g->BegEI(); vertice < g->EndEI(); vertice++)
        dormir << "<edge source=\"" << vertice.GetSrcNId() << "\" target=\"" << vertice.GetDstNId() << "\"/>\n";

    dormir << "</graph>" << "\n</graphml>";
    dormir.close();
}

void sharmutta(PNGraph g)//GraphGEXF
{
    dormir.open("archivo.gexf");
    dormir << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<gexf xmlns=\"http://www.gexf.net/1.2draft\"\n xmlns:xsi=\"http://www.w3.org/2001/XMLSchema−instance\"\n xsi:schemaLocation=\"http://www.gexf.net/1.2draft\n\t\thttp://www.gexf.net/1.2draft/gexf.xsd\"\nversion=\"1.2\">";
    dormir << "\n<graph defaultedgetype=\"directed\">";
    dormir << "<nodes>";
    for (PNGraph::TObj::TNodeI nodo = g->BegNI(); nodo < g->EndNI(); nodo++)
          dormir << "<node id=\"" << nodo.GetId() <<"\"/>\n";
      dormir << "</nodes>";
      dormir << "<edges>";
      int id = 1;
      for (PNGraph::TObj::TEdgeI vertice = g->BegEI(); vertice < g->EndEI(); vertice++)
      {
          dormir << "<edge id=\"" << id << "\" source=\"" << vertice.GetSrcNId() << "\" target=\"" << vertice.GetDstNId() << "\"/>\n";
          id++;
      }
      dormir << "</edges>";
      dormir << "</graph>";
      dormir << "</gexf>";
      dormir.close();
}

void kuzemac(PNGraph g) //JSON
{
    dormir.open("archivo.json");
    dormir << "{ \"graph\": {\n\"nodes\": [\n" ;

    for (PNGraph::TObj::TNodeI nodo = g->BegNI(); nodo < g->EndNI(); nodo++)
    {
        dormir << "{ \"id\": \"" << nodo.GetId() << "\" }";
        if (nodo++ != g->EndNI())
          dormir << " ,\n";
        else
          dormir << " ]\n";
    }

    dormir << "\"edges\": [\n";

    for (PNGraph::TObj::TEdgeI vertice = g->BegEI(); vertice < g->EndEI(); vertice++)
    {
          dormir << "{ \"source\": \"" << vertice.GetSrcNId() << "\", \"target\": \"" << vertice.GetDstNId() << "\" }";
          if (vertice++ != g->EndEI())
            dormir << " ,\n";
          else
            dormir << " ]\n";
      }
      dormir << "} }";
      dormir.close();
}

void modishness(PNGraph g)//GDF
{
    dormir.open("archivo.gdf");
    dormir << "nodedef>id VARCHAR\n";

    for (PNGraph::TObj::TNodeI nodo = g->BegNI(); nodo < g->EndNI(); nodo++)
          dormir << nodo.GetId() <<"\n";

    dormir << "edgedef>source VARCHAR, destination VARCHAR\n";

    for (PNGraph::TObj::TEdgeI vertice = g->BegEI(); vertice < g->EndEI(); vertice++)
          dormir << vertice.GetSrcNId() << "," << vertice.GetDstNId() << "\n";

    dormir.close();
}

int main()
{
    /*gracias a Snap se importa con una sola línea*/
    PNGraph g = TSnap::LoadEdgeList<PNGraph>("soc-Slashdot0811.txt",0,1); //creamos el grafo
    kuz(g);
    kuzemac(g);
    modishness(g);
    sharmutta(g);

    return 0;
}
