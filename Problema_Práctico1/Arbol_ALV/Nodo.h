#pragma once
#include <iostream>

using namespace std;

//class AVL;

class Nodo 
{
  public:
   Nodo(const int dat, Nodo *pad=nullptr, Nodo *izq=nullptr, Nodo *der=nullptr) : dato(dat), padre(pad), izquierdo(izq), derecho(der), FE(0) {}

   int dato;
   int FE;
   
   Nodo *izquierdo;
   Nodo *derecho;
   Nodo *padre;
   
   friend class AVL;
};
