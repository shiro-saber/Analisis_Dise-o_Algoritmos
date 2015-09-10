//
//  types.h
//  Ejercicio2
//
//  Created by SeijiJulianPerezSchimidzu on 09/09/15.
//  Copyright (c) 2015 ITESM CSF. All rights reserved.
//

#ifndef Ejercicio2_types_h
#define Ejercicio2_types_h


template <typename T>
T return_type()
{
	return T();
}

template <>
char return_type<char>()
{
	return '\0';
}

template <>
int return_type<int>()
{
	return -1;
}

template <>
float return_type<float>()
{
	return -1.0f;
}

template <>
double return_type<double>()
{
	return -1.0;
}

template <typename T>
bool encapsulate()
{
	
}


#endif
