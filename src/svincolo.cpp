#include "SVINCOLO_H.h"
#include <string>
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
	return "<" + to_string(id) + ">" + "<" + to_string(dist) + ">";
}