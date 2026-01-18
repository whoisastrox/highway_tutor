//Leonardo Stella
#ifndef TUTOR_VEHICLE_DATA
#define TUTOR_VEHICLE_DATA

#include "PASSAGE_H.h"

struct TutorVehicleData {
    std::string plate;
    Passage *first;
    Passage *latest;
};


#endif