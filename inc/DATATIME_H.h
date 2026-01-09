#ifndef DATATIME_H
#define DATATIME_H
#include <iostream>
using namespace std;
	
class datatime {
private:
	int giorno, mese, anno, ore, minuti;
	double secondi;
	enum GiorniMese {
		GEN = 31, FEB = 28, MAR = 31, APR = 30, MAG = 31, GIU = 30,
		LUG = 31, AGO = 31, SET = 30, OTT = 31, NOV = 30, DIC = 31
	};
	
public:
	datatime(int giorno,int mese,int anno,int ore,int minuti,double secondi);
	datatime();
	int getGiorno() const;
	int getMese() const;
	int getAnno() const;
	int getOre() const;
	int getMinuti() const;
	double getSecondi() const;
	void fillRandomData();
	void incrementaData(double s);
	bool checkBisestile(int anno) const;
	int giorniMese(int m) const;
};
ostream& operator<<(std::ostream& os, const datatime& d);
#endif
