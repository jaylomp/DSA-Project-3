#pragma once
#include <iostream>
#include <vector>
using namespace std;

class BTreeNode {
    public:
        bool leaf;
        vector<int> keys;
        vector<BTreeNode*> children;
        int minDegree;

        BTreeNode(int t, bool l);

        void insertNotfull(int k);

        void splitChild(int x, BTreeNode* y);

        void traverse();

        BTreeNode* search(int key);

        friend class BTree;



};



class BTree {
public:
    BTreeNode* root;
    int minDegree;

    BTree(int t) {root = nullptr, minDegree = t;}

    void traverse() {if (root != nullptr) root->traverse();}

    BTreeNode* search(int key) {
        return (root == nullptr) ? nullptr : root->search(key);
    }

    void insert (int k);

};
