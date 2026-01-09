#define _CRT_SECURE_NO_WARNINGS
#include "SIMULATORE_H.h"
#include "HIGHWAY_H.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include "FILE_ERROR_H.h"
#include <string>
#include <vector>
#include "DATATIME_H.h"
#include <random>
#include "VEHICLE_H.h"
#include "PROFILO_VELOCITA_H.h"
using namespace std;
int main() {
	srand(time(NULL));
	const int numVeicoli = 10000;

	try {
		Autostrada a = {};
		double trascorso = 0;

		time_t t = time(0);
		tm* adesso = localtime(&t);
		int anno = adesso->tm_year + 1900;
		int mese = adesso->tm_mon + 1;
		int giorno = adesso->tm_mday;
		int ore = adesso->tm_hour;
		int minuti = adesso->tm_min;
		double secondi = adesso->tm_sec;

		datatime d{ giorno,mese,anno,ore,minuti,secondi };
		//la data iniziale viene passata per reference in modo da essere incrementata ad ogni generazione
		//di un veicolo

		for (int i = 0; i < numVeicoli; i++) {
			creaVeicolo(a, d);
		}
		
		
	}
	catch (file_error& e) {
		cerr << e.what() << endl;
	}

	return 0;
}

static void creaVeicolo(Autostrada a, datatime& trascorso) {

	//generazione targa
	int rnd = 65+rand() % (26);
	string targa = "";
	targa += rnd;
	rnd = 65 + rand() % (26);
	targa += rnd;
	rnd = rand() % 11;
	targa += to_string(rnd);
	rnd = rand() % 11;
	targa += to_string(rnd);
	rnd = rand() % 11;
	targa += to_string(rnd);
	rnd = 65 + rand() % (26);
	targa += rnd;
	rnd = 65 + rand() % (26);
	targa += rnd;
	cout << targa<<endl;

	vector<svincolo> coppia = a.getCoppia();

	datatime d=impostaData(trascorso);
	cout << d << endl;
	
	profiloVelocita p = {};
	p.profiloCasuale(a.getLungh());

	//vehicle v{ targa, coppia[0], coppia[1], d, p };
	//modificare costruttore vehicle, togliere const, non servono

}

static double randomTime() { //genera un double tra 0.5 e 10
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> dist(0.5, 10.0); //definizione intervallo
	double time = dist(gen); //generazione valore
	time= floor(time * 100) / 100; //tronco a 2 decimali
	return time;
}

static datatime impostaData(datatime& d) {
	d.incrementaData(randomTime());
	return d;
}