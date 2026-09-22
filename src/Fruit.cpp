#include "Fruit.hpp"

Fruit::Fruit(DeliveryInfo delInfo){
    if(FRUIT_CATS.find(delInfo.productCategory) == FRUIT_CATS.end()){
        throw invalid_argument(CAT_ERR);
    }
    if(delInfo.freshness < 1 || delInfo.freshness > 100 || delInfo.decayRate <= 0 || delInfo.quantity <= 0){
        throw invalid_argument(PARAM_ERR);
    }

    name = delInfo.productName;
    category = delInfo.productCategory;
    shipmentId = delInfo.shipmentId;
    freshness = delInfo.freshness;
    decayRate = delInfo.decayRate;
    quantity = delInfo.quantity;
}

string Fruit::getCategory(){
    return category;
}

RegularFruit::RegularFruit(DeliveryInfo delInfo) : Fruit(delInfo){}

float RegularFruit::calcFreshness(float binModifier, float advancedTime){
    freshness = freshness - binModifier * decayRate * advancedTime;
    if(freshness < 0){
        freshness = 0;
    }
    return freshness;
}

OrganicFruit::OrganicFruit(DeliveryInfo delInfo) : Fruit(delInfo){}

float OrganicFruit::calcFreshness(float binModifier, float advancedTime){
    freshness -= (freshness > ORG_CRITICAL_POINT) ? decayRate * binModifier * advancedTime
                                                  : decayRate * binModifier * advancedTime * ORG_PENALTY_RATE;
    if(freshness < 0){
        freshness = 0;
    }
    return freshness;
}

GreenhouseFruit::GreenhouseFruit(DeliveryInfo delInfo) : Fruit(delInfo){}

float GreenhouseFruit::calcFreshness(float binModifier, float advancedTime){
    freshness = freshness - decayRate * advancedTime;
    if(freshness < 0){
        freshness = 0;
    }
    return freshness;
}
