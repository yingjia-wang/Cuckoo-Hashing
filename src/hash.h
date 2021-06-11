#ifndef CUCKOOHASHING_HASH_H
#define CUCKOOHASHING_HASH_H

#include "config.h"

class Hash {
private:
    int h1, h2, h3, h4;
public:
    Hash() : h1(u(e)), h2(u(e)), h3(u(e)), h4(u(e)){}

    void rehash() {
        h1 = u(e); h2 = u(e); h3 = u(e); h4 = u(e);
    }

    int hash1(int h) {
        h ^= (h << h1) ^ (h << h2);
        return (h ^ (h >> h3) ^ (h >> h4)) & 0x7fffffff;
        //return (h * h1 * h2 - h3 - h4) & 0x7fffffff;
    }

    int hash2(int h) {
        h ^= (h << h4) ^ (h << h3);
        return (h ^ (h >> h2) ^ (h >> h1)) & 0x7fffffff;
        //return (h * h3 * h4 - h1 - h2) & 0x7fffffff;
    }
};

#endif
