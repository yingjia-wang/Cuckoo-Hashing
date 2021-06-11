#ifndef CUCKOOHASHING_CUCKOOHASHING_H
#define CUCKOOHASHING_CUCKOOHASHING_H

#include "hash.h"

class CuckooHashing{
private:
    int unitsNum, unitsLen;

    Hash h;

    std::unordered_set<int> elements;

    int* units;

    inline bool InsertElement(int value);

    inline int& Value(int unit, int pos);

public:
    int crash;

    CuckooHashing(int len = UNITS_LEN) : unitsNum(2), unitsLen(len), crash(0){
        units = new int[unitsNum * unitsLen];
    }
    ~CuckooHashing(){
        delete units;
    }
    bool Insert(int value);

    bool Delete(int value);

    bool Search(int value);

    bool rebuild(int value);

    int count() const;

    int cap() const;
};

#endif
