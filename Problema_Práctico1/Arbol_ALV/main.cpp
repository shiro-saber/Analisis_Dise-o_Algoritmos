#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <iterator> 
#include <time.h>
#include<vector>
#include "AVL.h"

#define N 100000

using namespace std;

void Mostrar(int &d, int FE)
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
        arreglo[i] = rand() % 10;
    } 
    
    clock_t t;
    t = clock();
   // Un árbol de enteros
   AVL ArbolInt;

   //Agregar el arbol
   for (int j = 0; j < N; j++)
   
       ArbolInt.Insertar(arreglo[j]);
   /*ArbolInt.Insertar(15);
   ArbolInt.Insertar(4);
   ArbolInt.Insertar(20);
   ArbolInt.Insertar(3);
   ArbolInt.Insertar(25);
   ArbolInt.Insertar(6);
   ArbolInt.Insertar(8);
   ArbolInt.Insertar(1);
   ArbolInt.Insertar(2);
   ArbolInt.Insertar(3);
   ArbolInt.Insertar(4);
   ArbolInt.Insertar(5);
   ArbolInt.Insertar(6);
   ArbolInt.Insertar(7);
   ArbolInt.Insertar(8);
   ArbolInt.Insertar(9);
   ArbolInt.Insertar(10);
   ArbolInt.Insertar(11);
   ArbolInt.Insertar(12);
   ArbolInt.Insertar(13);
   ArbolInt.Insertar(14);
   ArbolInt.Insertar(15);
   ArbolInt.Insertar(16);
    */
   
   cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;

   // Ver el arbol en los diferentes ordenes
   cout << "InOrden: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   cout << "PreOrden: ";
   ArbolInt.PreOrden(Mostrar);
   cout << endl;
   cout << "PostOrden: ";
   ArbolInt.PostOrden(Mostrar);
   cout << endl;

   cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;

   // Ver el arbol en los diferentes ordenes
   cout << "InOrden: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   cout << "PreOrden: ";
   ArbolInt.PreOrden(Mostrar);
   cout << endl;
   cout << "PostOrden: ";
   ArbolInt.PostOrden(Mostrar);
   cout << endl;

   // Prueba de balanceo despues de borrar
   cout << "N nodos: " << ArbolInt.NumeroNodos() << endl;
  /* ArbolInt.Borrar(25);
   cout << "Borrar   25: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   ArbolInt.Borrar(8);
   cout << "Borrar   8: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   ArbolInt.Borrar(15);
   cout << "Borrar  15: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   ArbolInt.Borrar(245);
   cout << "Borrar 245: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   ArbolInt.Borrar(4);
   cout << "Borrar   4: ";
   ArbolInt.InOrden(Mostrar);
   ArbolInt.Borrar(17);
   cout << endl;
   cout << "Borrar  17: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;*/

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