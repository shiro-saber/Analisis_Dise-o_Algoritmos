//
//  main.cpp
//  Ejercicio2
//
//  Created by SeijiJulianPerezSchimidzu on 09/09/15.
//  Copyright (c) 2015 ITESM CSF. All rights reserved.
//

#include <iostream>
#include "b_tree.h"

#define TYPE int

int main()
{
	using namespace std;
	BTree<int> tree(1, 5);
	tree.insert(3);
	tree.insert(9);
	cout << tree;
	return 0;
}

