#include "HashTable.h"

#include <typeindex>

HashTable::HashTable(const int &s, const double &load) {
    size = s;
    loadFactor = load;
    numElements = 0;
    table.resize(size);
}

int HashTable::hash(const std::string& location) {
    return std::hash<std::string>{}(location) % size;
}

void HashTable::insert(const CrimeRecord& record) {
    int index = hash(record.location);
    table[index].push_back(record);
    numElements++;
    if (double(numElements) / double(size) >= loadFactor) {
        rehash();
    }
}

void HashTable::rehash() {
    std::vector<std::list<CrimeRecord>> oldTable = table;
    table.clear();
    size *= 2;
    table.resize(size);
    for (auto &i : oldTable) {
        for (auto &j : i) {
            int index = hash(j.location);
            table[index].push_back(j);
        }
    }
}

CrimeRecord* HashTable::search(const std::string &location) {
    int index = hash(location);
    for (auto &i : table[index]) {
        if (i.location == location) {
            return &i;
        }
    }
    return nullptr;
}