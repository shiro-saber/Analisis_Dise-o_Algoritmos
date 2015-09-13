//
//  b_tree.h
//  Ejercicio2
//
//  Created by SeijiJulianPerezSchimidzu on 09/09/15.
//  Copyright (c) 2015 ITESM CSF. All rights reserved.
//

#include <fstream>
#include <string>
#include "helpers.cpp"

#ifndef Ejercicio2_b_tree_h
#define Ejercicio2_b_tree_h

template <typename T>
class BTree;

template <typename T>
std::ostream& operator<<(std::ostream&, BTree<T>&);

template <typename T>
class BTree
{
	// Record position of the root node
	int root;
    
	// Size of the B-tree nodes, nodesNum -> minimum elements, 2 * nodesNum -> maximum elements
	int n;
    
	// Number of values that fit in a record, 2 * n
	int valueNum;
    
	int pointerNum;
    
	// Size in bytes of the data contained in the node
	int valueSize;
    
	// Size in bytes of the pointer to the next node
	int recPointerSize;
    
	// Size of each record of the B-tree, int + 2n * valueSize + (2n + 1) * recPointerSize
	int recSize;
    
	// Total number of records in the file
	int numOfRecords;
    
	// Handler to binary read and write
	std::fstream *fbin;
    
	// Opens a file in binary read/write mode, receives the file specification
	void openFile(std::string);

	void crudRecord(int numOfValues, int recordNumber, int & nodeSize, T * valueArray, int * pointerArray, ((void(*)(std::fstream::* operation))(const char *, std::streamsize)));
    
	// Writes a record to the file, receives the index it will write into
	// and references to the values to be stored
	void writeRecord(int, int&, T*, int*);
    
    
	//void crudRecord(int, int, int&, T*, int*, void (std::fstream::*operation)(const char*, std::streamsize));
    
	// Reads a record from the file, it receives the record index
	// and references to the variables where it's going to be stored
	void readRecord(int, int&, T*, int*);
    
	//Split a record into two
	void split(int, T*, int*);
    
	T* nuevos;
    
public:
	// Constructors
	BTree(int N) : root(-1),
    n(N),
    valueSize(sizeof(T)),
    recPointerSize(sizeof(int)),
    recSize(sizeof(int) + (2 * n * valueSize) + ((2 * n + 1) * recPointerSize))
    {}
    
	BTree(int N, T value, std::string fileName = "data.txt") : root(0),
    n(N),
    valueSize(sizeof(T)),
    recPointerSize(sizeof(int)),
    recSize(sizeof(int) + (2 * n * valueSize) + ((2 * n + 1) * recPointerSize))
    {
        valueNum = 2 * n;
        pointerNum = 2 * n + 1;
        
        openFile(fileName);
        int nodeSize = 1;
        T* valueArray = new T[2*n];
        for (int i = 1; i < 2 * n; ++i)
        {
            valueArray[i] = -1;
        }
        valueArray[0] = value;
        int* pointerArray = new int[2*n + 1];
        for (int i = 0; i < 2 * n + 1; ++i)
        {
            pointerArray[i] = -1;
        }
        
        writeRecord(0, nodeSize, valueArray, pointerArray);
        //crudRecord(n, 0, nodeSize, valueArray, pointerArray, &std::fstream::write);
    }
    
	// Destructor
	~BTree();
    
	// Insert a value into the tree
	void insert(T);
    
	friend std::ostream& operator<< <>(std::ostream&, BTree<T>&);
};

template <typename T>
void BTree<T>::openFile(std::string fileName)
{
	fbin = new std::fstream(fileName.c_str(), std::ios::binary | std::ios::in | std::ios::out);
	if (!fbin)
	{
		throw "Error: Could not open file " + fileName;
	}
}


template <typename T>
void BTree<T>::crudRecord(int numOfValues, int recordNumber, int& nodeSize, T* valueArray, int* pointerArray, ((void (*)(std::fstream::*operation))(const char*, std::streamsize)))
{
	// Move the file pointer to the start of our record
	fbin->seekp(recordNumber * recSize);
    
	// Read the number of values in the record
	(fbin->*operation)(reinterpret_cast<char*>(&nodeSize), sizeof(int));
    
	// Read the values in the record
	(fbin->*operation)(reinterpret_cast<char*>(valueArray), sizeof(T) * numOfValues);
    
	// Read the pointers in the record
	(fbin->*operation)(reinterpret_cast<char*>(pointerArray), sizeof(int) * numOfValues);
}


template <typename T>
void BTree<T>::writeRecord(int recordNumber, int& nodeSize, T* valueArray, int* pointerArray)
{
	// Move the file pointer to the start of our node
	fbin->seekp(recordNumber * recSize);
    
	// Read the number of values in the node
	fbin->write(reinterpret_cast<char*>(&nodeSize), sizeof(int));
    
	// Read the values in the node
	fbin->write(reinterpret_cast<char*>(valueArray), sizeof(T) * valueNum);
    
	// Read the pointers in the node
	fbin->write(reinterpret_cast<char*>(pointerArray), sizeof(int) * pointerNum);
}

template <typename T>
void BTree<T>::readRecord(int recordNumber, int& nodeSize, T* valueArray, int* pointerArray)
{
	// Move the file pointer to the start of our node
	fbin->seekp(recordNumber * recSize);
    
	// Read the number of values in the node
	fbin->read(reinterpret_cast<char*>(&nodeSize), sizeof(int));
    
	// Read the values in the node
	fbin->read(reinterpret_cast<char*>(valueArray), sizeof(T) * valueNum);
    
	// Read the pointers in the node
	fbin->read(reinterpret_cast<char*>(pointerArray), sizeof(int) * pointerNum);
}


template <typename T>
BTree<T>::~BTree()
{
	delete fbin;
}

template <typename T>
void BTree<T>::split(int recordNumber, T* valueArray, int* pointerArray, int valuePosition, T value)
{
    
	// Create a new array with the new value inserted in its position
	T* record = new T[valueNum + 1];
	int i = j = 0;
	while (i < valueNum + 1)
	{
		if (i == valuePosition)
		{
			record[i] = value;
			--j;
		}
		else
		{
			record[i] = valueArray[j];
		}
		++i;
		++j;
	}
    
	T middleValue = record[valueNum / 2];
    
	// Left record with the first half of values
	writeRecord(recordNumber,
                valueNum / 2,
                newArray(valueNum, 0, valueNum / 2, valueArray),
                newArray(valueNum, 0, valueNum / 2, pointerArray));
    
	// Right record with the second half of values
	writeRecord(numOfRecords++,
                valueNum / 2,
                newArray(valueNum, valueNum / 2, valueNum, valueArray),
                newArray(valueNum, valueNum / 2, valueNum, pointerArray));
    
	insert(recordNumber, valueArray, pointerArray, valuePosition, T value)
}

template <typename T>
void BTree<T>::insert(int recordNumber, T* valueArray, int* pointerArray, int valuePosition, T value)
{
	int leftRecord = recordNumber;
	int rightRecord = numOfRecords;
    
	T* record = new T[valueNum + 1];
	int i = j = 0;
	while (i < valueNum + 1)
	{
		if (i == valuePosition)
		{
			record[i] = value;
			--j;
		}
		else
		{
			record[i] = valueArray[j];
		}
		++i;
		++j;
	}
    
}

template <typename T>
void BTree<T>::insert(T value)
{
	int temp = root;
	int nodeSize;
	T* valueArray = new T[valueNum];
	int* pointerArray = new int[pointerNum];
	while (temp != -1)
	{
		std::cout << "temp: " << temp << std::endl;
        
		// Read the record from the file
		readRecord(temp, nodeSize, valueArray, pointerArray);
        
		// Search for the position the value should be inserted into
		int i = 0;
		while (i < nodeSize && valueArray[i] < value)
		{
			++i;
		}
        
		// If it's equal we don't insert it
		if (valueArray[i] == value)
		{
			return;
		}
		else
		{
			// If there is no other node we have can move to
			if (pointerArray[i] == -1)
			{
				// If there is enough space in the node, insert it there
				if (nodeSize < valueNum)
				{
					for (int j = nodeSize; j > i; --j)
					{
						valueArray[j] = valueArray[j - 1];
					}
					valueArray[i] = value;
                    
					// We made the changes on RAM, now we write them back to the record in the file
					writeRecord(temp, nodeSize, valueArray, pointerArray);
				}
				else	// Otherwise create two new nodes and divide the values between both
				{
					split(temp, valueArray, pointerArray, i, value);
				}
			}
            
			// We set temp to the new node's record number,
			// if it's -1 the loop will exit since we already inserted the value,
			// otherwise it will continue and repeat the read process
			temp = pointerArray[i];
		}
	}
    
	delete[] valueArray;
	delete[] pointerArray;
}

template <typename T>
std::ostream& operator<<(std::ostream& ostream, BTree<T>& refObj)
{
	return ostream;
}


#endif
