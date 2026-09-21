#ifndef FRUIT_HPP
#define FRUIT_HPP

#include "Fruit.hpp"

Fruit::Fruit(string cat, string name_, string shipmentId_, float freshness_, float decayRate_ , int quantity_){
    if(FRUIT_CATS.find(cat) == FRUIT_CATS.end()){
        throw invalid_argument(CAT_ERR);
    }
    if(freshness_ < 1 || freshness_ > 100 || decayRate_ <= 0 || quantity <= 0){
        throw invalid_argument(PARAM_ERR);
    }

    name = name_;
    category = cat;
    freshness = freshness_;
    decayRate = decayRate_;
    quantity = quantity_;
}

float RegularFruit::calcFreshness(float binModifier){
    freshness = freshness - binModifier * decayRate;

    return freshness;
}

float OrganicFruit::calcFreshness(float binModifier){
    freshness -= (freshness > ORG_CRITICAL_POINT) ? decayRate * binModifier : decayRate * binModifier * ORG_PENALTY_RATE;

    return freshness;
}

float GreenhouseFruit::calcFreshness(float binModifier){
    freshness = freshness - decayRate;

    return freshness;
}


#endif