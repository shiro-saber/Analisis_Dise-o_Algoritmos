#include <cstdlib>
#include "Arbol23.h"
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int main(int argc, char** argv) 
{
    vector<int> v { 10, 20, 30, 40, 50 ,60, 70 , 80, 90, 37, 36, 35, 34 };
    
    int size = sizeof(v)/sizeof(int);
    
    Arbol23<int> tree;
        
    Arbol23<int>::Node *inserted_node = nullptr;

    for(auto i = v.begin(); i != v.end(); ++i) 
    {    
        inserted_node = tree.insert(*i);
    }
      
    tree.Traverse([](int x){ cout << x << ' '; });       
    tree.remove(10);
    tree.remove(36);  
   
    tree.Traverse([](int x){ cout << x << ' '; }); // This blows up because we do not have a proper tree.
     
    cout << "\n------------\n" << endl;
    cout << endl;
    return 0;
}


