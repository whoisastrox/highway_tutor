//Alessandro Bonato
#ifndef HIGHWAY_H
#define HIGHWAY_H
#include "SVINCOLO_H.h"
#include "VARCO_H.h"
#include <vector>
#include <iterator>
using namespace std;

class Autostrada {

private:
	vector<svincolo*> svincoli; //array di puntatori a svincoli e varchi perch� uso memoria heap
	vector<varco*> varchi;

public:
	Autostrada();
	void ordina();
	vector<svincolo*>::iterator iterSvincoli();
	vector<varco*>::iterator iterVarchi();
	vector<svincolo*>::iterator iterSvincoliEnd();
	vector<varco*>::iterator iterVarchiEnd();
	vector<svincolo> getCoppia();
	~Autostrada();
	double getLungh();
	Autostrada(const Autostrada&);
};


#endif

