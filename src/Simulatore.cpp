//Alessandro Bonato
#define _CRT_SECURE_NO_WARNINGS
#include "../inc/SIMULATORE_H.h"
#include "../inc/HIGHWAY_H.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include "../inc/FILE_ERROR_H.h"
#include <string>
#include <vector>
#include "../inc/DATATIME_H.h"
#include <random>
#include "../inc/VEHICLE_H.h"
#include "../inc/PROFILO_VELOCITA_H.h"
#include <fstream>
using namespace std;
int main() {
	const int numVeicoli = 10000;

	ofstream pass("./Data/Passages.txt");
	if (!pass.is_open()) {
		throw runtime_error("errore nell'apertura del file Passages.txt");
	}
	pass << "";
	pass.close();


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
		ofstream out("./Data/Runs.txt");
		if (!out.is_open()) {
			throw runtime_error("errore nell'apertura del file Runs.txt");
		}
		string runs = "";
		string passages = "";
		for (int i = 0; i < numVeicoli; i++) {
			vehicle* v=creaVeicolo(a, d, passages);
			runs+=(*v).toString()+"\n";
			delete v;
			cout << "*";
		}
		out << runs;
		out.close();
		out=ofstream("./Data/Passages.txt", ios::app);
		if (!out.is_open()) {
			throw runtime_error("errore nell'apertura del file Passages.txt");
		}
		out << passages;
		out.close();
		
		
	}
	catch (file_error& e) {
		cerr << e.what() << endl;
	}

	return 0;
}

static vehicle* creaVeicolo(Autostrada a, datatime& trascorso, string& passages) {
	string targa = "";
	//generazione targa
	random_device random;
	mt19937 m(random());
	uniform_int_distribution<int> lettere{ 'A', 'Z' };
	uniform_int_distribution<int> cifre{ 0, 9 };
	targa += static_cast<char>(lettere(m));
	targa += static_cast<char>(lettere(m));
	targa += to_string(cifre(m));
	targa += to_string(cifre(m));
	targa += to_string(cifre(m));
	targa += static_cast<char>(lettere(m));
	targa += static_cast<char>(lettere(m));
	//cout << targa<<endl;

	vector<svincolo> coppia = a.getCoppia();

	datatime d=impostaData(trascorso);
	//cout << d << endl;
	
	profiloVelocita p = {};
	p.profiloCasuale(a.getLungh());

	const profiloVelocita profilo = p;

	const string t = targa;

	vehicle* v =new vehicle(t, coppia[0], coppia[1], d, profilo );

	//generazione passaggio per i varchi:
	a.ordina();
	auto iter = a.iterVarchi();
	while (iter != a.iterVarchiEnd() && (*iter)->getDist()<=coppia[1].getDist()) {
		if ((*iter)->getDist() >= coppia[0].getDist()) {
			double tempo = p.getIstantePassaggio((*iter)->getDist());
			//cout << tempo << endl;
			datatime* data = (*v).getPassaggio(tempo);
			passages = passages + "<" + to_string((*iter)->getId()) + "> <" + ((*v).getTarga()) + "> <" + (*data).toString() + ">\n";
			delete data;
		}
		iter++;
	}


	return v;

}

static double randomTime() { //genera un double tra 0.5 e 10
	random_device random;
	mt19937 m(random());
	uniform_real_distribution<double> tempo{ 0.5, 10.0 }; //definizione intervallo
	double time = tempo(m); //generazione valore
	time= floor(time * 1000) / 1000; //tronco a 3 decimali
	return time;
}

static datatime impostaData(datatime& d) {
	d.incrementaData(randomTime());
	return d;
}