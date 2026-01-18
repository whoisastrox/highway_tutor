//Leonardo Stella
#include "../inc/TUTOR_H.h"

#include <sstream>

using namespace std;


int main(){
    Tutor tutor = Tutor();

    string latestInput = "";
    cout<<"tutor system is ready to accept input"<<endl;
    while(true){
        getline(cin, latestInput);
        
        stringstream ss = stringstream(latestInput);

        string command;
        ss>>command;
        cout<<"executed command is: "<<command<<endl;
        if(command == "set_time"){
            int quantity = 0;
            char flag = ' ';

            if(! (ss >> quantity)){
                cout<<"invalid time advance format, use either \"set_time <integer>\" or \"set_time <integer>m\" "<<endl;
                continue;
            }
            if(ss >> flag){
                if(flag == 'm'){
                    quantity *= 60;
                }
            }

            tutor.set_time(quantity);
            continue;
        }
        
        if(command == "reset"){
            tutor.reset();
            continue;
        }
        
        if(command == "stats"){
            tutor.stats();
            continue;
        }
        
        cout<<"either use set_time, reset or stats"<<endl;
    }

    return 0;
}

