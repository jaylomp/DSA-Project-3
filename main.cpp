#include "HashTable.h"
#include "BTree.h"
#include <iostream>

void menu(BTree& tree) {
    while (true) {
        cout << "\n*** Crime Data Search Menu ***\n";
        cout << "1. Search for felonies in a specific county\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string countyToSearch;
            cout << "Enter the county name (or part of it): ";
            cin.ignore(); // To consume any leftover newline character
            getline(cin, countyToSearch);

            // Check if county exists and has felonies
            int felonyCount = tree.countFeloniesInCounty(countyToSearch);
            if (felonyCount > 0) {
                cout << "The number of felonies in counties matching \"" << countyToSearch << "\" is: " << felonyCount << endl;
            } else {
                cout << "No felonies found for \"" << countyToSearch << "\" or the county does not exist in the dataset. Please try again.\n";
            }

            cout << "\nWould you like to try again? (y/n): ";
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



