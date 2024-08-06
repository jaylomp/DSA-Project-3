#include "HashTable.h"
#include "BTree.h"
#include <iostream>

int main() {
    std::cout << "Hello world!" << std::endl;
    return 0;
}


/*vector<CrimeRecord> readCSV(const string& filename, int numRecords = -1) {
    ifstream file(filename);
    vector<CrimeRecord> dataset;
    string line;

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return dataset;
    }

    // Skip the header line
    getline(file, line);

    // Read each line of the CSV
    int recordCounter = 0;
    while (getline(file, line) && (numRecords == -1 || recordCounter < numRecords)) {
        stringstream ss(line);
        string cell;
        vector<string> row;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        // Assuming county is at index 1 and finalLevel is at index 27
        string county = row[1];
        string finalLevel = row[27];

        // Create a CrimeRecord object and add to the dataset
        // Using crimeID as a simple integer counter for demonstration
        static int crimeIDCounter = 1;
        CrimeRecord record(crimeIDCounter++, county, finalLevel);
        dataset.push_back(record);

        recordCounter++;
    }

    file.close();
    return dataset;
}*/
