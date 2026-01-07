#include "SVINCOLO_H.h"
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
string svincolo::toString() const {
	cout << id << endl;
	return "<" + to_string(id) + ">" + "<" + to_string(dist) + ">";
}
svincolo::~svincolo() {
	id = 0;
	dist = 0;
}