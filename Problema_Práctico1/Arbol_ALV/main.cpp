#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <iterator> 
#include <time.h>
#include<vector>
#include "AVL.h"

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

   //Agregar el arbol
   for (int j = 0; j < N; j++)
   {
        ArbolInt.Insertar(arreglo[j]);
   }

   t = clock() - t;
   
   printf ("Tarde %f segundo(s), para acabar el árbol AVL", (float)t/CLOCKS_PER_SEC);
   
   cin.get();
   return 0;
}
