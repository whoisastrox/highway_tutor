#include "../inc/DATATIME_H.h"
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

datatime::datatime() {
	giorno = 1;
	mese = 1;
	anno = 1970;
	ore = 0;
	minuti = 0;
	secondi = 0;
}

datatime::datatime(const double d){
    long s = static_cast<long>(d); // seconds elapsed since epoch

    double unused;
    double ms = modf(d, &unused);
    
    tm *time = localtime(&s);

    secondi = static_cast<double>(time->tm_sec) + ms;
    minuti = time->tm_min;
    ore = time->tm_hour;
    giorno = time->tm_mday;
    mese = time->tm_mon+1;
    anno = time->tm_year+1900;
}

datatime::datatime(int giorno, int mese, int anno, int ore, int minuti, double secondi) {
    if (mese < 1 || mese > 12) { //controllo se il mese � valido
        throw std::invalid_argument("Mese non valido");
    }
    if (giorno < 1 || giorno > giorniMese(mese)) { //controllo giorni
        throw std::invalid_argument("Giorno non valido");
    }
    if (ore < 0 || ore > 23) throw std::invalid_argument("Ora non valide");
    if (minuti < 0 || minuti > 59) throw std::invalid_argument("Minuti non validi");
    if (secondi < 0 || secondi >= 60) throw std::invalid_argument("Secondi non validi");
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
    case 2:  return checkBisestile(anno) ? 29 : FEB; //febbraio diventa di 29 giorni se bisestile
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
    secondi = rand() % 60;     
}
void datatime::incrementaData(double s){
    if(s<0){ 
        throw std::invalid_argument("Valore non valido");
    }
    secondi += s; //sommo secondi che ho gia + secondi che gli passo
    if(secondi>=60.0){
        minuti += static_cast<int>(secondi/60);
        secondi=fmod(secondi,60.0); //fa stessa operazione di % ma per i numeri reali, quindi torna resto divisione tra numeri reali
    }
    if(minuti>=60){
        ore += minuti/60;
        minuti = minuti%60;
    }
    if(ore>=24){
        giorno += ore/24;
        ore = ore%24;
    }
    while(giorno>giorniMese(mese)) {
        giorno -= giorniMese(mese);
        mese++;
        if (mese>12) {
            mese = 1;
            anno++;
        }
    }
}
bool datatime::checkBisestile(int anno) const { //bisestile se divisibile per 4 ma non per 100, o se divisibile per 400
    return (anno%4 == 0 && anno%100 != 0) || (anno%400 == 0);
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
datatime::~datatime() {
    giorno = 0;
    anno = 0;
    mese = 0;
    ore = 0;
    minuti = 0;
    secondi = 0;
}
datatime::datatime(const datatime& d) {
    giorno = d.giorno;
    mese = d.mese;
    anno = d.anno;
    ore = d.ore;
    minuti = d.minuti;
    secondi = d.secondi;
}
string datatime::toString() const {
    /*
    secondi = floor(secondi * 1000) / 1000;//tronco a 3 decimali
    stringstream stream;
    stream << std::fixed <<setprecision(3) << secondi;
    std::string sec = stream.str();
    
    //return to_string(giorno) + "/"+ to_string(mese) + "/"+ to_string(anno) + " "+ to_string(ore) + ":"+ to_string(minuti) + ":" + sec;
    */
    char buff[24];
    snprintf(buff, 24, "%02d/%02d/%04d %02d:%02d:%06.3f",
        getGiorno(), getMese(), getAnno(),
        getOre(), getMinuti(), getSecondi()
    );
    return string(buff);
}

/* returns seconds elapsed since epoch */
double datatime::value() const {
    tm t = tm_struct();
    time_t s = mktime(&t);
    double unused = 0;
    return static_cast<double>(s) + modf(getSecondi(), &unused);        
}

tm datatime::tm_struct() const {
    time_t now = time(nullptr);

    tm time = {};
    time.tm_sec = getSecondi();
    time.tm_min = getMinuti();
    time.tm_hour = getOre();
    time.tm_mday = getGiorno();
    time.tm_mon = getMese()-1;
    time.tm_year = getAnno()-1900;

    return time;
}

bool datatime::operator<(const datatime&d){
    return value() < d.value();
};

bool datatime::operator>(const datatime&d){
    return value() > d.value();
};

bool datatime::operator==(const datatime&d){
    return value() == d.value();
};

bool datatime::operator<(const double& s){
    return value() < s;
};

bool datatime::operator>(const double& s){
    return value() > s;
};

bool datatime::operator==(const double& s){
    return value() == s;
};

double datatime::operator+(const datatime& d){
    return value() + d.value();
}
double datatime::operator-(const datatime& d){
    return value() - d.value();
}

double datatime::operator+(const double& s){
    return value() + s;
}
double datatime::operator-(const double& s){
    return value() - s;
}
