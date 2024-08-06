#pragma once
#include <iostream>
#include <vector>
#include "CrimeRecord.h"

using namespace std;

class BTreeNode {
public:
    bool leaf;
    vector<CrimeRecord> keys;
    vector<BTreeNode*> children;
    int n; // Number of keys currently stored
    int minDegree;

    // Constructor for BTreeNode
    BTreeNode(int t, bool l);

    // Destructor for BTreeNode to deallocate memory
    ~BTreeNode();

    // Insert a key into a non-full node
    void insertNotFull(const CrimeRecord& k);

    // Split a full child node into two nodes
    void splitChild(int i, BTreeNode* y);

    // Traverse the subtree rooted at this node
    void traverse();

    // Search for a key in the subtree rooted at this node
    BTreeNode* search(int crimeID);

    friend class BTree;
};

class BTree {
public:
    BTreeNode* root;
    int minDegree;

    // Constructor for BTree
    BTree(int t);

    // Destructor for BTree to deallocate memory
    ~BTree();

    // Traverse the BTree starting from the root
    void traverse();

    // Search for a key in the BTree
    BTreeNode* search(int crimeID);

    // Insert a new key into the BTree
    void insert(const CrimeRecord& k);

    // Build BTree from a dataset (declared but not defined)
    void buildFromDataset(const vector<CrimeRecord>& dataset);
};
