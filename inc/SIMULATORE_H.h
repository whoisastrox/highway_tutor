#ifndef SIMULATORE_H
#define SIMULATORE_H
#include "HIGHWAY_H.h"
#include "DATATIME_H.h"
#include "VEHICLE_H.h"
static vehicle* creaVeicolo(Autostrada , datatime& d, string&);
static double randomTime();
static datatime impostaData(datatime&);

#endif
