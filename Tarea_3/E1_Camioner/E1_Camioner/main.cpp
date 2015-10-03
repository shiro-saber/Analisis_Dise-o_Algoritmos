#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

//suponemos que las gasolineras ya estan agregadas a un mapa.
using namespace std;

int siguientegas = 0; //cual es la siguiente gas
vector<int> mapa;

void paradas(int distancia, int eficiencia)
{
	int kuz = 0; //el tramo a recorrer
	int recorrido = 0; //el tramo que ha sido recorrido
	int paradas = 0; //numero de paradas

	while (recorrido < distancia)
	{
		if (recorrido + eficiencia < distancia)
		{
			if (siguientegas >= mapa.size())
			{
				cout << "Se paro " << paradas << " veces en el recorrido" << endl;
				return;
			}
			if (eficiencia < mapa[siguientegas])
			{
				cout << "No llega a la siguiente gas o ya no hay gas\n";
				return;
			}

			kuz += mapa[siguientegas];

			siguientegas++;

			if (kuz > eficiencia)
			{
				kuz -= mapa[--siguientegas];
				cout << "Se detuvo en una gas" << endl;
				recorrido += kuz;
				kuz = 0;
				paradas++;
			}
		}
		else
		{
			break;
		}
	}
	//cin.get();
}

int main()
{
	int distancia = 275;
	int eficiencia;
	//agregamos las gasolineras en el camino, cada una tiene su distancia diferente, en el vector solo se guarda la distancia en km
	mapa.push_back(50);
	mapa.push_back(30);
	mapa.push_back(65);
	mapa.push_back(43);
	mapa.push_back(78);

	cout << "Cual es la eficiencia km/l de tu coche" << endl;
	cin >> eficiencia;

	paradas(distancia, eficiencia);

	cin.get();
	return 0;
}