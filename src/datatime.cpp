#include "DATATIME_H.h"
#include <stdexcept>
#include <iostream>
using namespace std;

datatime::datatime() {
	giorno = 1;
	mese = 1;
	anno = 1970;
	ore = 0;
	minuti = 0;
	secondi = 0;
}

datatime::datatime(int giorno, int mese, int anno, int ore, int minuti, int secondi) {
    if (mese < 1 || mese > 12) { //controllo se il mese è valido
        throw std::invalid_argument("Mese non valido");
    }
    if (giorno < 1 || giorno > giorniMese(mese)) { //controllo giorni
        throw std::invalid_argument("Giorno non valido");
    }
    if (ore < 0 || ore > 23) throw std::invalid_argument("Ora non valide");
    if (minuti < 0 || minuti > 59) throw std::invalid_argument("Minuti non validi");
    if (secondi < 0 || secondi > 59.59) throw std::invalid_argument("Secondi non validi");
    this->giorno = giorno;
    this->mese = mese;
    this->anno = anno;
    this->ore = ore;
    this->minuti = minuti;
    this->secondi = secondi;
}

int datatime::giorniMese(int m) const {
    switch (m) {
    case 1:  return GEN; 
    case 2:  return FEB; 
    case 3:  return MAR;
    case 4:  return APR; 
    case 5:  return MAG; 
    case 6:  return GIU;
    case 7:  return LUG; 
    case 8:  return AGO; 
    case 9:  return SET;
    case 10: return OTT; 
    case 11: return NOV; 
    case 12: return DIC;
    default: return 0;
    }
}
void datatime::fillRandomData() {
    srand(time(NULL));
    anno = 1970 + rand() % (57);
    mese = rand() % 13;
    giorno = rand() % (giorniMese(mese) + 1);
    ore = rand() % 24;
    minuti = rand() % 60;
}
ostream& operator<<(ostream& os, const datatime& d) {
    os << d.getGiorno() << "/"
        << d.getMese() << "/"
        << d.getAnno() << " "
        << d.getOre() << ":"
        << d.getMinuti() << ":"
        << d.getSecondi();
    return os;
}
int datatime::getGiorno() const { return giorno; }
int datatime::getMese() const { return mese; }
int datatime::getAnno() const { return anno; }
int datatime::getOre() const { return ore; }
int datatime::getMinuti() const { return minuti; }
double datatime::getSecondi() const { return secondi; }