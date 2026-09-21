#include <stdexcept>
#include <string>
#include <set>
#include <map>

using namespace std;

const set<string> BIN_TYPES{"standard", "dedicated", "cold_storage"};
const map<string, float> BIN_RATES = {{"standard", 1}, {"dedicated", 0.8}, {"cold_storage", 0.5}};
const string BIN_TYPE_ERR = "Error: Invalid bin type";
const string ID_ERR = "Error: A bin with this ID already exists"; 
const string CAP_ERR = "Error: Invalid capacity";
const string BAD_ID_ERR = "Error: Invlaid ID";
const char BIN_STR_CHR = 'B';

class Bin{
    public:
    Bin(string id_, string type_, int cap);

    private:
    string id;
    string type;
    int capacity;
};