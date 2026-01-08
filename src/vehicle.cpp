#include "VEHICLE_H.h"
#include <string>
#include "PROFILO_VELOCITA_H.h"
using namespace std;
vehicle::vehicle(const string& targa, int svincoloIngresso, int svincoloUscita, double istanteIngresso, const profiloVelocita& p) : targa(targa), svincoloIngresso(svincoloIngresso), svincoloUscita(svincoloUscita), istanteIngresso(istanteIngresso), p(p) {}

//getter
const string& vehicle::getTarga() const { return targa; }
int vehicle::getSvincoloIngresso() const { return svincoloIngresso; }
int vehicle::getSvincoloUscita() const { return svincoloUscita; }
double vehicle::getIstanteIngresso() const { return istanteIngresso; }
const profiloVelocita& vehicle::getProfiloVelocita() const { return p; }
