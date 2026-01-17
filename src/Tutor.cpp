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
    currentMoment += forward_seconds;
    cout<<"setting_time"<<endl;
    cout<<static_cast<long>(passagesIt->moment.value())<<" - "<<currentMoment<<endl;
    cout<<"found plate - "<<vehiclesData.find(passagesIt->plate)->second.plate<<endl;
    cout<<"fine"<<endl;
    while(
        passagesIt != passages.end() && //checks that current and end are not the same
        passagesIt->moment < currentMoment //checks that current.moment is behind set moment
    ){
        cout<<"veicolo passato "<<passagesIt->plate<<endl;
        if(vehiclesData.find(passagesIt->plate) != vehiclesData.end()){
            //vehicle has already passed through a gate
            Passage *p1 = vehiclesData[(*passagesIt).plate].latest;
            // controlla se l'auto supera il limite, se necessario stampa la sanzione
            
            double distance = passagesIt->gate->getDist() - p1->gate->getDist();
            double interval = (passagesIt->moment - p1->moment)*3600;

            if(
                (distance / interval) > MAX_SPEED
            ){
                //print sanction
                printf("sanzione: %s - varchi %d a %d - velocità media: %.2fkm/h - instanti di passaggio %s - %s\n",
                    p1->plate.c_str(),
                    p1->gate->getId(), passagesIt->gate->getId(),
                    distance/interval,
                    p1->moment.toString().c_str(), passagesIt->moment.toString().c_str()
                );
                sanctionedVehicles++;
            }
            // aggiungi stats per varco, plate, velocità etc
            varchiCount[passagesIt->gate->getId()] += 1;
            
            
        }else{
            cout<<passagesIt->plate<<" inserting new vehicle data"<<endl;
            //vehicle is passing for the first time
            vehiclesData.insert({passagesIt->plate, {
                .plate = (*passagesIt).plate,
                .first = &(*passagesIt),
                .latest = &(*passagesIt)
            }});
        }
        // cambia ultimo passaggio con quello corrente
        
        passagesIt++;
    }
};

void Tutor::reset(){
    vehiclesData.clear();
    varchiCount.clear();
    while(varchiIt != highway.iterVarchiEnd()){
        varchiCount.push_back(0);
        varchiIt++;
    }
    varchiIt = highway.iterVarchi();
    sanctionedVehicles = 0;
    
    currentMoment = startingMoment;
};

void Tutor::stats(){
    for(int i = 0; i<varchiCount.size(); i++){
        printf("verco %d, numero di veicoli transitati: %d (%.2f veicoli/min)\n",
            i, varchiCount[i], static_cast<double>(varchiCount[i])/(currentMoment - startingMoment)*60
        );
    }
    auto dataIt = vehiclesData.begin();
    while(dataIt != vehiclesData.end()){
        
        if(dataIt->second.first == dataIt->second.latest){
            dataIt++;
            continue;
        }
        printf("veicolo %s, velocità media: %.2f\n",
            dataIt->second.plate.c_str(),
            (
                dataIt->second.latest->gate->getDist() - dataIt->second.first->gate->getDist()
            )/
            (
                (dataIt->second.latest->moment - dataIt->second.first->moment)*3600
            )
        );
        dataIt++;
    }
    printf("veicoli sanzionati: %d\n", sanctionedVehicles);
};

Tutor::Tutor(){
    highway = Autostrada();

    varchiIt = highway.iterVarchi();
    while(varchiIt != highway.iterVarchiEnd()){
        varchiCount.push_back(0);
        varchiIt++;
    }
    
    varchiIt = highway.iterVarchi();

    load_passages_from_file();
    
    passagesIt = passages.begin();
    currentMoment = static_cast<int>( floor(passages[0].moment.value()) );
    startingMoment = currentMoment;
};

void Tutor::load_passages_from_file(){
    varchiIt = highway.iterVarchi();
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
                ss >> ms; // This reads ".833" as a double
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
        varco *v = varchiIt[gateId];

        Passage p = {
            .gate = v, .plate = plate, .moment = d
        };
        passages.push_back(p);
        
    }
    cout<<"reading successfull"<<endl;
    cout<<"sorting"<<endl;
    sort(
        passages.begin(), passages.end(),
        [](const Passage p1, const Passage p2) { return &(p1.moment) < &(p2.moment); }
    );
    cout<<"sorting terminated"<<endl;
    return;
};