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
    //arreglo para agregar al arbol
    srand((int)time(NULL));
    int arreglo[N];
    for (int i = 0; i < N; i++)
    {
        arreglo[i] = rand() % 10000;
    } 
    
    clock_t t;
    t = clock();
   // Un árbol de enteros
   AVL<int> ArbolInt;

   //Agregar el arbol
   for (int j = 0; j < N; j++)
   {
        ArbolInt.Insertar(arreglo[j]);
        ArbolInt.InOrden(Mostrar);
   }
   
   cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;

   // Ver el arbol en los diferentes ordenes
   cout << "InOrden: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;

   cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;
   
   // Veamos algunos parámetros
   cout << "N nodos: " << ArbolInt.NumeroNodos() << endl;
   cout << "Altura de 1 " << ArbolInt.Altura(1) << endl;
   cout << "Altura de 10 " << ArbolInt.Altura(10) << endl;
   cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;

   t = clock() - t;
   
   printf ("Tarde %f segundo(s), para acabar el árbol AVL", (float)t/CLOCKS_PER_SEC);
   
   cin.get();
   return 0;
}