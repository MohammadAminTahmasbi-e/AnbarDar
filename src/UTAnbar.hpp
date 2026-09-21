#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <memory>
#include "Bin.hpp"

using namespace std;

typedef string id;
const char SPACE = ' ';
const string CMD_ADD_BIN = "create_bin";
const string REP_ID_ERR = "Error: A bin with this ID already exists ";

class UTAnbar{
    public:
    UTAnbar();
    void getCommands();
    void addBin(istringstream& line);

    private:
    map<id, Bin> bins;
};