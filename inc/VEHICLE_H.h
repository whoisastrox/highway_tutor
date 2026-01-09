#ifndef VEHICLE_H
#define VEHICLE_H 
#include <string>
#include "PROFILO_VELOCITA_H.h"
#include "DATATIME_H.h"
using namespace std;
class vehicle {
    private:
        string targa;
        int svincoloIngresso;
        int svincoloUscita;
        datatime istanteIngresso;
        profiloVelocita p;

    public: 
        vehicle(const string& targa, int svincoloIngresso, int svincoloUscita, datatime istanteIngresso, const profiloVelocita& p);
        const string& getTarga() const;
        int getSvincoloIngresso() const;
        int getSvincoloUscita() const;
        datatime getIstanteIngresso() const;
        const profiloVelocita& getProfiloVelocita() const;
};
#endif
