#include "../inc/VEHICLE_H.h"
#include <string>
#include "../inc/PROFILO_VELOCITA_H.h"
#include <iostream>
using namespace std;
vehicle::vehicle(const string& targa, svincolo svincoloIngresso, svincolo svincoloUscita, datatime istanteIngresso, const profiloVelocita& p) : targa(targa), svincoloIngresso(svincoloIngresso), svincoloUscita(svincoloUscita), istanteIngresso(istanteIngresso), p(p) {}

//getter
const string& vehicle::getTarga() const { return targa; }
svincolo vehicle::getSvincoloIngresso() const { return svincoloIngresso; }
svincolo vehicle::getSvincoloUscita() const { return svincoloUscita; }
datatime vehicle::getIstanteIngresso() const { return istanteIngresso; }
const profiloVelocita& vehicle::getProfiloVelocita() const { return p; }

ostream& operator<<(ostream& os, const vehicle& v) {
    os << "<" << v.getTarga()
        << "> <" << v.getSvincoloIngresso().getId()
        << "> <" << v.getSvincoloUscita().getId()
        << "> <" << v.getIstanteIngresso() <<"> "
        <<v.getProfiloVelocita();
    return os;
}

datatime* vehicle::getPassaggio(double tempo) {
    datatime* d = new datatime;
    *d = istanteIngresso;
    //cout << istanteIngresso;
    (*d).incrementaData(tempo);
    return d;
}

string vehicle::toString() {
    return "<" + targa
        + "> <" + to_string(svincoloIngresso.getId())
        + "> <" + to_string(svincoloUscita.getId())
        + "> <" + (istanteIngresso.toString()) + "> " + p.toString();
}

vehicle::~vehicle() {
    targa = "";
    svincoloIngresso = svincolo();
    svincoloUscita = svincolo();
    istanteIngresso = datatime();
    p = profiloVelocita();
}
