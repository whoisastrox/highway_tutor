//Giovanni Genzini
#include <iostream>
#ifndef VARCO_H
#define VARCO_H
using namespace std;
class varco {
private:
	static int countVarc;
	int id;
	double dist;

public:
	varco(double);
	double getDist() const;
	int getId() const;
	~varco();
	varco(const varco&);

};
ostream& operator<<(ostream& os, const varco& v);
#endif

