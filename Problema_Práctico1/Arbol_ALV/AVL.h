#pragma once
#include <iostream>
#include "Nodo.h"

using namespace std;

template<class DATO>
class AVL 
{   
   enum {IZQUIERDO, DERECHO};
   
   Nodo<DATO> *raiz;
   Nodo<DATO> *actual;
   int contador;
   int altura;
    
   void Equilibrar(Nodo<DATO> *nodo, int, bool);
   
   void RSI(Nodo<DATO>* nodo);
   void RSD(Nodo<DATO>* nodo);
   void RDI(Nodo<DATO>* nodo);
   void RDD(Nodo<DATO>* nodo);
   
   void Podar(Nodo<DATO>* &);
   void auxContador(Nodo<DATO>*);
   void auxAltura(Nodo<DATO>*, int);

  public:
   AVL() : raiz(nullptr), actual(nullptr) {}
   ~AVL() { Podar(raiz); }
   
   void Insertar(const DATO dat);
   void Borrar(const DATO dat);
   
   bool Buscar(const DATO dat);
   bool Vacio(Nodo<DATO> *r) { return r==nullptr; }
   bool EsHoja(Nodo<DATO> *r) { return !r->derecho && !r->izquierdo; }
   
   const int NumeroNodos();
   const int AlturaArbol();
   
   int Altura(const DATO dat);
   
   DATO &ValorActual() { return actual->dato; }
   
   void Raiz() { actual = raiz; }
   void InOrden(void (*func)(DATO&, int) , Nodo<DATO> *nodo=nullptr, bool r=true);
   void PreOrden(void (*func)(DATO&, int) , Nodo<DATO> *nodo=nullptr, bool r=true);
   void PostOrden(void (*func)(DATO&, int) , Nodo<DATO> *nodo=nullptr, bool r=true);
};

// borra todo desde el elemento dado
template<class DATO>
void AVL<DATO>::Podar(Nodo<DATO>* &nodo)
{
   if(nodo) 
   {
      Podar(nodo->izquierdo); // Podar izquierdo
      Podar(nodo->derecho);   // Podar derecho
      delete nodo;            // Eliminar nodo
      nodo = nullptr;
   }
}

// Insertar un dato en el árbol
template<class DATO>
void AVL<DATO>::Insertar(const DATO dat)
{
   Nodo<DATO> *padre = nullptr;

   cout << endl  << "Insertar: " << dat << endl;
   actual = raiz;
   
   while(!Vacio(actual) && dat != actual->dato) 
   {
      padre = actual;
      if(dat > actual->dato) 
          actual = actual->derecho;
      else if(dat < actual->dato) 
          actual = actual->izquierdo;
   }
   
   if(Vacio(padre)) 
       raiz = new Nodo<DATO>(dat);
   else if(dat < padre->dato) 
   {
      padre->izquierdo = new Nodo<DATO>(dat, padre);
      Equilibrar(padre, IZQUIERDO, true);
   }
   else if(dat > padre->dato) 
   {
      padre->derecho = new Nodo<DATO>(dat, padre);
      Equilibrar(padre, DERECHO, true);
   }
}

template<class DATO>
void AVL<DATO>::Equilibrar(Nodo<DATO> *nodo, int rama, bool nuevo)
{
   bool salir = false;

   while(nodo && !salir) 
   {
      if(nuevo)
         if(rama == IZQUIERDO) 
             nodo->FE--; 
         else                 
             nodo->FE++;
      else
         if(rama == IZQUIERDO) 
             nodo->FE++; 
         else                  
             nodo->FE--;
      
      if(nodo->FE == 0) 
          salir = true;
      else if(nodo->FE == -2) 
      { 
         if(nodo->izquierdo->FE == 1) 
             RDD(nodo); // Rotación doble
         else 
             RSD(nodo);// Rotación simple
         
         salir = true;
      }
      else if(nodo->FE == 2) 
      {  
         if(nodo->derecho->FE == -1) 
             RDI(nodo); // Rotación doble
         else 
             RSI(nodo);// Rotación simple
         
         salir = true;
      }
      
      if(nodo->padre) 
         if(nodo->padre->derecho == nodo) 
             rama = DERECHO; 
         else 
             rama = IZQUIERDO;
      
      nodo = nodo->padre; // Calcular FE, siguiente nodo del camino.
   }   
}

template<class DATO>
void AVL<DATO>::RDD(Nodo<DATO>* nodo)
{
   cout << "RDD" << endl;
   Nodo<DATO> *Padre = nodo->padre;
   Nodo<DATO> *P = nodo;
   Nodo<DATO> *Q = P->izquierdo;
   Nodo<DATO> *R = Q->derecho;
   Nodo<DATO> *B = R->izquierdo;
   Nodo<DATO> *C = R->derecho;

   if(Padre) 
     if(Padre->derecho == nodo) 
         Padre->derecho = R;
     else 
         Padre->izquierdo = R;
   else 
       raiz = R;

   // Reconstruir árbol:
   Q->derecho = B;
   P->izquierdo = C;
   R->izquierdo = Q;
   R->derecho = P;
   
   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) 
       B->padre = Q;
   if(C) 
       C->padre = P;

   switch(R->FE) 
   {
      case -1: 
          Q->FE = 0; 
          P->FE = 1; 
          break;
      case 0:  
          Q->FE = 0; 
          P->FE = 0; 
          break;
      case 1:  
          Q->FE = -1; 
          P->FE = 0; 
          break;
   }
   
   R->FE = 0;
}

template<class DATO>
void AVL<DATO>::RDI(Nodo<DATO>* nodo)
{
   cout << "RDI" << endl;
   Nodo<DATO> *Padre = nodo->padre;
   Nodo<DATO> *P = nodo;
   Nodo<DATO> *Q = P->derecho;
   Nodo<DATO> *R = Q->izquierdo;
   Nodo<DATO> *B = R->izquierdo;
   Nodo<DATO> *C = R->derecho;

   if(Padre) 
     if(Padre->derecho == nodo) 
         Padre->derecho = R;
     else 
         Padre->izquierdo = R;
   else 
       raiz = R;

   // Reconstruir árbol:
   P->derecho = B;
   Q->izquierdo = C;
   R->izquierdo = P;
   R->derecho = Q;
   
   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   
   if(B) 
       B->padre = P;
   if(C) 
       C->padre = Q;

   switch(R->FE) 
   {
      case -1: 
          P->FE = 0; 
          Q->FE = 1; 
          break;
      case 0:  
          P->FE = 0; 
          Q->FE = 0; 
          break;
      case 1:  
          P->FE = -1; 
          Q->FE = 0; 
          break;
   }
   
   R->FE = 0;
}

template<class DATO>
void AVL<DATO>::RSD(Nodo<DATO>* nodo)
{
   cout << "RSD" << endl;
   Nodo<DATO> *Padre = nodo->padre;
   Nodo<DATO> *P = nodo;
   Nodo<DATO> *Q = P->izquierdo;
   Nodo<DATO> *B = Q->derecho;

   if(Padre) 
     if(Padre->derecho == P) 
         Padre->derecho = Q;
     else 
         Padre->izquierdo = Q;
   else 
       raiz = Q;

   // Reconstruir árbol:
   P->izquierdo = B;
   Q->derecho = P;
   
   // Reasignar padres:
   P->padre = Q;
   if(B) 
       B->padre = P;
   
   Q->padre = Padre;

   P->FE = 0;
   Q->FE = 0;
}

template<class DATO>
void AVL<DATO>::RSI(Nodo<DATO>* nodo)
{
   cout << "RSI" << endl;
   Nodo<DATO> *Padre = nodo->padre;
   Nodo<DATO> *P = nodo;
   Nodo<DATO> *Q = P->derecho;
   Nodo<DATO> *B = Q->izquierdo;

   if(Padre) 
     if(Padre->derecho == P) 
         Padre->derecho = Q;
     else 
         Padre->izquierdo = Q;
   else 
       raiz = Q;

   // Reconstruir árbol:
   P->derecho = B;
   Q->izquierdo = P;
   
   P->padre = Q;
   if(B) 
       B->padre = P;
   
   Q->padre = Padre;
   
   P->FE = 0;
   Q->FE = 0;
}

template<class DATO>
void AVL<DATO>::Borrar(const DATO dat)
{
   Nodo<DATO> *padre = nullptr;
   Nodo<DATO> *nodo;
   DATO aux;
   
   actual = raiz;
   
   // Mientras sea posible que el valor esté en el árbol
   while(!Vacio(actual)) 
   {
      if(dat == actual->dato) 
      { // Si el valor está en el nodo actual
         if(EsHoja(actual)) 
         { // Y si además es un nodo hoja: lo borramos
            if(padre) 
                if(padre->derecho == actual) 
                    padre->derecho = nullptr;
               else if(padre->izquierdo == actual) 
                   padre->izquierdo = nullptr;
            delete actual; // Borrar el nodo
            actual = nullptr;
            
            if((padre->derecho == actual && padre->FE == 1) || (padre->izquierdo == actual && padre->FE == -1)) 
            {
               padre->FE = 0;
               actual = padre;
               padre = actual->padre;
            }
            
            if(padre)
               if(padre->derecho == actual) 
                   Equilibrar(padre, DERECHO, false);
               else                         
                   Equilibrar(padre, IZQUIERDO, false);
            return;
         }
         else 
         { 
            padre = actual;
            
            if(actual->derecho) 
            {
               nodo = actual->derecho;
               while(nodo->izquierdo) 
               {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            
            else 
            {
               nodo = actual->izquierdo;
                while(nodo->derecho) 
                {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else 
      { 
         padre = actual;
         if(dat > actual->dato) 
             actual = actual->derecho;
         else if(dat < actual->dato) 
             actual = actual->izquierdo;
      }
   }
}

template<class DATO>
void AVL<DATO>::InOrden(void (*func)(DATO&, int) , Nodo<DATO> *nodo, bool r)
{
   if(r) 
       nodo = raiz;
   
   if(nodo->izquierdo) 
       InOrden(func, nodo->izquierdo, false);
   
   func(nodo->dato, nodo->FE);
   
   if(nodo->derecho) 
       InOrden(func, nodo->derecho, false);
}

template<class DATO>
void AVL<DATO>::PreOrden(void (*func)(DATO&, int), Nodo<DATO> *nodo, bool r)
{
   if(r) 
       nodo = raiz;
   
   func(nodo->dato, nodo->FE);
   
   if(nodo->izquierdo) 
       PreOrden(func, nodo->izquierdo, false);
   
   if(nodo->derecho) 
       PreOrden(func, nodo->derecho, false);
}

template<class DATO>
void AVL<DATO>::PostOrden(void (*func)(DATO&, int), Nodo<DATO> *nodo, bool r)
{
   if(r) 
       nodo = raiz;
   
   if(nodo->izquierdo) 
       PostOrden(func, nodo->izquierdo, false);
   
   if(nodo->derecho) 
       PostOrden(func, nodo->derecho, false);
   
   func(nodo->dato, nodo->FE);
}

// Buscar un valor en el árbol
template<class DATO>
bool AVL<DATO>::Buscar(const DATO dat)
{
   actual = raiz;
    
   while(!Vacio(actual)) 
   {
      if(dat == actual->dato) 
          return true; // dato encontrado
      else if(dat > actual->dato) 
          actual = actual->derecho; // Seguir
      else if(dat < actual->dato) 
          actual = actual->izquierdo;
   }
   return false; // No está en árbol
}

template<class DATO>
int AVL<DATO>::Altura(const DATO dat)
{
   int altura = 0;
   actual = raiz;

   while(!Vacio(actual)) 
   {
      if(dat == actual->dato) 
          return altura; // dato encontrado
      else 
      {
         altura++; // Incrementamos la altura, seguimos buscando
         if(dat > actual->dato) 
             actual = actual->derecho;
         else if(dat < actual->dato) 
             actual = actual->izquierdo;
      }
   }
   return -1;
}

// Contar el número de nodos
template<class DATO>
const int AVL<DATO>::NumeroNodos()
{
   contador = 0;

   auxContador(raiz);
   return contador;
}

template<class DATO>
void AVL<DATO>::auxContador(Nodo<DATO> *nodo)
{
   contador++;  

   if(nodo->izquierdo) 
       auxContador(nodo->izquierdo);
   if(nodo->derecho)   
       auxContador(nodo->derecho);
}

template<class DATO>
const int AVL<DATO>::AlturaArbol()
{
   altura = 0;

   auxAltura(raiz, 0);
   return altura;
}

template<class DATO>
void AVL<DATO>::auxAltura(Nodo<DATO> *nodo, int a)
{
   if(nodo->izquierdo) 
       auxAltura(nodo->izquierdo, a+1);
   
   if(nodo->derecho)   
       auxAltura(nodo->derecho, a+1);
   
   if(EsHoja(nodo) && a > altura) 
       altura = a;
}
