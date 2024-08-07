#include "HashTable.h"
#include "BTree.h"
#include <iostream>



int main() {
    std::vector<CrimeRecord> records = readCSV("FloridaConvictions_00000.csv", 10000000);
    HashTable table;
    auto start = chrono::high_resolution_clock::now();
    for (auto& i : records) {
        i.county = normalizeCountyName(i.county);
        i.finalLevel = normalizeFinalLevel(i.finalLevel);
        table.insert(i);
    }
    auto stop = chrono::high_resolution_clock::now();
    auto tableInsertTime = chrono::duration_cast<chrono::milliseconds>(stop - start);
    // std::cout << "Table insert: " << tableInsertTime.count() << " milliseconds" << std::endl;

    /*
    start = chrono::high_resolution_clock::now();
    int felonyCount = table.searchCount("pinellas county"); // How to get felonyCount from HashTable
    stop = chrono::high_resolution_clock::now();
    auto tableSearchTime = chrono::duration_cast<chrono::microseconds>(stop - start);
    std::cout << "Pinellas County count: " << felonyCount << " felonies" << std::endl;
    std::cout << "Table search: " << tableSearchTime.count() << " microseconds" << std::endl;
    */

    //BTree

    /*
    BTree tree(32); // minDegree
    start = chrono::high_resolution_clock::now();
    tree.buildFromDataset(records);
    stop = chrono::high_resolution_clock::now();
    auto treeInsertTime = chrono::duration_cast<chrono::milliseconds>(stop - start);
    std::cout << "Tree insert: " << treeInsertTime.count() << " milliseconds" << std::endl;
    start = chrono::high_resolution_clock::now();
    std::cout << tree.countFeloniesInCounty("Pinellas County");  // How to get felonyCount from BTree
    stop = chrono::high_resolution_clock::now();
    auto treeSearchTime = chrono::duration_cast<chrono::milliseconds>(stop - start);
    */
}
