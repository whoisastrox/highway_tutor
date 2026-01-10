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
#include <ctime>
#include <cmath>
using namespace std;
int main() {
    const int numVeicoli = 10;

    try {
        Autostrada a;  // inizializza autostrada da file

        // prendi data/ora corrente
        time_t t = time(nullptr);
        tm* adesso = localtime(&t);

        datatime d{
            adesso->tm_mday,
            adesso->tm_mon + 1,
            adesso->tm_year + 1900,
            adesso->tm_hour,
            adesso->tm_min,
            static_cast<double>(adesso->tm_sec)
        };

        cout << "=== Generazione veicoli ===\n";
        for (int i = 0; i < numVeicoli; ++i) {
            cout << "\nVeicolo #" << (i + 1) << endl;

            // creazione veicolo con targa casuale, coppia di svincoli e profilo velocità
            auto coppia = a.getCoppia(); 

            profiloVelocita p;
            double lunghezza = a.getLungh();
            p.profiloCasuale(lunghezza); // genera velocità casuali fino alla lunghezza autostrada

            creaVeicolo(a, d); // stampa targa e data

            // stampiamo info sul profilo velocità per verifica
            cout << "Profilo velocità:\n";
            const auto& intervalli = p.getIntervalli();
            for (size_t j = 0; j < intervalli.size(); ++j) {
                cout << "  Intervallo " << j+1 
                     << ": velocità=" << intervalli[j].velocita
                     << " km/h, durata=" << intervalli[j].durata << " min\n";
            }

            // stampiamo distanza totale percorsa per controllo
            cout << "Distanza totale percorsa (stimata): " 
                 << p.distanzaPercorsa() << " km\n";
        }

        cout << "\n=== Test getCoppia() ===\n";
        for (int i = 0; i < 5; ++i) { // test più coppie casuali
            auto coppia = a.getCoppia();
            cout << "Coppia casuale #" << (i+1) 
                 << ": ingresso a distanza " << coppia[0].getDist()
                 << ", uscita a distanza " << coppia[1].getDist() << endl;
        }

    } catch (file_error& e) {
        cerr << "Errore file: " << e.what() << endl;
    } catch (exception& e) {
        cerr << "Errore: " << e.what() << endl;
    }

    return 0;
}
static random_device rd;
static mt19937 gen(rd());//genera numeri pseudo-casuali
static uniform_int_distribution<int> distLettere('A', 'Z');
static uniform_int_distribution<int> distNumeri(0, 9);
static uniform_real_distribution<double> distTempo(0.0, 1.0); //utilizzo in randomTime()
//uniform_int_distribution<int> genera numeri interia casuali in un intervallo definito in maniera uniforme, quindi tutti i numeri hanno la stessa probabilità di capitare	
static void creaVeicolo(Autostrada a, datatime& trascorso) {
	//generazione targa
	string targa;
    targa.reserve(7);
    targa += static_cast<char>(distLettere(gen));//prendo una lettera maiuscola casuale
    targa += static_cast<char>(distLettere(gen));
    targa += to_string(distNumeri(gen));
    targa += to_string(distNumeri(gen));
    targa += to_string(distNumeri(gen));
    targa += static_cast<char>(distLettere(gen));
    targa += static_cast<char>(distLettere(gen));
	cout << targa<<endl;

	vector<svincolo> coppia = a.getCoppia();

	datatime d=impostaData(trascorso);
	cout << d << endl;
	
	profiloVelocita p = {};
	p.profiloCasuale(a.getLungh());

	//vehicle v{ targa, coppia[0], coppia[1], d, p };
	//modificare costruttore vehicle, togliere const, non servono

}

static double randomTime() {
	double time = distTempo(gen); //generazione valore
	time= floor(time * 100) / 100; //tronco a 2 decimali
	return time;
}

static datatime impostaData(datatime& d) {
	d.incrementaData(randomTime());
	return d;
}