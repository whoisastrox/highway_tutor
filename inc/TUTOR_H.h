#ifndef TUTOR_H
#define TUTOR_H
#include "HIGHWAY_H.h"
#include "VARCO_H.h"
#include "VEHICLE_H.h"
#include "PASSAGE_H.h"
#include "TUTOR_VEHICLE_DATA.h"
#include <map>


class Tutor {
    public:
        void set_time(int forward_seconds);

        void reset();
        
        void stats();
    
        Tutor();
    private:
        Autostrada highway;
        map<string, TutorVehicleData> vehiclesData;

        vector<Passage> passages;
        vector<Passage>::iterator passagesIt;

        vector<int> varchiCount;
        vector<varco*>::iterator varchiIt;
        
        int sanctionedVehicles = 0;
        int currentMoment;
        int startingMoment;
        

        void load_passages_from_file();
};

#endif
