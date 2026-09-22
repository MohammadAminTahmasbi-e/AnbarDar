#ifndef FRUIT_HPP
#define FRUIT_HPP

#include <string>
#include <set>
#include <stdexcept>

using namespace std;

struct DeliveryInfo{
    string shipmentId; 
    string deliveryType;
    string binId;
    string productName;
    string productCategory;
    int quantity;
    float freshness; 
    float decayRate;
};
const string ORG_FRU_CAT = "organic";
const string REG_FRU_CAT = "regular";
const string GRE_FRU_CAT = "greenhouse"; 
const set<string> FRUIT_CATS = {REG_FRU_CAT, ORG_FRU_CAT, GRE_FRU_CAT};
const string CAT_ERR = "Error: Invalid product category";
const string PARAM_ERR = "Error: Invalid shipment parameters";
const int ORG_CRITICAL_POINT = 50;
const int ORG_PENALTY_RATE = 2;

class Fruit{
    public:
    Fruit(DeliveryInfo delInfo);
    string getCategory();
    float getFreshness();
    string getShipmentId();
    string getName();
    int getQuantity();
    virtual float calcFreshness(float binModifier, float advancedTime) = 0;

    protected:
    string category;
    string name;
    string shipmentId;
    float freshness;
    float decayRate;
    int quantity;
};

class RegularFruit : public Fruit{
    public:
    RegularFruit(DeliveryInfo delInfo);
    virtual float calcFreshness(float binModifier, float advancedTime);
};

class OrganicFruit : public Fruit{
    public:
    OrganicFruit(DeliveryInfo delInfo);
    virtual float calcFreshness(float binModifier, float advancedTime);
};

class GreenhouseFruit : public Fruit{
    public:
    GreenhouseFruit(DeliveryInfo delInfo);
    virtual float calcFreshness(float binModifier, float advancedTime);
};


#endif