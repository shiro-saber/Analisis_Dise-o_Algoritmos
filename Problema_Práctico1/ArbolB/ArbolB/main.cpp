//
//  main.cpp
//  Ejercicio2
//
//  Created by SeijiJulianPerezSchimidzu on 09/09/15.
//  Copyright (c) 2015 ITESM CSF. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include "b_tree.h"

using namespace std;

#define TYPE int
#define N 100000

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
		while (encontrado)
		{
			encontrado = false;
			r = rand() % 1000000;
			for (int x = 0; x < N; x++)
			{
				if (r == arreglo[x])
				{
					encontrado = true;
					break;
				}
			}
		}
		arreglo[i] = r;
	}
	t = clock();
	BTree<int> tree(1, 5);
	//tree.insert(3);
	//tree.insert(9);
	t = clock() - t;

	cout << tree;
	printf("Tarde %f segundo(s), para acabar el árbol AVL", (float)t / CLOCKS_PER_SEC);

	cin.get();
	return 0;
}

