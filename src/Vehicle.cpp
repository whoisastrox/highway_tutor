#include "Vehicle.h"

//costruttore
Vehicle::Vehicle(const std::string& targa, int svincoloIngresso, int svincoloUscita, double istanteIngresso, const std::vector<IntervalloVelocita>& profiloVelocita) : targa(targa), svincoloIngresso(svincoloIngresso), svincoloUscita(svincoloUscita), istanteIngresso(istanteIngresso), profiloVelocita(profiloVelocita){ }

//getter
const std::string& Vehicle::getTarga() const { return targa; }
int Vehicle::getSvincoloIngresso() const { return svincoloIngresso; }
int Vehicle::getSvincoloUscita() const { return svincoloUscita; }
double Vehicle::getIstanteIngresso() const { return istanteIngresso; }
const std::vector<Vehicle::IntervalloVelocita>& Vehicle::getProfiloVelocita() const { return profiloVelocita; }
