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

    for (PGraph::TObj::TNodeI NI = G->BegNI(); NI < G->EndNI(); NI++){
        printf("  %d: ", NI.GetId());
        for (int e = 0; e < NI.GetDeg(); e++) {
            printf(" %d", NI.GetNbrNId(e));
        }
        printf("\n");
    }

    IAssert(G->IsOk());
  //BFS
  TSnap::GetBfsTree (G, 1, true, true);

  //DFS
  //TSccVisitor<PNGraph,true>::TSccVisitor(&G);

  //PRIM

  //KRUSKAL
  
  //DIJKSTRA
  
  //FLOYD-WARSHALL
  
  
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
