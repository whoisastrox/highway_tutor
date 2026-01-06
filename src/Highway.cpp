#include "HIGHWAY_H.h"
#include "SVINCOLO_H.h"
#include "VARCO_H.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "FILE_ERROR_H.h"
#include <string>
#include <sstream>
using namespace std;
Autostrada::Autostrada(){
	ifstream fileInput("Highway.txt");
    string riga;	
	while (std::getline(fileInput, riga)) {
		stringstream ss(riga);
		double distanza;
		char tipo;
		char scarto; //dove metto gli scarti(<>)	
		//std::cout << riga;
		if (!(ss >> scarto >> distanza >> scarto >> scarto >> tipo >> scarto)) { //salta in automatico gli scarti
			throw file_error(0);
		}
		std::cout << "dist:" << distanza << "tipo:" << tipo<<endl;
		double dist = distanza;
		if (tipo == 'S') {
			svincolo s{dist};
			svincoli.push_back(s);
		}
		else if (tipo == 'V') {
			varco v{ dist };
			varchi.push_back(v);
		}
		else {
			throw file_error(1);
		}
		
	}
	//ci sono meno di 2 varchi?
	if (varchi.size() < 2) {
		throw file_error(2);
	}
	//dist minima tra svincolo e varco di 1 km
	for (int i = 0; i < varchi.size(); i++) {
		for (int j = 0; j < svincoli.size(); j++) {
			if ((abs(varchi[i].getDist() - svincoli[j].getDist()) < 1)) {
				throw file_error(3);
			}
		}
	}
	//almeno uno svincolo prima del primo varco e almeno uno svincolo successivo all'ultimo varco
	ordina();
	if (varchi[0].getDist() < svincoli[0].getDist() || varchi[varchi.size() - 1].getDist() > svincoli[svincoli.size() - 1].getDist()) {
		throw file_error(4);
	}
	
}

void Autostrada::ordina() {
	std::sort(varchi.begin(), varchi.end(),
		[](const varco& a, const varco& b)
		{ return a.getDist() < b.getDist(); }
	);

	std::sort(svincoli.begin(), svincoli.end(),
		[](const svincolo& a, const svincolo& b)
		{ return a.getDist() < b.getDist(); }
	);
}