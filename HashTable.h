#pragma once
#include <vector>
#include <list>
#include "CrimeRecord.h"
#include <functional>

class HashTable {
    int size;
    int numElements;
    double loadFactor;
    // Chained hash table
    std::vector<std::list<CrimeRecord>> table;
    int hash(const std::string& location);
    void rehash();
public:
    // Default size is 16, default loadFactor is 1.0
    HashTable(const int& s = 16, const double& load = 1.0);
    void insert(CrimeRecord& record);
    CrimeRecord* search(const std::string& location);
    int searchCount(const std::string &location);
};


