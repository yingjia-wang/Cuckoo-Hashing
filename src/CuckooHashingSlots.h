#ifndef CUCKOOHASHING_CUCKOOHASHINGSLOTS_H
#define CUCKOOHASHING_CUCKOOHASHINGSLOTS_H

#include "hash.h"

class CuckooHashingSlots {
private:
    int unitsNum, unitsLen, slotsNum;

    Hash h;

    std::unordered_set<int> elements;

    int* units;

    inline bool findElementInSlots(int unit, int pos, int value);

    inline bool tryInsertInSlots(int unit, int pos, int value);

    inline bool tryDeleteInSlots(int unit, int pos, int value);

    inline int seizeElementInSlots(int unit, int pos, int value);

    inline bool InsertElement(int value);

    inline int& Value(int unit, int pos, int slot);

public:
    int crash;

    CuckooHashingSlots(int len = UNITS_LEN, int num = SLOTS_NUM) : unitsNum(2), unitsLen(len), slotsNum(num), crash(0){
        units = new int[unitsNum * unitsLen * slotsNum];
    }

    ~CuckooHashingSlots(){
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
