//Giovanni Genzini
#ifndef PROFILO_VELOCITA_H
#define PROFILO_VELOCITA_H
#include <vector>
#include <iostream>
#include <string>
using namespace std;
class profiloVelocita {    
    public:
        struct intervallo{
            int velocita;
            int durata;
        };

        profiloVelocita();
        void aggiungiIntervallo(int velocita, int durata);
        const vector<intervallo>& getIntervalli() const;
        double distanzaPercorsa() const;
        double tempoTotale() const;
        void profiloCasuale(double dist); //crea profilo causale che copre distanza che gli passo 
	    ~profiloVelocita();
        profiloVelocita(const profiloVelocita&);
        double getIstantePassaggio(double);
        string toString();
    
    private:
        vector<intervallo> intervalli;
};

ostream& operator<<(ostream& os, const profiloVelocita& p);
#endif