#include "VARCO_H.h"
int varco::count = 0;
varco::varco(double d) {
	dist = d;
	id = count++;
}
double varco::getDist()  const {
	return dist;
}
int varco::getId()  const {
	return id;
}