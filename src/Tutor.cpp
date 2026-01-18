#include "../inc/FILE_ERROR_H.h"
#include "../inc/TUTOR_H.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cmath>
#include <iomanip>

const int MAX_SPEED = 130;

void Tutor::set_time(int forward_seconds){
    cout<<"setting time - adding "<<forward_seconds<<" seconds"<<endl;

    currentMoment += forward_seconds;    
    
    while(
        passagesIt != passages.end() && //checks that current and end are not the same
        passagesIt->moment.value() < currentMoment //checks that current.moment is behind set moment
    ){
        
        cout<<"veicolo passato "<<passagesIt->plate;
        
        auto vd = vehiclesData.find(passagesIt->plate);

        if(vd != vehiclesData.end()){
            cout<<"- vd trovato";
        }else{
            cout<<"- vd non trovato";
        }

        if(vd != vehiclesData.end()){
            //vehicle has already passed through a gate
            // controlla se l'auto supera il limite, se necessario stampa la sanzione
            cout<<" - computing speed ... ";
            Passage *p1 = vd->second.latest;
            
            double speed = computeSpeed(p1, &(*passagesIt));

            printf(" %.3fkm/s", speed);
            if(
                (speed) > MAX_SPEED
            ){
                //print sanction
                printf("\nsanzione: %s - tratta <%d - %d> - velocità media: %.2fkm/h - instanti di passaggio %s - %s",
                    p1->plate.c_str(),
                    p1->gate->getId(), passagesIt->gate->getId(),
                    speed,
                    p1->moment.toString().c_str(), passagesIt->moment.toString().c_str()
                );
                sanctionedVehicles++;
            }
            
            // aggiungi stats per varco, plate, velocità etc
            varchiCount[passagesIt->gate->getId()] += 1;
            vd->second.latest = &(*passagesIt);
            
        }else{
            //vehicle is passing for the first time
            vehiclesData.insert({passagesIt->plate, {
                .plate = (*passagesIt).plate,
                .first = &(*passagesIt),
                .latest = &(*passagesIt)
            }});
        }
        // cambia ultimo passaggio con quello corrente
        
        passagesIt++;
        cout<<endl;
    }
};

void Tutor::reset(){
    vehiclesData.clear();
    
    passagesIt = passages.begin();

    varchiCount.clear();

    auto vIt = highway->iterVarchi();
    while(vIt != highway->iterVarchiEnd()){
        varchiCount.push_back(0);
        vIt++;
    }

    sanctionedVehicles = 0;
    
    currentMoment = startingMoment;
};

void Tutor::stats(){
    cout<<"///STATISTICHE PER VARCO"<<endl;
    for(int i = 0; i<varchiCount.size(); i++){
        printf("verco %d, numero di veicoli transitati: %d (%.2f veicoli/min)\n",
            i, varchiCount[i], static_cast<double>(varchiCount[i])/(currentMoment - startingMoment)*60
        );
    }
    cout<<endl;
    
    cout<<"///STATISTICHE PER VEICOLO"<<endl;
    auto dataIt = vehiclesData.begin();
    while(dataIt != vehiclesData.end()){
        printf("veicolo %s, velocità media: ",
            dataIt->second.plate.c_str()
        );
        if(dataIt->second.first == dataIt->second.latest){
            cout<<"non calcolabile (troppi pochi varchi)"<<endl;
        }else{
            printf("%.2fkm/h\n",
                computeSpeed(dataIt->second.first, dataIt->second.latest)
            );
        }
        
        dataIt++;
    }
    cout<<endl;

    printf("///TOTALE VEICOLI SANZIONATI: %d\n", sanctionedVehicles);
};

Tutor::Tutor(){
    highway = new Autostrada();

    auto vIt = highway->iterVarchi();

    while(vIt != highway->iterVarchiEnd()){
        varchiCount.push_back(0);
        vIt++;
    }

    load_passages_from_file();

    passagesIt = passages.begin();
    currentMoment = static_cast<int>( floor(passages[0].moment.value()) );
    startingMoment = currentMoment;
};

void Tutor::load_passages_from_file(){
    auto vIt = highway->iterVarchi();
    ifstream fileInput("./Data/Passages.txt");
    string riga;	
    while (std::getline(fileInput, riga)) {
        if(riga.empty()) continue;
        stringstream ss(riga);
        char unused;
        if(riga.length()<1) break;

        int gateId;
        string plate;
        tm moment;
        
        if (!(ss >> unused >> gateId >> unused)) {
            throw file_error(0);
        }
        ss >> ws >> unused;
        
        getline(ss, plate, '>'); 

        ss >> ws >> unused;

        ss >> get_time(&moment, "%d/%m/%Y %H:%M:%S");
        
        double ms = 0;
        if (ss.fail()) {
           throw file_error(0);
        } else {
            if (ss.peek() == '.') {
                ss >> ms;
            }
        }
        
        datatime d = datatime(
            moment.tm_mday,
            moment.tm_mon+1,
            moment.tm_year+1900,
            moment.tm_hour,
            moment.tm_min,
            static_cast<double>(moment.tm_sec) + ms
        );
        varco *v = vIt[gateId];

        Passage p = {
            .gate = v, .plate = plate, .moment = d
        };
        passages.push_back(p);
        
    }
    sort(
        passages.begin(), passages.end(),
        [](const Passage p1, const Passage p2) { return p1.moment.value() < p2.moment.value(); }
    );
    return;
};
/*
@return
double - the average speed, in km/h, between the two passages 

p1 represents the earliest passage, p2 the latest
*/
double Tutor::computeSpeed(Passage *p1, Passage *p2){
    return (
        p2->gate->getDist() - p1->gate->getDist()
    ) / (
        p2->moment.value() - p1->moment.value()
    ) * 3600;
};