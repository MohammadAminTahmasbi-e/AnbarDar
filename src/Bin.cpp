#ifndef BIN_HPP
#define BIN_HPP

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
    if(type == "dedicated" && fruits.size()){
        if(delInfo.productCategory != (*fruits.begin())->getCategory()){
            throw invalid_argument(DED_TYP_ERR);
        } 
    }
    if(capacity - storedUnits < delInfo.quantity){
        throw invalid_argument(CAP_ERR);
    }

    fruits.push_back(make_shared<Fruit>(delInfo.productCategory, delInfo.productName, delInfo.shipmentId,
                                        delInfo.freshness, delInfo.decayRate, delInfo.quantity));
    storedUnits += delInfo.quantity;

    cout << "Success: Shipment " << delInfo.shipmentId << " stored in bin " << id << endl; 
}

bool Bin::isSuitableToPut(string category, int quantity){
    if(type == "dedicated" && fruits.size()){
        if(category != (*fruits.begin())->getCategory()){
            return false;
        } 
    }
    if(capacity - storedUnits < quantity){
        return false;
    }
    if(type == "standard" && category == "Organic"){
        return false;
    }
}

inline string Bin::getType(){
    return type;
}

#endif