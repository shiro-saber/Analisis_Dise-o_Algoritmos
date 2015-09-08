#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <iterator> 
#include <time.h>
#include<vector>
#include "AVL.h"
#include "Arbol23.h"

#define N 100000

using namespace std;

template <class DATO>
void Mostrar(DATO &d, int FE)
{
   cout << d << "(" << FE << "),";
}

int main()
{
    clock_t t;
    
    //arreglo para agregar al arbol
    srand((int)time(NULL));
    int arreglo[N];
    
    for (int i = 0; i < N; i++)
    {
        int r;
       bool encontrado = true;
	while(encontrado)
       {
             encontrado = false;
            r = rand() % 1000000;
            for (int x = 0; x < N; x++)
   	   {
                  if ( r == arreglo[x])
		  {
                         encontrado = true;
                        break;
                 }
           } 
       }	
        arreglo[i] = r;
    } 
    t = clock();
   
   AVL<int> ArbolInt;
   Arbol23<int> ArbolInt2;
   
   Arbol23<int>::Node *inserted_node = nullptr;

   //Agregar el arbol
   for (int j = 0; j < N; j++)
   {
        ArbolInt.Insertar(arreglo[j]);
        inserted_node = ArbolInt2.insert(j);
   }
   
   ArbolInt2.Traverse([](int x) { cout << x << ' ';});
   ArbolInt.InOrden(Mostrar);   

   /*cout  << endl << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;
   cout << "N nodos: " << ArbolInt.NumeroNodos() << endl;
   cout << "Altura de 1 " << ArbolInt.Altura(1) << endl;
   cout << "Altura de 10 " << ArbolInt.Altura(10) << endl;
   cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;*/

   t = clock() - t;
   
   printf ("Tarde %f segundo(s), para acabar el árbol AVL", (float)t/CLOCKS_PER_SEC);
   
   cin.get();
   return 0;
}
