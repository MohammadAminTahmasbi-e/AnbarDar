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
    cout << "Success: Storage bin " << id << " created successfully" << endl;
}

void UTAnbar::putInBin(DeliveryInfo delInfo){
    if(delInfo.deliveryType == DIR_DEL_TYP){
        bins[delInfo.binId].put(delInfo);
        return;
    }

    Bin* bin = findBin(delInfo.productCategory, delInfo.quantity, true);
    if(bin != NULL){
        bin->put(delInfo);
    }
    else{
        bin = findBin(delInfo.productCategory, delInfo.quantity, false);
        if(bin != NULL){
            bin->put(delInfo);
        }
        else{
            waitList.push_back(make_shared<Fruit>(delInfo.productCategory, delInfo.productName, delInfo.shipmentId,
                                            delInfo.freshness, delInfo.decayRate, delInfo.quantity));

            cout << "Success: Shipment " << delInfo.shipmentId << " added to waiting queue" << endl;
        }
    }
}

void UTAnbar::recieveShipment(istringstream& line){
    DeliveryInfo delInfo;

    line >> delInfo.shipmentId >> delInfo.deliveryType;
    if(delInfo.deliveryType == BUL_DEL_TYP){
        line >> delInfo.binId;

        if(bins.find(delInfo.binId) != bins.end()){
            throw invalid_argument("Error: Bin " + delInfo.binId + " does not exist");
        }
    }
    line >> delInfo.productName >> delInfo.productCategory 
         >> delInfo.quantity >> delInfo.freshness >> delInfo.decayRate;

    if(delInfo.deliveryType != BUL_DEL_TYP && delInfo.deliveryType != DIR_DEL_TYP){
        throw invalid_argument(PARAM_ERR);
    }
    if(shipmentIds.find(delInfo.shipmentId) == shipmentIds.end()){
        throw invalid_argument(REP_SHP_ID_ERR);
    }
    
    putInBin(delInfo);
}

Bin* UTAnbar::findBin(string category, int quantity, bool dedicatedOnly){
    auto id_bin = bins.begin();

    for(;id_bin != bins.end(); ++id_bin){
        if((id_bin->second.getType() == "dedicated" || !dedicatedOnly) && id_bin->second.isSuitableToPut(category, quantity)){
            return &id_bin->second;
        }
    }

    return NULL;
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