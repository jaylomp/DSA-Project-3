#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <sstream>
#include "CrimeRecord.h"
#include "FileHelpers.h"

using namespace std;

class BTreeNode {
public:
    bool leaf;
    vector<CrimeRecord> keys;
    vector<BTreeNode*> children;
    int n;
    int minDegree;

    BTreeNode(int t, bool l);
    ~BTreeNode();

    void insertNotFull(const CrimeRecord& k);
    void splitChild(int i, BTreeNode* y);
    void traverse();
    BTreeNode* search(int crimeID);

    // New function to count felonies in a specific county
    int countFeloniesInCounty(const string& county);

    friend class BTree;
};

class BTree {
public:
    BTreeNode* root;
    int minDegree;

    BTree(int t);
    ~BTree();

    void traverse();
    BTreeNode* search(int crimeID);
    void insert(const CrimeRecord& k);
    void buildFromDataset(const vector<CrimeRecord>& dataset);
    vector<CrimeRecord> readCSV(const string& filename, int numRecords = -1);

    // New function to count felonies in a specific county
    int countFeloniesInCounty(const string& county);

    double timeCountFeloniesInCounty(const string& county) {
        auto start = std::chrono::high_resolution_clock::now();
        int felonyCount = root->countFeloniesInCounty(county);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time taken to count felonies in " << county << ": " << elapsed.count() << " seconds" << std::endl;

        return elapsed.count();
    }
};
