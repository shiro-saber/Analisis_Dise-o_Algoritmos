//
//  b_tree_node.h
//  Ejercicio2
//
//  Created by SeijiJulianPerezSchimidzu on 09/09/15.
//  Copyright (c) 2015 ITESM CSF. All rights reserved.
//

#include <iostream>
#include "types.h"
#include "node.h"

#ifndef Ejercicio2_b_tree_node_h
#define Ejercicio2_b_tree_node_h

template <typename T>
class BTreeNode;

template <typename T>
std::ostream& operator<<(std::ostream&, BTreeNode<T>&);

template <typename T>
class BTreeNode
{
private:
	int recordNum;
	int size;
	int maxSize;
	int parent;
    
	T* valuesArray;
	int* pointersArray;
    
public:
	/* Constructors */
	BTreeNode(int MaxSize) : maxSize(MaxSize), firstElement(NULL) {}
	BTreeNode(InnerNode<T>* FirstNode, int MaxSize) : maxSize(MaxSize), firstNode(FirstNode) {}
    
	/* Desctructor */
	~BTreeNode();
    
	/* Returns true if the linked-list is full, false otherwise */
	bool isFull();
    
	/* Returns the size of the linked-list */
	int size();
    
	/* Returns true if the value was found in the list, false otherwise */
	bool find(T);
    
	/* Inserts the node in the list */
	void insert(T);
    
	/* Deletes the node with the value passed from the linked-list */
	void delete(T);
};

template <typename T>
BTreeNode<T>::~BTreeNode()
{
	InnerNode<T>* temp = root;
	while (temp != NULL)
	{
		InnerNode<T>* deleteNode = temp;
		temp = temp->getNextNode();
		delete deleteNode;
	}
}

template <typename T>
void BTreeNode<T>::setFirstNode(InnerNode<T>* FirstNode)
{
	firstNode = FirstNode;
}

template <typename T>
InnerNode<T>* BTreeNode<T>::getFirstNode()
{
	return firstNode;
}

template <typename T>
bool BTreeNode<T>::isFull()
{
	if (size >= maxSize)
	{
		return true;
	}
	return false;
}

template <typename T>
int BTreeNode<T>::size()
{
	return size;
}

template <typename T>
bool BTreeNode<T>::find(T value)
{
	InnerNode<T>* temp = root;
	while (temp != NULL)
	{
		if (temp->getValue() == value)
		{
			return true;
		}
		temp = temp->getNextNode();
	}
	return false;
}

template <typename T>
bool BTreeNode<T>::insert(InnerNode<T>* node)
{
	InnerNode<T>* temp = root;
	while (temp != NULL)
	{
		if (temp->getValue() >= node->getValue())
		{
			break;
		}
		temp = temp->getNextNode();
	}
    
	if (temp == NULL)
	{
		lastNode->setNextNode(node);
		lastNode = node;
	}
	else
	{
		node->setNextNode(temp->getNextNode());
		temp->setNextNode(node);
	}
    
	size++;
}

template <typename T>
void BTreeNode<T>::delete(T value)
{
	InnerNode<T>* currentNode = root;
	if (root != NULL)
	{
		InnerNode<T>* nextNode = root->getNextNode();
		while (currentNode != NULL)
		{
			if (currentNode->getValue() == value)
			{
                
			}
		}
	}
}


#endif
