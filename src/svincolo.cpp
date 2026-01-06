#include "SVINCOLO_H.h"
int svincolo::count = 0;
svincolo::svincolo(double d) {
	dist = d;
	id = count++;
}
double svincolo::getDist() const {
	return dist;
}
int svincolo::getId() const {
	return id;
}