#pragma once
#include <string>
using namespace std;

class CrimeRecord {
public:
    int crimeID;
    string crimeType;
    string location;
    string date;

    // Default constructor
    CrimeRecord() : crimeID(0), crimeType("Unknown"), location("Unknown"), date("Unknown") {}

    // Parameterized constructor
    CrimeRecord(int id, const string& type, const string& loc, const string& dt)
        : crimeID(id), crimeType(type), location(loc), date(dt) {}

    // Overload comparison operators for CrimeRecord
    bool operator<(const CrimeRecord& other) const {
        return crimeID < other.crimeID;
    }
    bool operator>(const CrimeRecord& other) const {
        return crimeID > other.crimeID;
    }
};
