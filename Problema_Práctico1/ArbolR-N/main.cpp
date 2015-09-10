//
//  main.cpp
//  Ejercicio3
//
//  Created by SeijiJulianPerezSchimidzu on 09/09/15.
//  Copyright (c) 2015 ITESM CSF. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <iostream>
using namespace std;


#define N 100000
#define RED		1
#define BLACK	2

struct node {
	int key;
	struct node *left, *right, *p;
	int color;
};

typedef struct node *NODEPTR;
struct node NIL;
NODEPTR NILPTR = &NIL;

void inorder(NODEPTR x) {
	if (x != NILPTR) {
		inorder(x->left);
		printf("%d ", x->key);
		inorder(x->right);
	}
}

void inorderB(NODEPTR x)
{
    if (x != NILPTR)
    {
        
        inorderB(x->right);
		printf("%d ", x->key);
		inorderB(x->left);
	}
}

NODEPTR search(NODEPTR root, int k) {
	if (root == NILPTR || root->key == k)
		return root;
	if (k < root->key)
		return search(root->left, k);
	else
		return search(root->right, k);
}

NODEPTR minimum(NODEPTR root) {
	while (root->left != NILPTR)
		root = root->left;
	return root;
}

NODEPTR maximum(NODEPTR root) {
	while (root->right != NILPTR)
		root = root->right;
	return root;
}

NODEPTR successor(NODEPTR root, int x) {
	NODEPTR temp = search(root, x);
	if (temp == NILPTR) {
		printf("%d not in tree\n", x);
		return temp;
	}
	if (temp->right != NILPTR)
		return minimum(temp->right);
	NODEPTR y = temp->p;
	while (y != NILPTR && temp == y->right) {
		temp = y;
		y = y->p;
	}
	return y;
}

NODEPTR predecessor(NODEPTR root, int x) {
	NODEPTR temp = search(root, x);
	if (temp == NILPTR) {
		printf("%d not in tree\n", x);
		return temp;
	}
	if (temp->left != NILPTR)
		return maximum(temp->left);
	NODEPTR y = temp->p;
	while (y != NILPTR && temp == y->left) {
		temp = y;
		y = y->p;
	}
	return y;
}
void leftrotate(NODEPTR *treeroot, NODEPTR x) {
	NODEPTR y = x->right;
	x->right = y->left;
	if (y->left != NILPTR)
		y->left->p = x;
	y->p = x->p;
	if (x->p == NILPTR)
		*treeroot = y;
	else if (x->p->left == x)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

void rightrotate(NODEPTR *treeroot, NODEPTR y) {
	NODEPTR x = y->left;
	y->left = x->right;
	if (x->right != NILPTR)
		x->right->p = y;
	x->p = y->p;
	if (y->p == NILPTR)
		*treeroot = x;
	else if (y->p->left == y)
		y->p->left = x;
	else
		y->p->right = x;
	x->right = y;
	y->p = x;
}

void rbinsertfixup(NODEPTR *treeroot, NODEPTR z) {
	while (z->p->color == RED) {
		if (z->p == z->p->p->left) {
			NODEPTR y = z->p->p->right;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->right) {
					z = z->p;
					leftrotate(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				rightrotate(treeroot,z->p->p);
			}
		}
		else {
			NODEPTR y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->left) {
					z = z->p;
					rightrotate(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				leftrotate(treeroot,z->p->p);
			}
		}
	}
	(*treeroot)->color = BLACK;
}

void rbinsert(NODEPTR *treeroot, int z) {
	NODEPTR Z = (NODEPTR) malloc(sizeof(struct node));
	Z->key = z;
	NODEPTR y = NILPTR;
	NODEPTR x = *treeroot;
	while (x != NILPTR) {
		y = x;
		if (Z->key < x->key)
			x = x->left;
		else if (Z->key > x->key)
			x = x->right;
        else return;
	}
	Z->p = y;
	if (y == NILPTR)
		*treeroot = Z;
	else if (Z->key < y->key)
		y->left = Z;
	else
		y->right = Z;
	Z->left = NILPTR;
	Z->right = NILPTR;
	Z->color = RED;
	rbinsertfixup(treeroot,Z);
}

void rbtransplant(NODEPTR *treeroot, NODEPTR u, NODEPTR v) {
	if (u->p == NILPTR)
		*treeroot = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

void rbdeletefixup(NODEPTR *treeroot, NODEPTR x) {
	while (x != *treeroot && x->color == BLACK) {
		if (x == x->p->left) {
			NODEPTR w = x->p->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				leftrotate(treeroot,x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else {
			 	if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rightrotate(treeroot,w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				leftrotate(treeroot,x->p);
				x = *treeroot;
			}
		}
		else {
			NODEPTR w = x->p->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				rightrotate(treeroot,x->p);
				w = x->p->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					leftrotate(treeroot,w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				rightrotate(treeroot,x->p);
				x = *treeroot;
			}
		}
	}
	x->color = BLACK;
}

void rbdelete(NODEPTR *treeroot, int z) {
	NODEPTR Z = search(*treeroot, z);
	if (Z == NILPTR) {
		printf("Node to be deleted not found\n");
		return;
	}
	NODEPTR y = Z;
	int yoc = y->color;
	NODEPTR x;
	if (Z->left == NILPTR) {
		x = Z->right;
		rbtransplant(treeroot,Z,Z->right);
	}
	else if (Z->right == NILPTR) {
		x = Z->left;
		rbtransplant(treeroot,Z,Z->left);
	}
	else {
		y = minimum(Z->right);
		yoc = y->color;
		x = y->right;
		if (y->p == Z)
			x->p = y;
		else {
			rbtransplant(treeroot,y,y->right);
			y->right = Z->right;
			y->right->p = y;
		}
		rbtransplant(treeroot,Z,y);
		y->left = Z->left;
		y->left->p = y;
		y->color = Z->color;
	}
	if (yoc == BLACK)
		rbdeletefixup(treeroot,x);
}

int rbnivel(NODEPTR root, int z)
{
    NODEPTR temp = root;
    int nivel = 0;
    temp = search(temp, z);
    if (temp == NILPTR) {
		printf("No se encontro el nodo\n");
		return -1;
	}
	temp = root;
    
	while(temp != NILPTR)
    {
        if(z == temp->key ) return nivel;
        else
        {
            nivel++;
            if(z > temp->key) temp = temp->right;
            else if (z < temp->key) temp = temp->left;
        }
        
    }
    
    
	return nivel;
}

int rbaltura(NODEPTR root)
{
    if (root == NILPTR)
    {
        return -1;
    }
    
    int left = rbaltura(root->left);
    int right = rbaltura(root->right);
    
    return 1 + std::max(left, right);
}

int main(int argc, const char * argv[])
{
	NIL.left = NIL.right = NIL.p = NILPTR;
	NIL.color = BLACK;
	NODEPTR tree = NILPTR;
	int n;
    
	clock_t t;

	//arreglo para agregar al arbol
	srand((int)time(NULL));
	int arreglo[N];
	t = clock();

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
	
	for (int d = 0; d < N; d++)
		rbinsert(&tree, arreglo[d]);

	//inorder(tree);

	t = clock() - t;
	printf("Tarde %f segundo(s), para acabar el árbol AVL", (float)t / CLOCKS_PER_SEC);

	cin.get();
	//for (int x = 0; x < N; x++)
		
    /*double secs;
    clock_t t1, t2;
    //int arreglo[N];
    int a;
    
    srand(16);
    for(int i = 0; i <N; i++)
    {
        a = (rand()%1000000)+1;
        rbinsert(&tree, a);
        arreglo[i] = a;
    }
    
    for(int i = 0; i < 10; i++)
    {
		t1 = clock();
        a = (rand()%N)+1;
        search(tree, arreglo[a]);
        t2 = clock();
        secs = (double)(t2 - t1)/CLOCKS_PER_SEC;
        cout<<"numero: "<<i+1 <<" tiempo.  " ;
        std::cout << "Tomo " << secs * 1000 << " milisegundos" << std::endl;
        
    }
    
    
    
	while (1) {
		printf("1.Insert\n2.Search\n3.Inorder\n4.Inorder (Desc)\n5.Delete\n6.Nivel/Profundidad\n7.Altura\n8.Exit\n");
		scanf_s("%d", &n);
		if (n == 1) {
			printf("Ingrese un numero:\n");
			int num;
			scanf_s("%d", &num);
			rbinsert(&tree, num);
			printf("nivel: %d\n", rbnivel(tree, num));
			printf("altura: %d\n",rbaltura(search(tree, num)));
		}
		else if (n == 2) {
			printf("Ingrese el numero a buscar:\n");
			int num;
			scanf_s("%d", &num);
			if (search(tree, num) == NILPTR)
				printf("%d not found\n", num);
			else
				printf("%d found\n", num);
		}
		else if (n == 3) {
			inorder(tree);
			printf("\n");
		}
		else if (n == 4)
        {
            inorderB(tree);
			printf("\n");
        }
        
		else if (n == 5)
        {
			printf("Ingrese el numero que desea borrar:\n");
			int num;
			scanf_s("%d", &num);
			rbdelete(&tree, num);
		}
		else if (n == 6)
        {
            printf("Ingrese el numero cuyo nivel desea encontrar:\n");
			int num;
			scanf_s("%d", &num);
			printf("nivel: %d\n", rbnivel(tree, num));
            
        }
        else if (n == 7)
        {
            printf("Ingrese el numero cuya altura desea encontrar:\n");
			int num;
			scanf_s("%d", &num);
			NODEPTR encontrado = search(tree,num);
            
			if(encontrado != NILPTR)
                printf("altura: %d\n",rbaltura(encontrado));
            else
                printf("Nodo no encontrado");
        }
        else
			break;
	}*/
	return 0;
}

