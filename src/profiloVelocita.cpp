#include "../inc/PROFILO_VELOCITA_H.h"
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;

profiloVelocita::profiloVelocita() {}

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
profiloVelocita profiloVelocita::profiloCasuale(double dist) {
    profiloVelocita p;
    const int V_MIN = 80;
    const int V_MAX = 190;
    const int T_MIN = 5;
    const int T_MAX = 15;
    double distanzaPercorsa = 0.0;
    while(distanzaPercorsa < dist){
        int v = V_MIN+rand()%(V_MAX-V_MIN+1);
        int t = T_MIN+rand()%(T_MAX-T_MIN+1);
        double dIntervallo = v*(t/60.0);
        if (distanzaPercorsa + dIntervallo > dist) {
            t = static_cast<int>(ceil((dist - distanzaPercorsa)*60.0/v)); //tronco ultimo intervallo
        }
        p.aggiungiIntervallo(v, t);
        distanzaPercorsa += v*(t/60.0);
    }
    return p;
}
profiloVelocita::~profiloVelocita() {
    intervalli.clear();
}