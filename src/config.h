#ifndef CUCKOOHASHING_CONFIG_H
#define CUCKOOHASHING_CONFIG_H

#include <iostream>
#include <unordered_set>
#include <random>
#include <cstring>

const int TEST_COUNT = 1000000; // default test count
const int UNITS_LEN = 2500000; // default units length
const int SLOTS_NUM = 4; // default slots number
const int MAX_KICK = 200; // maximum kick times
const int MAX_REHASH = 100; // maximum rehash times

const int SEED = 1024; // default random seed
const int MIN_RANGE = 1; // minimum random range
const int MAX_RANGE = 20; // maximum random range

std::default_random_engine e(SEED);
std::uniform_int_distribution<int> u(MIN_RANGE, MAX_RANGE);

#endif
