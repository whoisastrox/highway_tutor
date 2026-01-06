#ifndef VEHICLE_H
#define VEHICLE_H //include guard Serve a evitare che l’header venga incluso più volte causando errori di compilazione.

#include <string>
#include <vector>
#include <utility>

using namespace std;

class Vehicle {
public:
    
    using IntervalloVelocita = std::pair<int, int>; //template di std che serve a contenere due valori insieme (anche differenti in caso si voglia), scritto per evita di scrivere sempre std::pair<int,int>

    //costruttore
    Vehicle(const std::string& targa, int svincoloIngresso, int svincoloUscita, double istanteIngresso, const std::vector<IntervalloVelocita>& profiloVelocita);

    //getter
    const std::string& getTarga() const;
    int getSvincoloIngresso() const;
    int getSvincoloUscita() const;
    double getIstanteIngresso() const;
    const vector<IntervalloVelocita>& getProfiloVelocita() const;

private:
    std::string targa;
    int svincoloIngresso;
    int svincoloUscita;
    double istanteIngresso;
    std::vector<IntervalloVelocita> profiloVelocita;
};

#endif
