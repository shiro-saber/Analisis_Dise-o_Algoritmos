#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <sstream>
#include <list>

using namespace std;
//ajusatr como cosntante la longitud de la jsutificacion
const int pageWidth = 70;
typedef std::list<std::string> WordList;


//se divide en renglones menores que L, luego se espacian hasta que lleguen a ~L 
WordList splitTextIntoWords(const std::string &text)
{
	WordList words;
	std::istringstream in(text);
	std::copy(std::istream_iterator<string>(in),
		std::istream_iterator<std::string>(),
		std::back_inserter(words));
	return words;
}

void justifyLine(std::string line)
{
	size_t pos = line.find_first_of(' ');
	if (pos != std::string::npos) {
		while (line.size() < pageWidth) {
			pos = line.find_first_not_of(' ', pos);
			line.insert(pos, " ");
			pos = line.find_first_of(' ', pos + 1);
			if (pos == std::string::npos) {
				pos = line.find_first_of(' ');
			}
		}
	}
	std::cout << line << std::endl;
}

void justifyText(const std::string &text)
{
	WordList words = splitTextIntoWords(text);

	std::string line;
	for (const std::string& word : words) {
		if (line.size() + word.size() + 1 > pageWidth) { // siguiente palabra no entra en la línea
			justifyLine(line);
			line.clear();
			line = word;
		}
		else {
			if (!line.empty()) {
				line.append(" ");
			}
			line.append(word);
		}
	}
	std::cout << line << std::endl;
}




int main()
{
	string parrafo;
	getline(cin, parrafo);
	
	justifyText("La radio fue el primer medio que llevo "

		"Las estaciones de radio salen por novedad "
		"Dependeindo el rating, es decir la demanda, según eso lo que ponían.Tener el mayor éxito "
		"Epezaorn con noticias, deportes, música, etc. "
		"La economía de los 20 ayudo al desarrollo de la radio "
		"Mayor comercialización "
		"Surgen distintos generos musicales "
		"Surgen radio difusoras.Empeizan a tener presencia en la radio.No había segmentación como hoy en día.Una estación podía tener a distintas horas distintas cosas, ej: musca, noticas, novela. "

		"En los 40 fue el mayor auge.Noticias en vivo.La segunda guerra mundial, la gente quería saber que apsaba. "
		"Concepto de estrellas.Reporteros estrellas.Quien estaba detras ");
	system("PAUSE");
	return 0;
}