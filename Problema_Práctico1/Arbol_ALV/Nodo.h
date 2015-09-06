#pragma once
#include <iostream>

using namespace std;

template<class DATO> class AVL;

template<class DATO>
class Nodo 
{
  public:
   Nodo(const DATO dat, Nodo<DATO> *pad=nullptr, Nodo<DATO> *izq=nullptr, Nodo<DATO> *der=nullptr) : dato(dat), padre(pad), izquierdo(izq), derecho(der), FE(0) {}
   
   DATO dato;
   
   int FE;
   
   Nodo<DATO> *izquierdo;
   Nodo<DATO> *derecho;
   Nodo<DATO> *padre;
   
   friend class AVL<DATO>;
};
