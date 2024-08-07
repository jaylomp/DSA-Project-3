#include "HashTable.h"
#include "BTree.h"
#include <iostream>
#include <chrono>

void menu(BTree& tree, HashTable& table) {
    while (true) {
        cout << "\n*** Crime Data Search Menu ***\n";
        cout << "1. Search for felonies in a specific county\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore(); // To consume any leftover newline character

        if (choice == 1) {
            string countyToSearch;
            cout << "Enter the county name (Enter the name in lowercase followed by \"county\"): ";
            getline(cin, countyToSearch);
            // Check if county exists and has felonies
            auto start = chrono::high_resolution_clock::now();
            int tableFelonyCount = table.searchCount(countyToSearch);
            auto stop = chrono::high_resolution_clock::now();
            auto tableSearchTime = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            start = chrono::high_resolution_clock::now();
            int treeFelonyCount = tree.countFeloniesInCounty(countyToSearch);
            stop = chrono::high_resolution_clock::now();
            auto treeSearchTime = chrono::duration_cast<chrono::milliseconds>(stop - start);
            if (tableFelonyCount > 0 && treeFelonyCount > 0) {
                cout << "Number of felonies is: " << std::endl << "HashTable result: " <<
                    tableFelonyCount << " felonies" << std::endl << "BTree result: " << treeFelonyCount << " felonies" << std::endl <<
                        "HashTable search time: " << tableSearchTime.count() << " nanoseconds" << std::endl << "BTree search time: " <<
                            treeSearchTime.count() << " milliseconds" << std::endl;
            } else {
                cout << "County not found" << std::endl;
            }
            cout << "\nWould you like to search again? (y/n): ";
            char tryAgain;
            cin >> tryAgain;

            if (tryAgain == 'n' || tryAgain == 'N') {
                break;
            }

        } else if (choice == 2) {
            cout << "Exiting the program.\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

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
    std::cout << "HashTable insert time: " << tableInsertTime.count() << " milliseconds" << std::endl;
    BTree tree (32);
    start = chrono::high_resolution_clock::now();
    tree.buildFromDataset(records);
    stop = chrono::high_resolution_clock::now();
    auto treeInsertTime = chrono::duration_cast<chrono::milliseconds>(stop - start);
    std::cout << "BTree insert time: " << treeInsertTime.count() << " milliseconds" << std::endl;

    menu(tree, table);
    

    
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

    menu(tree);
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



