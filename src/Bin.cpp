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
}



#endif