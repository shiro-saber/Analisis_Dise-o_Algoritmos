#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC //unicamente para checar memory leaks.
#include<iostream>

using namespace std;

char b[100][100];
int c[100][100];

void LCS(char X[], char Y[])
{
	int m, n, i, j;
	m = strlen(X) - 1;
	n = strlen(Y) - 1;

	/*Se empiezan a llenar en 0 */
	for (i = 1; i <= m; i++)
		c[i][0] = 0;

	for (j = 0; j <= n; j++)
		c[0][j] = 0;

	/*a partir de aqui vamos a seleccionar donde hay ocurrencias y las ponemos*/
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (X[i] == Y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = '/';
			}
			else
			{
				if (c[i - 1][j] >= c[i][j - 1])
				{
					c[i][j] = c[i - 1][j];
					b[i][j] = '|';

				}
				else
				{
					c[i][j] = c[i][j - 1];
					b[i][j] = '-';
				}
			}
		}
	}
}

void llenamela(char M[])
{
	int i;
	char a;

	a = getchar();
	M[1] = a;
	i = 2;

	while (a != 10)
	{
		a = getchar();
		M[i] = a;
		i++;
	}

	M[i - 1] = '\0';
}

void imprimir_LCS(char X[], int i, int j) 
// Imprime cada caracter igual del Vector B en A
{
	if (i == 0 || j == 0)
		return;

	if (b[i][j] == '/')
	{
		imprimir_LCS(X, i - 1, j - 1);
		cout << X[i];
	}
	else
		/* recursividad \o/*/
		if (b[i][j] == '|')
			imprimir_LCS(X, i - 1, j);
		else
			imprimir_LCS(X, i, j - 1);
}
int main()
{
	//nada mas cambia el color de la terminal porque yolo jajaja
	system("color B0");
	char kuz[100], sharmuta[100];
	int tamkuz, tamsharmuta;

	cout << " Problema de la SubSecuencia Comun Mas Larga Con PD" << endl;

	cout << "\t Ingresa Cadena A: ";
	llenamela(kuz);
	fflush(stdin); //evita leaks, limpia el stdin

	cout << "\t Ingresa Cadena B: ";
	llenamela(sharmuta);
	fflush(stdin);

	tamkuz = strlen(kuz);
	tamsharmuta = strlen(sharmuta);
	LCS(kuz, sharmuta);

	cout << endl;
	//La tabla es una matriz que es creada dependiendo de la longitud de ambas palabras, se va llenando con un i+1 cada que hay una ocurrencia y donde se procude.
	cout << "\t\tTABLA DINAMICA";
	cout << endl;

	for (int i = 0; i <= tamkuz - 1; i++)
	{
		cout << "\t\t";
		for (int j = 0; j <= tamsharmuta; j++)
			if (j + 1 == tamsharmuta + 1)
				cout << endl;

			else
				cout << " " << c[i][j];
	}
	cout << "\n";
	cout << " La Subsecuencia comun mas larga B en A: " << endl << endl;

	//La subsecuencia que es igual
	cout << "{ ";
	imprimir_LCS(kuz, tamkuz - 1, tamsharmuta - 1);
	cout << " }" << endl;
	cout << endl;

	//Cuantas veces se encuentran caracteres iguales en ambos strings
	cout << "El numero de ocurrencia es: ";
	cout << c[tamkuz - 1][tamsharmuta - 1] << endl << endl;

	system("Pause");
	return 0;
}
#endif