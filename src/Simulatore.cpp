#include "SIMULATORE_H.h"
#include "HIGHWAY_H.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include "FILE_ERROR_H.h"
#include <string>
#include <vector>
#include "DATATIME_H.h"
using namespace std;
int main() {
	try {
		Autostrada a = {};
		creaVeicolo(a);
		
	}
	catch (file_error& e) {
		cerr << e.what() << endl;
	}

	return 0;
}

static void creaVeicolo(Autostrada a) {
	srand(time(NULL));

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

	datatime d{};
	d.fillRandomData();

	cout << d << endl;

}