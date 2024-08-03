#pragma once
#include <iostream>
#include <vector>
using namespace std;

class BTreeNode {
public:
    bool leaf;
    vector<CrimeRecord> keys;
    vector<BTreeNode*> children;
    int minDegree;

    BTreeNode(int t, bool l);

    void insertNotFull(const CrimeRecord& k);

    void splitChild(int i, BTreeNode* y);

    void traverse();

    BTreeNode* search(int crimeID);

    friend class BTree;
};


class BTree {
public:
    BTreeNode* root;
    int minDegree;

    BTree(int t) : root(nullptr), minDegree(t) {}

    void traverse() { if (root != nullptr) root->traverse(); }

    BTreeNode* search(int crimeID) {
        return (root == nullptr) ? nullptr : root->search(crimeID);
    }

    void insert(const CrimeRecord& k);

    void buildFromDataset(const vector<CrimeRecord>& dataset);
};



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
