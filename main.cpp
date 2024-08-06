#include "HashTable.h"
#include "BTree.h"
#include <iostream>



int main() {
    std::vector<CrimeRecord> records = readCSV("FloridaConvictions_00000.csv", 10000000);
    HashTable table;
    // BTree tree;
    for (auto& i : records) {
        i.county = normalizeCountyName(i.county);
        i.finalLevel = normalizeFinalLevel(i.finalLevel);
        table.insert(i);
        // tree.insert(i);
    }
}
