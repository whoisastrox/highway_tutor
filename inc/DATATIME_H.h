//Alessandro Bonato
#ifndef DATATIME_H
#define DATATIME_H
#include <iostream>
#include <string>

using namespace std;
	
class datatime {
private:
	int giorno, mese, anno, ore, minuti;
	double secondi;
	enum GiorniMese {
		GEN = 31, FEB = 28, MAR = 31, APR = 30, MAG = 31, GIU = 30,
		LUG = 31, AGO = 31, SET = 30, OTT = 31, NOV = 30, DIC = 31
	};
	
	tm tm_struct() const;
	
public:
	datatime(int giorno,int mese,int anno,int ore,int minuti,double secondi);
	datatime(double secondi);
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
	~datatime();
	datatime(const datatime&);
	string toString() const;

	bool operator<(const datatime& d);
	bool operator>(const datatime& d);
	bool operator==(const datatime& d);
	
	bool operator<(const double& s);
	bool operator>(const double& s);
	bool operator==(const double& s);
	
	double operator+(const datatime& d);
	double operator-(const datatime& d);

	double operator+(const double& s);
	double operator-(const double& s);

	double value() const;

};
ostream& operator<<(std::ostream& os, const datatime& d);

#endif
