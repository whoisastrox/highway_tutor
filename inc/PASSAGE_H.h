#ifndef PASSAGE_H
#define PASSAGE_H

#include "VARCO_H.h"
#include "DATATIME_H.h"
#include <string>


struct Passage {
    varco* gate;
    std::string plate;
    datatime moment;
};


#endif