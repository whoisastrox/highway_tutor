#ifndef VEHICLE_H
#define VEHICLE_H 
#include <string>
#include "PROFILO_VELOCITA_H.h"
#include "DATATIME_H.h"
#include "SVINCOLO_H.h"
#include <iostream>
using namespace std;
class vehicle {
    private:
        string targa;
        svincolo svincoloIngresso;
        svincolo svincoloUscita;
        datatime istanteIngresso;
        profiloVelocita p;

    public: 
        vehicle(const string& targa, svincolo svincoloIngresso, svincolo svincoloUscita, datatime istanteIngresso, const profiloVelocita& p);
        const string& getTarga() const;
        svincolo getSvincoloIngresso() const;
        svincolo getSvincoloUscita() const;
        datatime getIstanteIngresso() const;
        const profiloVelocita& getProfiloVelocita() const;
        ~vehicle();
        datatime* getPassaggio(double);
        string toString();
        
};

ostream& operator<<(ostream& os, const vehicle& v);

#endif
