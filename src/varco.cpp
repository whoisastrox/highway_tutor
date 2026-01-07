#include "VARCO_H.h"
int varco::countVarc = 0;
varco::varco(double d) {
	dist = d;
	id = countVarc++;
}
double varco::getDist()  const {
	return dist;
}
int varco::getId()  const {
	return id;
}
varco::~varco() {
	id = 0;
	dist = 0;
}