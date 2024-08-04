#pragma once
#include <string>
using namespace std;


// this is just a place holder we need to discuss what we want in the nodes
struct CrimeRecord {
    int crimeID;
    string type;
    string date;
    string location;

    // Comparison operators for BTree ordering by crimeID
    bool operator<(const CrimeRecord& other) const {
        return crimeID < other.crimeID;
    }

    bool operator>(const CrimeRecord& other) const {
        return crimeID > other.crimeID;
    }

    bool operator==(const CrimeRecord& other) const {
        return crimeID == other.crimeID;
    }
};