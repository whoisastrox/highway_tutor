//Alessandro Bonato
#include "../inc/SVINCOLO_H.h"
#include <string>
#include <iostream>
using namespace std;
int svincolo::countSvinc = 0;
svincolo::svincolo(double d) {
	dist = d;
	id = countSvinc++;
}
double svincolo::getDist() const {
	return dist;
}
int svincolo::getId() const {
	return id;
}
/*string svincolo::toString() const {
	cout << id << endl;
	return "<" + to_string(id) + ">" + "<" + to_string(dist) + ">";
}*/
svincolo::svincolo(const svincolo& s) {
	dist = s.dist;
	id = s.id;
}
svincolo::~svincolo() {
	id = 0;
	dist = 0;
}
ostream& operator<<(ostream& os, const svincolo& s) {
	os << "id: " << s.getId() << " dist: " << s.getDist();
	return os;
}
svincolo::svincolo() {
	id = 0;
	dist = 0;
}