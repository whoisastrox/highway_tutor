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
			svincolo* s = new svincolo(dist); //uso allocazione dinamica, altrimenti quando esco dallo
												//scope s viene deallocato, lo stesso per il varco
			svincoli.push_back(s);
		}
		else if (tipo == 'V') {
			varco* v = new varco(dist);
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
			if ((abs((*varchi[i]).getDist() - (*svincoli[j]).getDist()) < 1)) { //uso dereference perchè ho dei vector di puntatori
				throw file_error(3);
			}
		}
	}
	//almeno uno svincolo prima del primo varco e almeno uno svincolo successivo all'ultimo varco
	ordina();
	if ((*varchi[0]).getDist() < (*svincoli[0]).getDist() || (*varchi[varchi.size() - 1]).getDist() > (*svincoli[svincoli.size() - 1]).getDist()) {
		throw file_error(4);
	}
	
}

void Autostrada::ordina() {
	std::sort(varchi.begin(), varchi.end(),
		[](const varco* a, const varco* b)
		{ return a->getDist() < b->getDist(); }
	);

	std::sort(svincoli.begin(), svincoli.end(),
		[](const svincolo* a, const svincolo* b)
		{ return a->getDist() < b->getDist(); }
	);
}

vector<svincolo*>::iterator Autostrada::iterSvincoli() {
	return svincoli.begin();
}
vector<varco*>::iterator Autostrada::iterVarchi() {
	return varchi.begin();
}
vector<svincolo> Autostrada::getCoppia() {
	srand(time(NULL)); //inizializzazione per generazione numeri random
	int ingresso, uscita;
	if (svincoli.size() == 2) {
		ingresso = 0;
		uscita = 1;
	}
	else {
		ingresso = rand() % (svincoli.size() - 2); //genera un numero casuale tra 0 e v.size()-2 in modo da non includere l'ultimo svincolo come svincolo di ingresso
		uscita = ingresso + 1 + rand() % (svincoli.size() - 1);//genera un numero casuale successivo a ingresso e che sia al massimo l'ultimo svincolo
	}
	if (uscita > svincoli.size() - 1) {
		uscita = svincoli.size() - 1;
	}
	ordina(); //ordino gli svincoli (e anche i varchi) in modo da poter prendere lo svincolo nel vector con indice ingresso/uscita correttamente
	vector<svincolo> ret;
	ret.push_back(*svincoli[ingresso]);
	ret.push_back(*svincoli[uscita]);
	return ret;
}

Autostrada::~Autostrada() { //dealloco gli svincoli e i varchi contenuti nei vector perchè allocati nella heap
	for (int i = 0; i < varchi.size(); i++) {
		delete varchi[i];
	}
	for (int i = 0; i < svincoli.size(); i++) {
		delete svincoli[i];
	}
}
double Autostrada::getLungh() {
	ordina();
	return svincoli[svincoli.size()-1]->getDist();
}
