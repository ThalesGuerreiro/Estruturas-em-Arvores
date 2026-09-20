#ifndef TREAP_H
#define TREAP_H

namespace treap{

struct TreapNode{
    int key, priority;
    TreapNode *left, *right;
};

struct TreapTree {
    TreapNode* root;
};

TreapNode* rightRotate(TreapNode* y);

TreapNode* leftRotate(TreapNode* x);

TreapNode* newNode(int key);

TreapNode* searchRecursive(TreapNode* root, int key);

TreapNode* insertRecursive(TreapNode* root, int key);

TreapNode* deleteRecursive(TreapNode* root, int key);

void insert(TreapTree* tree, int key);

bool remove(TreapTree* tree, int key);

bool search(TreapTree* tree, int key);

void inorder(TreapNode* root);

void clear(TreapTree* tree);

}

#endif