#include "UTAnbar.hpp" 

void UTAnbar::addWaitList(DeliveryInfo delInfo){
    if(delInfo.productCategory == REG_FRU_CAT){
        waitList.push_back(make_shared<RegularFruit>(delInfo));
    }
    else if(delInfo.productCategory == ORG_FRU_CAT){
        waitList.push_back(make_shared<OrganicFruit>(delInfo));
    }
    else{
        waitList.push_back(make_shared<GreenhouseFruit>(delInfo));
    }
}

void UTAnbar::addBin(istringstream& line){
    string id, type;
    int cap;

    line >> id >> cap >> type;
    if(bins.find(id) != bins.end()){
        throw invalid_argument(REP_ID_ERR);
    }
    bins.insert({id, Bin(id, type, cap)});
    
    cout << "Success: Storage bin " << id << " created successfully" << endl;
}

void UTAnbar::putInBin(DeliveryInfo delInfo){
    if(delInfo.deliveryType == DIR_DEL_TYP){
        bins.at(delInfo.binId).put(delInfo);
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
            addWaitList(delInfo);

            cout << "Success: Shipment " << delInfo.shipmentId << " added to waiting queue" << endl;
        }
    }
}

void UTAnbar::recieveShipment(istringstream& line){
    DeliveryInfo delInfo;

    line >> delInfo.shipmentId >> delInfo.deliveryType;
    if(delInfo.deliveryType == DIR_DEL_TYP){
        line >> delInfo.binId;

        if(bins.find(delInfo.binId) == bins.end()){
            throw invalid_argument("Error: Bin " + delInfo.binId + " does not exist");
        }
    }
    line >> delInfo.productName >> delInfo.productCategory 
         >> delInfo.quantity >> delInfo.freshness >> delInfo.decayRate;

    if(delInfo.deliveryType != BUL_DEL_TYP && delInfo.deliveryType != DIR_DEL_TYP){
        throw invalid_argument(PARAM_ERR);
    }
    if(shipmentIds.find(delInfo.shipmentId) != shipmentIds.end()){
        throw invalid_argument(REP_SHP_ID_ERR);
    }
    
    putInBin(delInfo);
    shipmentIds.insert(delInfo.shipmentId);
}

Bin* UTAnbar::findBin(string category, int quantity, bool dedicatedOnly){
    for(auto id_bin = bins.begin();id_bin != bins.end(); ++id_bin){
        if((id_bin->second.getType() == DED_BIN || !dedicatedOnly) && id_bin->second.isSuitableToPut(category, quantity)){
            return &id_bin->second;
        }
    }

    return NULL;
}

void UTAnbar::tickWaitlist(float time){
    auto delivery = waitList.begin();

    while(delivery != waitList.end()){
        if(!(*delivery)->calcFreshness(WAIT_LIST_MODIFIER, time)){
            delivery = waitList.erase(delivery);
            continue;
        }
        ++delivery;
    }
}

void UTAnbar::tickBins(float time){
    for(auto id_bin = bins.begin(); id_bin != bins.end(); ++id_bin){
        id_bin->second.tick(time);
    }
}

void UTAnbar::tick(istringstream& line){
    float timeUnits;

    line >> timeUnits;
    if(timeUnits < 0){
        throw invalid_argument(INV_TIM_UNI);
    }

    tickWaitlist(timeUnits);
    tickBins(timeUnits);

    cout << "Success: Time advanced by " << timeUnits << " units " << endl;
}

bool UTAnbar::putIfPossible(shared_ptr<Fruit> fruit){
    Bin* bin = findBin(fruit->getCategory(), fruit->getQuantity(), true);

    if(bin != NULL){
        bin->put(fruit);
    }
    else{
        Bin* bin = findBin(fruit->getCategory(), fruit->getQuantity(), true);

        if(bin != NULL){
            bin->put(fruit);
        }
        else{
            return false;
        }
    }
    return true;
}

void UTAnbar::moveFromWaitlist(){
    auto delivery = waitList.begin();

    while(delivery != waitList.end()){
        if(!putIfPossible(*delivery)){
            delivery = waitList.erase(delivery);
            continue;
        }
        ++delivery;
    }
}

void UTAnbar::checkSpoilage(){
    bool isSpoiled = false;

    for(auto id_bin = bins.begin(); id_bin != bins.end(); ++id_bin){
        id_bin->second.checkSpoilage(isSpoiled);
    }
    if(!isSpoiled){
        cout << NO_SPOILED_OUT << endl;
        return;
    }
    moveFromWaitlist();
}

void UTAnbar::getCommands(){
    string line, cmd;

    while(getline(cin, line)){
        istringstream l(line);
        
        try{
            getline(l, cmd, SPACE);
            if(cmd == CMD_ADD_BIN){
                addBin(l);
            }
            else if(cmd == CMD_REC_SHP){
                recieveShipment(l);
            }
            else if(cmd == CMD_TIC){
                tick(l);
            }
            else if(cmd == CMD_CHK_SPO){
                checkSpoilage();
            }
        }
        catch(const invalid_argument& e){
            cout << e.what() << endl;
        }
    }
}
