#include "CuckooHashingSlots.h"

int& CuckooHashingSlots::Value(int unit, int pos, int slot){
    return units[unit * unitsLen * slotsNum + pos * slotsNum + slot];
}

bool CuckooHashingSlots::findElementInSlots(int unit, int pos, int value) {
    for (int i = 0; i < slotsNum; i++) {
        if (Value(unit, pos, i) == value)
            return true;
    }
    return false;
}

bool CuckooHashingSlots::tryInsertInSlots(int unit, int pos, int value) {
    for(int i = 0; i < slotsNum; i++) {
        if (Value(unit, pos, i) == 0) {
            Value(unit, pos, i) = value;
            return true;
        }
    }
    return false;
}

bool CuckooHashingSlots::tryDeleteInSlots(int unit, int pos, int value) {
    for (int i = 0; i < slotsNum; i++) {
        if (Value(unit, pos, i) == value){
            Value(unit, pos, i) = 0;
            return true;
        }
    }
    return false;
}

int CuckooHashingSlots::seizeElementInSlots(int unit, int pos, int value) {
    // default seize the first position
    int v = Value(unit, pos, 0);
    Value(unit, pos, 0) = value;
    return v;
}

bool CuckooHashingSlots::InsertElement(int value) {
    int index1 = h.hash1(value) % unitsLen, index2 = h.hash2(value) % unitsLen;
    if(tryInsertInSlots(0, index1, value) || tryInsertInSlots(1, index2, value)){
        elements.insert(value);
        return true;
    }

    int cnt = 0, lastElement = value, index = index1;

    while(cnt < MAX_KICK){
        int kick = seizeElementInSlots(cnt % 2, index, lastElement);

        int nextPos = cnt % 2 ? (h.hash1(kick) % unitsLen) : (h.hash2(kick) % unitsLen);
        cnt++;
        if(tryInsertInSlots(cnt % 2, nextPos, kick)){
            elements.insert(value);
            return true;
        }
        lastElement = kick;
        index = nextPos;
    }
    return false;
}

bool CuckooHashingSlots::Insert(int value) {
    if(count() > cap()){
        std::cout << "Insert Failed because over capacity!" << std::endl;
        return false;
    }

    bool ok = InsertElement(value);
    if(ok)
        return true;
    else{
        int t = 0;
        while(t < MAX_REHASH){
            std::cout << "Try to rebuild for " << t+1 << " times..." << std::endl;
            h.rehash();
            if(rebuild(value)){
                std::cout << "Rebuild Successful!" << std::endl;
                elements.insert(value);
                return true;
            }
            t++;
        }
        std::cout << "Insert Failed because " << MAX_REHASH << " times of rebuild don't help!" << std::endl;
        return false;
    }
}

bool CuckooHashingSlots::Delete(int value) {
    int index1 = h.hash1(value) % unitsLen, index2 = h.hash2(value) % unitsLen;
    if(tryDeleteInSlots(0, index1, value)){
        elements.erase(value);
        return true;
    }

    if(tryDeleteInSlots(1, index2, value)){
        elements.erase(value);
        return true;
    }
    return false;
}

bool CuckooHashingSlots::Search(int value) {
    int index1 = h.hash1(value) % unitsLen, index2 = h.hash2(value) % unitsLen;
    return findElementInSlots(0, index1, value) || findElementInSlots(1, index2, value);
}

bool CuckooHashingSlots::rebuild(int value) {
    memset(units, 0, sizeof(int) * cap());
    crash++;

    for(int elem : elements)
        if(!InsertElement(elem)){
            std::cout << elem << " Crash!" << std::endl;
            return false;
        }
    return InsertElement(value);
}

int CuckooHashingSlots::count() const {
    return elements.size();
}

int CuckooHashingSlots::cap() const {
    return unitsNum * unitsLen * slotsNum;
}









