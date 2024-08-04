#include "HashTable.h"

#include <typeindex>

HashTable::HashTable(const int &s, const double &load) {
    size = s;
    loadFactor = load;
    numElements = 0;
    table.resize(size);
}

int HashTable::hash(const std::string& location) {
    // Uses std library hash function % size to get index
    return std::hash<std::string>{}(location) % size;
}

void HashTable::insert(const CrimeRecord& record) {
    int index = hash(record.location);
    table[index].push_back(record);
    numElements++;
    // Check load factor
    if (double(numElements) / double(size) >= loadFactor) {
        rehash();
    }
}

void HashTable::rehash() {
    // Holds old hashed entries
    std::vector<std::list<CrimeRecord>> oldTable = table;
    table.clear();
    size *= 2;
    table.resize(size);
    // Traverses through old hashed entries and rehashes them
    for (auto &i : oldTable) {
        for (auto &j : i) {
            int index = hash(j.location);
            table[index].push_back(j);
        }
    }
}

CrimeRecord* HashTable::search(const std::string &location) {
    int index = hash(location);
    // Traverses through list at index to find record
    for (auto &i : table[index]) {
        if (i.location == location) {
            return &i;
        }
    }
    return nullptr;
}
