#include "../inc/PROFILO_VELOCITA_H.h"
#include <cstdlib>
#include <cmath>
#include <vector>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
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
    double distanzaPercorsa = 0;
    random_device random;
    mt19937 m(random());
    uniform_int_distribution<int> velocita{ 80, 190 };
    uniform_int_distribution<int> tempo{ 5, 15 };
    while(distanzaPercorsa < dist){
        int v = velocita(m);
        int t = tempo(m);
        double dIntervallo = v*(t/60.0);
        this->aggiungiIntervallo(v, t);
        distanzaPercorsa += dIntervallo;
    }
}
profiloVelocita::~profiloVelocita() {
    intervalli.clear();
}
profiloVelocita::profiloVelocita(const profiloVelocita& p) {
    for (int i = 0; i < p.intervalli.size(); i++) {
        this->intervalli.push_back(p.intervalli[i]);
    }
}
    ostream& operator<<(ostream& os, const profiloVelocita& p) {
    //cout << p.getIntervalli().size();
    for (int i = 0; i < p.getIntervalli().size(); i++) {
        os << "<" << p.getIntervalli()[i].velocita << " " << p.getIntervalli()[i].durata << ">"<<" ";
    }
    return os;
}

double profiloVelocita::getIstantePassaggio(double spazio) {
    double tempo = 0;
    double d = 0;
    int i = 0;
    while (d < spazio && i<intervalli.size()) {
       // cout << intervalli[i].velocita<<"spazio:"<<spazio<<endl;
        double ds = (intervalli[i].durata/60.0)*intervalli[i].velocita;
        //cout << "ds:" << ds << endl;
        if (d + ds < spazio) {
            d += ds;
            tempo += (intervalli[i].durata*60.0); //in secondi
        }
        else {
            double last = spazio-d;
            //cout <<"last:"<< last<<"/vel:"<<intervalli[i].velocita<<endl;
            double durataLast = (last / intervalli[i].velocita)*3600;
            //cout <<"dur"<< durataLast<<endl;
            tempo += durataLast;
            d += last;
        }
        i++;
        //cout<<"tempo" << tempo << endl;
    }
    return tempo;
}
string profiloVelocita::toString() {
    string ret = "";
    for (int i = 0; i < intervalli.size(); i++) {
        ret=ret + "<" + to_string(intervalli[i].velocita) + " " + to_string(intervalli[i].durata) + ">" + ", ";
    }
    return ret;
}
