#ifndef UTANBAR_HPP
#define UTANBAR_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <memory>
#include <list>
#include "Bin.hpp"
#include "Fruit.hpp"

using namespace std;

typedef string id;
const char SPACE = ' ';
const float WAIT_LIST_MODIFIER = 2;
const string CMD_ADD_BIN = "create_bin";
const string CMD_REC_SHP = "receive_shipment";
const string CMD_TIC = "tick";
const string CMD_CHK_SPO = "check_spoilage";
const string REP_ID_ERR = "Error: A bin with this ID already exists ";
const string REP_SHP_ID_ERR = "Error: A shipment with this ID already exists";
const string INV_TIM_UNI = "Error: Invalid time units ";
const string NO_SPOILED_OUT = "No spoiled product found.";
const string BUL_DEL_TYP = "BULK";
const string DIR_DEL_TYP = "DIRECT";

struct BinIdComparator {
    bool operator()(const std::string& a, const std::string& b) const {
        int numA = std::stoi(a.substr(1));
        int numB = std::stoi(b.substr(1));

        return numA < numB;
    }
};


class UTAnbar{
    public:
    void getCommands();

    private:
    map<id, Bin, BinIdComparator> bins;
    set<string> shipmentIds;
    list<shared_ptr<Fruit>> waitList;
    void addWaitList(DeliveryInfo delInfo);
    void addBin(istringstream& line);
    void recieveShipment(istringstream& line);
    void putInBin(DeliveryInfo delInfo);
    bool putIfPossible(shared_ptr<Fruit> fruit);
    Bin* findBin(string category, int quantity, bool dedicatedOnly);
    void tick(istringstream& line);
    void tickWaitlist(float time);
    void tickBins(float time);
    void moveFromWaitlist();
    void checkSpoilage();
};

#endif