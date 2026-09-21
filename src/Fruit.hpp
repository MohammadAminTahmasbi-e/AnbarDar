#include <string>
#include <set>
#include <stdexcept>

using namespace std;

const set<string> FRUIT_CATS = {"Regular", "Organic", "Greenhouse"};
const string CAT_ERR = "Error: Invalid product category";
const string PARAM_ERR = "Error: Invalid shipment parameters";
const int ORG_CRITICAL_POINT = 50;
const int ORG_PENALTY_RATE = 2;

class Fruit{
    public:
    Fruit(string cat, string name_, string shipmentId_, float freshness_, float decayRate_, int quantity_);
    virtual float calcFreshness(float binModifier) = 0;

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
    virtual float calcFreshness(float binModifier);
};

class OrganicFruit : public Fruit{
    public:
    virtual float calcFreshness(float binModifier);
};

class GreenhouseFruit : public Fruit{
    public:
    virtual float calcFreshness(float binModifier);
};