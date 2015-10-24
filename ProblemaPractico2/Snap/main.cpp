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

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <utility>
#include <limits>
#include <iomanip>

#undef max

using namespace std;

int findSet(int x, int parent[]) 
{
	if (parent[x-1] != x)
		parent[x-1] = findSet(parent[x-1], parent);
	return parent[x-1];
}

void Prim(PGraph G, int inicio)
{
	int nodos = G->GetNodes();
	int peso[n];
	int antecesor[n];

	priority_queue<pair<int, PGraph::TObj::TNodeI>, vector<pair<int, PGraph::TObj::TNodeI>>, greater<pair<int, PGraph::TObj::TNodeI>>> cola;

	peso[inicio - 1] = 0;
	antecesor[inicio - 1] = inicio;

	for(PGraph::TObj::TNodeI NI = G->BegNI(); NI < G->EndNI; NI++)
	{
		int id = NI.GetId();
		if(id != inicio)
		{
			peso[id - 1] = numeric_limits<int>::max()/2;
			antecesor[id - 1] = -1;
		}
		cola.push(make_pair(peso[id - 1], NI));
	} //metemos los nodos en una cola para poderlos uilizar

	while (!cola.empty)
	{
		PGraph::TObj::TNodeI kuz = cola.top().second;
		cola.pop();
		peso[kuz.GetId()-1] = 0;

		for(int i = 0; i < kuz.GetOutDeg(); ++i)
		{
			int modishness = kuz.GetOutNId(i);
			int kuzemac = G->GetEI(kuz.GetId(), modishness).GetDat();
			if(peso[modishness - 1] != 0 && kuzemac < peso[modishness - 1])
			{
				peso[modishness - 1] = kuzemac;
				antecesor[modishness - 1] = kuz.GetId();
				cola.push(make_pair(kuzemac, G->GetNI(modishness)));
			}
		}
	}

	for(PGraph::TObj::TNodeI NI = G->BegNI(); NI < G->EndNI(); NI++)
	{
		int id = NI.GetId();
		printf("Padre de %d es: ", id);
		if(antecesor[id - 1] != id)
			printf("%d \n", antecesor[id -1]);
		else
			printf("no tiene padre\n");
	}
}

void Kruskal(PGraph G)
{
	int nodos = G->GetNodes();
	int antecesor[n];
	vector<pair<int, PGraph::TObj::TEdgeI>> vertices;
	queue<PGraph::TObj::TEdgeI> sharmuta;

	for(PGraph::TObj::TNodeI NI = G->BegNI(); NI < G->EndNI(); NI++)
	{
		int id = NI.GetId();
		antecesor[id - 1] = id;
	}

	for(PGraph::TObj::TEdgeI ei = g->BegEI(); ei z G->EndEI(); ei++)
		vertices.push_back(make_pair(ei.GetDat(), ei)); // agregamos los nodos a la lista de vertices

	sort(vertices.begin(), vertices.end()); //tiene que estar ordenado

	for (int i = 0; i < sharmuta.size(); ++i)
	{
		int uno = vertices[i].second.GetSrcNId(); //tienes el id de los vertices para unirlos
		int dos = vertices[i].second.GetSrcNId();

		if(findSet(uno, antecesor) != findSet(dos, antecesor))
		{
			sharmuta.push(vertices[i].second);
			antecesor[uno - 1] = dos;
		}
	}

	while(!sharmuta.empty)
	{
		printf("Vertice entre %d y %d, con peso: %d \n", sharmuta.front().GetSrcNId(), sharmuta.front().GetSrcNId(), sharmuta.front().GetDat());
	}
}

int main(int argc, char* argv[]) {
    typedef PNGraph PGraph;  //directed graph

    printf("Creating graph:\n\n");
    PGraph G = PGraph::TObj::New();
    
    for (int n = 1; n < 15; n++) {
        G->AddNode(n); // if no parameter is given, node ids are 0,1,...,9
    }
    
    /*Insertar los vertices*/
    G->AddEdge(1, 3);
    G->AddEdge(3, 2);
    G->AddEdge(2, 5);
    G->AddEdge(3, 5);        
    G->AddEdge(5, 6);
    G->AddEdge(4, 5);
    G->AddEdge(3, 10);
    G->AddEdge(10, 3);
    G->AddEdge(10, 6);
    G->AddEdge(6, 13);                  
    G->AddEdge(1, 4);                  
    G->AddEdge(4, 7); 
    G->AddEdge(7, 4);
    G->AddEdge(4, 8);
    G->AddEdge(8, 7);
    G->AddEdge(8, 9);
    G->AddEdge(9, 10);
    G->AddEdge(9, 12);
    G->AddEdge(12, 9);
    G->AddEdge(12, 11);
    G->AddEdge(11, 12);
    G->AddEdge(12, 14);
    G->AddEdge(14, 13);
    G->AddEdge(13, 14);

    printf("GRAFO!\n\n");
    printf("Graph (%d, %d)\n", G->GetNodes(), G->GetEdges());
                                                                                                                                               
    for (PGraph::TObj::TNodeI NI = G->BegNI(); NI < G->EndNI(); NI++) {
        printf("  %d: ", NI.GetId());
        for (int e = 0; e < NI.GetDeg(); e++) { 
            printf(" %d", NI.GetNbrNId(e)); 
        }
        printf("\n");
    }
     
    IAssert(G->IsOk());

    /*Prim*/
    printf("Prim!");
    Prim(G, 1);

    /*Kruskal*/
    printf("Kruskal!");
    Kruskal(G);


    /*DELETE PART*/
    
    // delete edge
    PGraph::TObj::TNodeI NI = G->GetNI(1);
    printf("\n\nDelete edge %d -- %d\n\n", NI.GetId(), NI.GetOutNId(1));
    G->DelEdge(NI.GetId(), NI.GetOutNId(1));
    
    printf("Graph (%d, %d)\n", G->GetNodes(), G->GetEdges());
    for (PGraph::TObj::TNodeI NI = G->BegNI(); NI < G->EndNI(); NI++) {
        printf("  %d: ", NI.GetId());
        for (int e = 0; e < NI.GetDeg(); e++) {
            printf(" %d", NI.GetNbrNId(e)); }
        printf("\n");
    }
    
    IAssert(G->IsOk());
    
    //delete node
    PGraph::TObj::TNodeI N = G->GetNI(12);
    printf("\n\nDelete Node %d\n\n", N.GetId());
    G->DelNode(N.GetId());
    
    IAssert(G->IsOk());
    
    printf("Graph (%d, %d)\n", G->GetNodes(), G->GetEdges());
    for (PGraph::TObj::TNodeI NI = G->BegNI(); NI < G->EndNI(); NI++) {
        printf("  %d: ", NI.GetId());
        for (int e = 0; e < NI.GetDeg(); e++) {
            printf(" %d", NI.GetNbrNId(e)); 
        }
        printf("\n");    
    }
     
    return 0;
}
