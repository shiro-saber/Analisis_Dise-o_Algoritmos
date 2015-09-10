//
//  inner_node.h
//  Ejercicio2
//
//  Created by SeijiJulianPerezSchimidzu on 09/09/15.
//  Copyright (c) 2015 ITESM CSF. All rights reserved.
//

#include "types.h"
#include <iostream>

#ifndef Ejercicio2_inner_node_h
#define Ejercicio2_inner_node_h

template <typename T>
class InnerNode;

template <typename T>
std::ostream& operator<<(std::ostream&, InnerNode<T>&);

template <typename T>
class InnerNode
{
private:
	/* Pointer to the next node in the linked-list. */
	InnerNode<T>* nextInnerNode;
    
	/* Generic type/object with the data contained by the node. */
	T value;
    
public:
	/* Constructors */
	InnerNode() : value(return_type<T>()), nextInnerNode(NULL) {}
	InnerNode(T Value, InnerNode<T>* NextInnerNode) : value(Value), nextInnerNode(NextInnerNode) {}
	InnerNode(T Value) : value(Value), nextInnerNode(NULL) {}
	InnerNode(InnerNode<T>* NextInnerNode) : value(return_type<T>()), nextInnerNode(NextInnerNode) {}
    
	/* Destructor */
	~InnerNode();
    
	/* Setter, getter for |nextInnerNode| */
	void setNextNode(InnerNode<T>*);
	InnerNode<T>* getNextNode();
    
	/* Setter, getter for |value| */
	void setValue(T);
	T getValue();
    
	/* ostream << operator overload */
	friend std::ostream& operator<< <>(std::ostream&, InnerNode<T>&);
};

template <typename T>
void InnerNode<T>::setNextNode(InnerNode<T>* NextInnerNode)
{
	nextInnerNode = NextInnerNode;
}

template <typename T>
InnerNode<T>* InnerNode<T>::getNextNode()
{
	return nextInnerNode;
}

template <typename T>
void InnerNode<T>::setValue(T Value)
{
	value = Value;
}

template <typename T>
T InnerNode<T>::getValue()
{
	return value;
}

template <typename T>
std::ostream& operator<<(std::ostream& ostream, InnerNode<T>& refObj)
{
	ostream << refObj.getValue();
	return ostream;
}

#endif
