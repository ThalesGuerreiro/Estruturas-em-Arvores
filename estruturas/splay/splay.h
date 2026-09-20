#ifndef SPLAY_H
#define SPLAY_H

namespace splay{

struct SplayNode{
    int key;
    SplayNode *left, *right;
};

struct SplayTree{
    SplayNode* root;
};

SplayNode* newSplayNode(int key);

SplayNode* rightRotate(SplayNode* x);

SplayNode* leftRotate(SplayNode* x);

SplayNode* splay(SplayNode* root, int key);

SplayNode* insertNode(SplayNode* root, int key);

SplayNode* removeNode(SplayNode* root, int key);

void insert(SplayTree* tree, int key);

bool remove(SplayTree* tree, int key);

bool search(SplayTree* tree, int key);

void clear(SplayTree* root);

}

#endif