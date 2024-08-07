// CrimeRecord.h
#pragma once
#include <string>
using namespace std;

class CrimeRecord {
public:
    int crimeID; // We'll keep this for unique identification
    string county;
    string finalLevel;
    int count;

    // Default constructor
    CrimeRecord() : crimeID(0), county("Unknown"), finalLevel("Unknown") {}

    // Parameterized constructor with all parameters
    CrimeRecord(int id, const string& cnty, const string& level)
        : crimeID(id), county(cnty), finalLevel(level) {}

    // Overload comparison operators for CrimeRecord
    bool operator<(const CrimeRecord& other) const {
        return crimeID < other.crimeID;
    }
    bool operator>(const CrimeRecord& other) const {
        return crimeID > other.crimeID;
    }
};




