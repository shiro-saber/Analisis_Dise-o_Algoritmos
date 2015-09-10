//
//  helpers.cpp
//  Ejercicio2
//
//  Created by SeijiJulianPerezSchimidzu on 09/09/15.
//  Copyright (c) 2015 ITESM CSF. All rights reserved.
//

#include "types.h"

template <typename T>
T* newArray(int size, int start, int end, T* arr)
{
	T* newArr = new T[size];
	int i = 0;
	T returnValue = return_type();
    
	while (i < start)
	{
		newArr[i] = returnValue;
		++i;
	}
    
	while (i < end)
	{
		newArr[i] = arr[i];
		++i;
	}
    
	while (i < size)
	{
		newArr[i] = returnValue;
		++i;
	}
    
	return newArr;
}