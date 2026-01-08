#ifndef PROFILO_VELOCITA_H
#define PROFILO_VELOCITA_H
#include <vector>
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
    
    private:
        vector<intervallo> intervalli;
};
#endif