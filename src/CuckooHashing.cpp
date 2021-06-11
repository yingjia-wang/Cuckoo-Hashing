#include "CuckooHashing.h"

int& CuckooHashing::Value(int unit, int pos){
    return units[unit * unitsLen + pos];
}

bool CuckooHashing::InsertElement(int value) {
    int index1 = h.hash1(value) % unitsLen, index2 = h.hash2(value) % unitsLen;
    if(Value(0, index1) == 0){
        Value(0, index1) = value;
        elements.insert(value);
        return true;
    }
    if(Value(1, index2) == 0){
        Value(1, index2) = value;
        elements.insert(value);
        return true;
    }

    int cnt = 0, lastElement = value, index = index1;

    while(cnt < MAX_KICK){
        int kick = Value(cnt % 2, index);
        Value(cnt % 2, index) = lastElement;

        int nextPos = cnt % 2 ? (h.hash1(kick) % unitsLen) : (h.hash2(kick) % unitsLen);
        cnt++;
        if(Value(cnt % 2, nextPos) == 0){
            Value(cnt % 2, nextPos) = kick;
            elements.insert(value);
            return true;
        }
        lastElement = kick;
        index = nextPos;
    }
    return false;
}

bool CuckooHashing::Insert(int value) {
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

bool CuckooHashing::Delete(int value) {
    int index1 = h.hash1(value) % unitsLen, index2 = h.hash2(value) % unitsLen;
    if(Value(0, index1) != value && Value(1, index2) != value)
        return false;
    else{
        if(Value(0, index1) == value)
            Value(0, index1) = 0;
        else
            Value(1, index2) = 0;
        elements.erase(value);
        return true;
    }
}

bool CuckooHashing::Search(int value) {
    int index1 = h.hash1(value) % unitsLen, index2 = h.hash2(value) % unitsLen;
    return Value(0, index1) == value || Value(1, index2) == value;
}

bool CuckooHashing::rebuild(int value) {
    memset(units, 0, sizeof(int) * cap());
    crash++;

    for(int elem : elements)
        if(!InsertElement(elem)){
            std::cout << elem << " Crash!" << std::endl;
            return false;
        }
    return InsertElement(value);
}

int CuckooHashing::count() const {
    return elements.size();
}

int CuckooHashing::cap() const {
    return unitsNum * unitsLen;
}
