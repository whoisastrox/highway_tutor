#ifndef VEHICLE_H
#define VEHICLE_H 
#include <string>
#include "PROFILO_VELOCITA_H.h"
using namespace std;
class vehicle {
    private:
        string targa;
        int svincoloIngresso;
        int svincoloUscita;
        double istanteIngresso;
        profiloVelocita p;

    public: 
        vehicle(const string& targa, int svincoloIngresso, int svincoloUscita, double istanteIngresso, const profiloVelocita& p);
        const string& getTarga() const;
        int getSvincoloIngresso() const;
        int getSvincoloUscita() const;
        double getIstanteIngresso() const;
        const profiloVelocita& getProfiloVelocita() const;
};
#endif
