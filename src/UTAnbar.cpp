#ifndef UTANBAR_HPP
#define UTANBAR_HPP

#include "UTAnbar.hpp" 

void UTAnbar::addBin(istringstream& line){
    string id, type;
    int cap;

    line >> id >> cap >> type;
    if(bins.find(id) != bins.end()){
        throw invalid_argument(REP_ID_ERR);
    }

    Bin bin(id, type, cap);
    bins[id] = bin;
}

void UTAnbar::recieveShipment(istringstream& line){

}

void UTAnbar::getCommands(){
    string line, cmd;

    while(getline(cin, line)){
        istringstream l(line);
        
        getline(l, cmd, SPACE);
        if(cmd == CMD_ADD_BIN){
            addBin(l);
        }
        else if(cmd == CMD_REC_SHP){
            recieveShipment(l);
        }
    }
}
#endif