#include "BTree.h"
#include <iostream>
#include <algorithm>

// Constructor for BTreeNode
BTreeNode::BTreeNode(int t, bool l) : minDegree(t), leaf(l), n(0) {
    keys.resize(2 * t - 1);
    children.resize(2 * t, nullptr);
}

// Traverse the subtree rooted at this node
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            children[i]->traverse();
        // cout << " " << keys[i].crimeID;
    }

    if (!leaf)
        children[i]->traverse();
}

// Insert a key into a non-full node
void BTreeNode::insertNotFull(const CrimeRecord& k) {
    int i = n - 1;

    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n = n + 1;
    } else {
        while (i >= 0 && keys[i] > k) {
            i--;
        }
        i++;
        if (children[i]->n == 2 * minDegree - 1) {
            splitChild(i, children[i]);
            if (keys[i] < k) {
                i++;
            }
        }
        children[i]->insertNotFull(k);
    }
}

// Split a full child node into two nodes
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->minDegree, y->leaf);
    z->n = minDegree - 1;

    // Copy the second half of y's keys to z
    for (int j = 0; j < minDegree - 1; j++) {
        z->keys[j] = y->keys[j + minDegree];
    }

    // Copy the second half of y's children to z if y is not a leaf
    if (!y->leaf) {
        for (int j = 0; j < minDegree; j++) {
            z->children[j] = y->children[j + minDegree];
            y->children[j + minDegree] = nullptr; // Clear the child pointer in y
        }
    }

    y->n = minDegree - 1;

    // Move children of this node to make space for z
    for (int j = n; j >= i + 1; j--) {
        children[j + 1] = children[j];
    }
    children[i + 1] = z;

    // Move keys of this node to make space for the middle key of y
    for (int j = n - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
    }
    keys[i] = y->keys[minDegree - 1];
    y->keys[minDegree - 1] = CrimeRecord(); // Clear the moved key

    n++;
}

// Insert a new key into the BTree
void BTree::insert(const CrimeRecord& k) {
    if (root == nullptr) {
        root = new BTreeNode(minDegree, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * minDegree - 1) {
            BTreeNode* s = new BTreeNode(minDegree, false);
            s->children[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k) {
                i++;
            }
            s->children[i]->insertNotFull(k);
            root = s;
        } else {
            root->insertNotFull(k);
        }
    }
}

// Search for a key in the subtree rooted at this node
BTreeNode* BTreeNode::search(int crimeID) {
    int i = 0;
    while (i < n && crimeID > keys[i].crimeID) {
        i++;
    }

    if (i < n && keys[i].crimeID == crimeID) {
        return this;
    }

    if (leaf) {
        return nullptr;
    }

    return children[i]->search(crimeID);
}

// Constructor for BTree
BTree::BTree(int t) : root(nullptr), minDegree(t) {}

// Traverse the BTree starting from the root
void BTree::traverse() {
    if (root != nullptr) root->traverse();
}

// Search for a key in the BTree
BTreeNode* BTree::search(int crimeID) {
    return (root == nullptr) ? nullptr : root->search(crimeID);
}

// Destructor for proper memory management
BTree::~BTree() {
    //std::cout << "Deleting BTree" << std::endl;
    delete root;
}

// Destructor for BTreeNode to deallocate memory
BTreeNode::~BTreeNode() {
    for (int i = 0; i < n; i++) {
        // std::cout << keys[i].crimeID << " ";
    }
    // std::cout << std::endl;

    // Delete child nodes
    for (auto& child : children) {
        if (child != nullptr) {
            delete child;
            child = nullptr;
        }
    }
}


// Function to build the BTree from a dataset
void BTree::buildFromDataset(const vector<CrimeRecord>& dataset) {
    for (const auto& record : dataset) {
        insert(record);
    }
}

int BTree::countFeloniesInCounty(const string& county) {
    if (root != nullptr) {
        return root->countFeloniesInCounty(county);
    } else {
        return 0; // If the tree is empty, return 0
    }
}



// Count felonies for a specific county in the subtree rooted at this node
int BTreeNode::countFeloniesInCounty(const string& county) {
    int count = 0;
    string normalizedCounty = normalizeString(county);

    for (int i = 0; i < n; i++) {
        string recordCounty = normalizeString(keys[i].county);
        string recordFinalLevel = normalizeString(keys[i].finalLevel);

        // Check if the normalized county contains the search string and if the final level is "felony"
        if (recordCounty.find(normalizedCounty) != string::npos && recordFinalLevel == "felony") {
            count++;
        }
    }

    // Recursively count felonies in child nodes
    if (!leaf) {
        for (int i = 0; i <= n; i++) {
            count += children[i]->countFeloniesInCounty(county);
        }
    }
    return count; // Return the total count
}






