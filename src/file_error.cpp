//Alessandro Bonato
#include "../inc/FILE_ERROR_H.h"
#include <stdexcept>
file_error::file_error(int x) :runtime_error("Errore file"), error_value(x) {}
const char* file_error::what() const noexcept{
	switch (error_value)
	{
		case 0: return "formattazione del file errata";break;
		case 1: return "il secondo argomento di ogni riga deve essere S (svincolo) o V (varco)";break;
		case 2: return "il file Highway.txt presenta meno di 2 varchi"; break;
		case 3: return "ci sono varchi che sono a distanza minore di 1km da uno svincolo"; break;
		case 4: return "devono esserci almeno uno svincolo prima del primo varco e almeno uno svincolo successivo all'ultimo varco"; break;
		default: return "errore misterioso :/"; break;
	}
}