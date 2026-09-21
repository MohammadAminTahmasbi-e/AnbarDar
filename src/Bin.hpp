#include <iostream>
#include <stdexcept>
#include <string>
#include <set>
#include <map>
#include <list>
#include <memory>
#include "Fruit.hpp"

using namespace std;

const set<string> BIN_TYPES{"standard", "dedicated", "cold_storage"};
const map<string, float> BIN_RATES = {{"standard", 1}, {"dedicated", 0.8}, {"cold_storage", 0.5}};
const string BIN_TYPE_ERR = "Error: Invalid bin type";
const string ID_ERR = "Error: A bin with this ID already exists"; 
const string CAP_ERR = "Error: Invalid capacity";
const string BAD_ID_ERR = "Error: Invlaid ID";
const string DED_TYP_ERR = "Error: Incompatible product type for dedicated bin";
const string CAP_ERR = "Error: Bin capacity exceeded";
const char BIN_STR_CHR = 'B';

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

class Bin{
    public:
    Bin(string id_, string type_, int cap);
    void put(DeliveryInfo delInfo);
    bool isSuitableToPut(string category, int quantity);
    inline string getType();
    private:
    string id;
    string type;
    int capacity;
    int storedUnits;
    list<shared_ptr<Fruit>> fruits;
};