#pragma once
#include <vector>
#include <list>
#include "CrimeRecord.h"
#include <functional>

class HashTable {
    int size;
    int numElements;
    double loadFactor;
    std::vector<std::list<CrimeRecord>> table;
    int hash(const std::string& location);
    void rehash();
public:
    HashTable(const int& s = 16, const double& load = 1.0);
    void insert(const CrimeRecord& record);
    CrimeRecord* search(const std::string& location);
};