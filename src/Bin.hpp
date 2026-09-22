#ifndef BIN_HPP
#define BIN_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <set>
#include <map>
#include <list>
#include <memory>
#include "Fruit.hpp"

using namespace std;

const string DED_BIN = "dedicated";
const string STD_BIN = "standard";
const string COL_BIN = "cold_storage";
const set<string> BIN_TYPES{DED_BIN, STD_BIN, COL_BIN};
const map<string, float> BIN_RATES = {{STD_BIN, 1}, {DED_BIN, 0.8}, {COL_BIN, 0.5}};
const string BIN_TYPE_ERR = "Error: Invalid bin type";
const string ID_ERR = "Error: A bin with this ID already exists"; 
const string CAP_ERR = "Error: Invalid capacity";
const string BAD_ID_ERR = "Error: Invlaid ID";
const string DED_TYP_ERR = "Error: Incompatible product type for dedicated bin";
const string BIN_CAP_ERR = "Error: Bin capacity exceeded";
const char BIN_STR_CHR = 'B';

class Bin{
    public:
    Bin(string id_, string type_, int cap);
    void put(DeliveryInfo delInfo);
    void put(shared_ptr<Fruit> fruit);
    void addFruit(DeliveryInfo delInfo);
    bool isSuitableToPut(string category, int quantity);
    void checkSpoilage(bool& spoiledFounded);
    string getType();
    void tick(float time);
    private:
    string id;
    string type;
    int capacity;
    int storedUnits;
    list<shared_ptr<Fruit>> fruits;
};

#endif