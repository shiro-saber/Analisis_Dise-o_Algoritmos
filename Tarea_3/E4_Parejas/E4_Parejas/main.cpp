#include <iostream>
#include<cstdlib>
#define N 4

using namespace std;

int M[N][N]{ { 2, 4, 3, 1 },{ 3, 1, 2, 4 },{ 1, 3, 4, 2 },{ 4, 2, 1, 3 } }; //mujeres
int H[N][N]{ { 4, 2, 1, 3 },{ 2, 1, 4, 3 },{ 3, 4, 1, 2 },{ 2, 3, 4, 1 } }; //hombres
int ordenM[N][N]{ { 3, 2, 4, 1 },{ 2, 1, 4, 3 },{ 3, 4, 1, 2 },{ 4, 1, 2, 3 } }; //orden mujeres
int ordenH[N][N]{ { 4, 1, 3, 2 },{ 2, 3, 1, 4 },{ 1, 4, 2, 3 },{ 3, 2, 4, 1 } }; //orden hombres
int X[N];
int Y[N];

bool libre[N]{ 1, 1, 1, 1 }; //si esta libre
bool logro;

bool estable(int h, int m, int p)
{
	bool s = 1;
	int mejorMujer, mejorHombre, limite;
	int i = 1;

	while (i < p && s)
	{
		mejorMujer = M[h][i];
		i++;

		if (!libre[mejorMujer])
			s = ordenM[mejorMujer, h] > ordenM[mejorMujer, Y[mejorMujer]];
	}

	i = 1;
	limite = H[m][h];

	while (i < limite && s)
	{
		mejorHombre = H[m][i];
		i++;

		if (mejorHombre < h)
			s = ordenH[mejorHombre][m] > ordenH[mejorHombre][X[mejorHombre]];
	}
	return s;
}
void armaParejas(int hombre, bool exito) 
{
	int mujer = 0;
	int prefiere = 0;
	int preferencia = 0;

	while (!exito) 
	{
		for (prefiere = 0; prefiere < N; ++prefiere) 
		{
			mujer = M[hombre][prefiere];

			if (libre[mujer] && estable(hombre, mujer, prefiere)) 
			{
				X[hombre] = mujer;
				Y[mujer] = hombre;
				libre[mujer] = 0;

				if (hombre < N) 
					armaParejas(hombre + 1, exito);

				if (!exito) 
					libre[mujer] = 1;
			}
			else
				exito = 1;
		}
	}
}

int main() 
{

	armaParejas(0, logro);

	for (int i = 0; i < N; ++i)
		cout << "El hombre " << i << " quedo con la mujer " << X[i] << "\n";

	system("pause");
	return 0;
}