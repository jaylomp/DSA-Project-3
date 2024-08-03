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


void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(minDegree, true);
        root->keys.push_back(k);
    } else {
        if (root->keys.size() == 2 * minDegree - 1) {
            BTreeNode* s = new BTreeNode(minDegree, false);
            s->children.push_back(root);
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



void BTreeNode::insertNotFull(int k) {
    int i = keys.size() - 1;
    if (leaf) {
        keys.push_back(0);
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
    } else {
        while (i >= 0 && keys[i] > k) {
            i--;
        }
        i++;
        if (children[i]->keys.size() == 2 * minDegree - 1) {
            splitChild(i, children[i]);
            if (keys[i] < k) {
                i++;
            }
        }
        children[i]->insertNotFull(k);
    }
}


void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->minDegree, y->leaf);
    z->keys.resize(minDegree - 1);
    for (int j = 0; j < minDegree - 1; j++) {
        z->keys[j] = y->keys[j + minDegree];
    }
    if (!y->leaf) {
        z->children.resize(minDegree);
        for (int j = 0; j < minDegree; j++) {
            z->children[j] = y->children[j + minDegree];
        }
    }
    y->keys.resize(minDegree - 1);
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[minDegree - 1]);
    y->keys.pop_back();
}
