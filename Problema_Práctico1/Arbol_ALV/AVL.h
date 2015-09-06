#pragma once
#include <iostream>
#include "Nodo.h"

using namespace std;

class AVL 
{
    enum {IZQUIERDO, DERECHO};

   Nodo *raiz; //pointer a la raíz
   Nodo *actual; //nodo en el que estamos
   
   int contador;
   int altura;
   
   // Funciones de rotación simples y dobles
   void Equilibrar(Nodo *nodo, int, bool);
   void RSI(Nodo* nodo);
   void RSD(Nodo* nodo);
   void RDI(Nodo* nodo);
   void RDD(Nodo* nodo);
   
   // Funciones auxiliares
   void Podar(Nodo* &);
   void auxContador(Nodo*);
   void auxAltura(Nodo*, int);
public:
   AVL() : raiz(NULL), actual(NULL) {}
   ~AVL() { Podar(raiz); }
   
   // Insertar en árbol ordenado:
   void Insertar(const int dat);
   void Borrar(const int dat);
   
   bool Buscar(const int dat);
   bool Vacio(Nodo *r) { return r==NULL; }
   bool EsHoja(Nodo *r) { return !r->derecho && !r->izquierdo; }
   
   const int NumeroNodos();
   const int AlturaArbol();
   
   int Altura(const int dat);
   int &ValorActual() { return actual->dato; }
   
   void Raiz() { actual = raiz; }
   void InOrden(void (*func)(int&, int) , Nodo *nodo=NULL, bool r=true);
   void PreOrden(void (*func)(int&, int) , Nodo *nodo=NULL, bool r=true);
   void PostOrden(void (*func)(int&, int) , Nodo *nodo=NULL, bool r=true);
};
