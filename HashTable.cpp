#include "HashTable.h"

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

void HashTable::insert(CrimeRecord& record) {
    if (record.finalLevel != "felony") {
        return;
    }
    CrimeRecord* tempRecord = this->search(record.county);
    if (tempRecord != nullptr) {
        tempRecord->count++;
        return;
    }
    record.count = 1;
    int index = hash(record.county);
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
            int index = hash(j.county);
            table[index].push_back(j);
        }
    }
}

CrimeRecord* HashTable::search(const std::string &location) {
    int index = hash(location);
    // Traverses through list at index to find record
    for (auto &i : table[index]) {
        if (i.county == location) {
            return &i;

        }
    }
    return nullptr;
}

int HashTable::searchCount(const std::string &location) {
    CrimeRecord* temp = search(location);
    if (temp != nullptr) {
        return temp->count;
    }
    else {
        return 0;
    }
}

