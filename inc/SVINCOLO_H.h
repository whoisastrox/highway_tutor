//Alessandro Bonato
#ifndef SVINCOLO_H
#define SVINCOLO_H
#include <string>
using namespace std;
class svincolo {
private:
	static int countSvinc;
	int id;
	double dist;

public:
	svincolo();
	svincolo(double);
	double getDist() const;
	int getId() const;
	string toString() const;
	~svincolo();
	svincolo(const svincolo&);
};
ostream& operator<<(ostream& os, const svincolo& s);
#endif
