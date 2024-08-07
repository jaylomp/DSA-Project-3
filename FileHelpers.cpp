#include "FileHelpers.h"

// Function to read a limited number of records from CSV
vector<CrimeRecord> readCSV(const string& filename, int numRecords) {
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

        // Remove potential leading/trailing spaces (optional)
        county.erase(0, county.find_first_not_of(' ')); // Left trim
        county.erase(county.find_last_not_of(' ') + 1); // Right trim
        finalLevel.erase(0, finalLevel.find_first_not_of(' ')); // Left trim
        finalLevel.erase(finalLevel.find_last_not_of(' ') + 1); // Right trim

        // cout<< county << " " << finalLevel << endl;

        static int crimeIDCounter = 1;
        CrimeRecord record(crimeIDCounter++, county, finalLevel);
        dataset.push_back(record);

        recordCounter++;
    }

    file.close();
    return dataset;
}

string normalizeString(const string& str) {
    string normalized = str;

    // Remove leading and trailing quotes
    if (!normalized.empty() && normalized.front() == '"') {
        normalized.erase(0, 1);
    }
    if (!normalized.empty() && normalized.back() == '"') {
        normalized.erase(normalized.size() - 1);
    }

    // Trim leading spaces
    normalized.erase(normalized.begin(), std::find_if(normalized.begin(), normalized.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    // Trim trailing spaces
    normalized.erase(std::find_if(normalized.rbegin(), normalized.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), normalized.end());

    // Convert to lowercase
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);

    return normalized;
}

// Update the functions to use normalizeString
string normalizeCountyName(const string& county) {
    return normalizeString(county);
}

string normalizeFinalLevel(const string& level) {
    return normalizeString(level);
}

