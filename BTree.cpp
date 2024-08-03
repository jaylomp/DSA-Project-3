#include "BTree.h"


BTreeNode::BTreeNode(int t, bool l) {
    minDegree = t;
    leaf = l;
}

void BTreeNode::traverse() {
    int i;
    for (int i = 0; i < keys.size(); i++) {
        if (!leaf) {
            children[i]->traverse();
        }
    }

    if (!leaf) {
        children[i]->traverse();
    }
}

BTreeNode* BTreeNode::search(int key) {
    int i = 0;

    while (i < keys.size() && k > keys[i]) {
        i++;
    }

    if (i < keys.size() && keys[i] == k) {
        return this;
    }

    if (leaf) {
        return nullptr;
    }

    return children[i]->search(key);
} 

