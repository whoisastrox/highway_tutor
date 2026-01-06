#ifndef HIGHWAY_H
#define HIGHWAY_H
#include "SVINCOLO_H.h"
#include "VARCO_H.h"
#include <vector>
#include <iterator>
using namespace std;

class Autostrada {

private:
	vector<svincolo> svincoli;
	vector<varco> varchi;

public:
	Autostrada();
	void ordina();
	vector<svincolo>::iterator iterSvincoli();
	vector<varco>::iterator iterVarchi();


};


#endif

