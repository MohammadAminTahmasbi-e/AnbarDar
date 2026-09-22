#include "Bin.hpp"

Bin::Bin(string id_, string type_, int cap){
    if(BIN_TYPES.find(type_) == BIN_TYPES.end()){
        throw invalid_argument(BIN_TYPE_ERR);
    }
    if(cap <= 0){
        throw invalid_argument(CAP_ERR);
    }
    if(id_[0] != BIN_STR_CHR){
        throw invalid_argument(BAD_ID_ERR);
    }
    
    id = id_;
    type = type_;
    capacity = cap;
    storedUnits = 0;
}

void Bin::put(DeliveryInfo delInfo){
    if(type == DED_BIN && fruits.size()){
        if(delInfo.productCategory != (*fruits.begin())->getCategory()){
            throw invalid_argument(DED_TYP_ERR);
        } 
    }
    if(capacity - storedUnits < delInfo.quantity){
        throw invalid_argument(BIN_CAP_ERR);
    }

    addFruit(delInfo);
    storedUnits += delInfo.quantity;

    cout << "Success: Shipment " << delInfo.shipmentId << " stored in bin " << id << endl; 
}

void Bin::addFruit(DeliveryInfo delInfo){
    if(delInfo.productCategory == REG_FRU_CAT){
        fruits.push_back(make_shared<RegularFruit>(delInfo));
    }
    else if(delInfo.productCategory == ORG_FRU_CAT){
        fruits.push_back(make_shared<OrganicFruit>(delInfo));
    }
    else{
        fruits.push_back(make_shared<GreenhouseFruit>(delInfo));
    }
}

bool Bin::isSuitableToPut(string category, int quantity){
    if(type == DED_BIN && fruits.size()){
        if(category != (*fruits.begin())->getCategory()){
            return false;
        } 
    }
    if(capacity - storedUnits < quantity){
        return false;
    }
    if(type == STD_BIN && category == ORG_FRU_CAT){
        return false;
    }

    return true;
}

void Bin::tick(float time){
    for(auto fruit = fruits.begin(); fruit != fruits.end(); ++fruit){
        (*fruit)->calcFreshness(BIN_RATES.at(type), time);
    }
}

void Bin::checkSpoilage(bool& spoiledFounded){
    auto fruit = fruits.begin();
    
    while(fruit != fruits.end()){
        if(!(*fruit)->getFreshness()){
            if(!spoiledFounded){
                spoiledFounded = true;

                cout << "Spoiled shipments removed:" << endl;
            }
            cout << "- Bin " << id << ": Shipment " << (*fruit)->getShipmentId() 
                 << " (" << (*fruit)->getName() << ", " << (*fruit)->getQuantity() << " units)" << endl;

            fruit = fruits.erase(fruit);
            continue;
        }
        ++fruit;
    }
}

void Bin::put(shared_ptr<Fruit> fruit){
    fruits.push_back(fruit);
}

string Bin::getType(){
    return type;
}
