#include "../inc/TUTOR_H.h"

#include <sstream>

using namespace std;


int main(){
    Tutor tutor = Tutor();

    string latestInput = "";
    cout<<"starting tutor system"<<endl;
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
                cout<<"broken"<<endl;
                continue;
            }
            cout<<quantity<<endl;
            if(ss >> flag){
                if(flag == 'm'){
                    quantity *= 60;
                }
            }

            cout<<quantity<<flag<<endl;
            tutor.set_time(quantity);
        }
        
        if(command == "reset"){
            tutor.reset();
        }
        
        if(command == "stats"){
            tutor.stats();
        }
        
    }

    return 0;
}

