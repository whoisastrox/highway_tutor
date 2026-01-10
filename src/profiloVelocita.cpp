#include "../inc/PROFILO_VELOCITA_H.h"
#include <cstdlib>
#include <cmath>
#include <vector>
#include <random>
using namespace std;

profiloVelocita::profiloVelocita() {
    intervalli={ };
}

void profiloVelocita::aggiungiIntervallo(int velocita, int durata) {
    intervalli.push_back({velocita, durata});
}
const vector<profiloVelocita::intervallo>& profiloVelocita::getIntervalli() const {
    return intervalli;
}
double profiloVelocita::distanzaPercorsa() const {
    double distanza = 0.0;
    /*for(int i=0; i<intervalli.size(); i++){
        distanza += intervalli[i].velocita*(intervalli[i].durata/60.0);
    }*/
    for(const auto& i : intervalli) {
        distanza += i.velocita*(i.durata/60.0);
    }
    return distanza;
}
double profiloVelocita::tempoTotale() const {
    double tempo = 0.0;
    /*for(int i=0; i<intervalli.size(); i++){
        tempo += intervalli[i].durata;
    }*/
    for(const auto& i : intervalli) {
        tempo += i.durata;
    }
    return tempo;
}
void profiloVelocita::profiloCasuale(double dist) {
    static  random_device rd;
    static  mt19937 gen(rd());
    const int V_MIN = 80;
    const int V_MAX = 190;
    const int T_MIN = 5;
    const int T_MAX = 15;
    uniform_int_distribution<int> distV(V_MIN, V_MAX);
    uniform_int_distribution<int> distT(T_MIN, T_MAX);
    double distanzaPercorsa = 0.0;
    while(distanzaPercorsa < dist){
        int v = distV(gen);
        int t = distV(gen);
        double dIntervallo = v*(t/60.0);
        this->aggiungiIntervallo(v, t);
        distanzaPercorsa += dIntervallo;
    }
}
profiloVelocita::~profiloVelocita() {
    intervalli.clear();
}