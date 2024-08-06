#include "HashTable.h"
#include "BTree.h"
#include <iostream>



int main() {
    std::vector<CrimeRecord> records = readCSV("FloridaConvictions_00000.csv", 10000000);
    HashTable table;
    // HashTable;
    for (auto& i : records) {
        i.county = normalizeCountyName(i.county);
        i.finalLevel = normalizeFinalLevel(i.finalLevel);
        table.insert(i);
        // tree.insert(i);
    }


    //BTree

    BTree tree(32); // minDegree
    tree.buildFromDataset(records);
    
    //string countyToSearch = "Pinellas County";
    //tree.timeCountFeloniesInCounty(countyToSearch);
    
    
}
