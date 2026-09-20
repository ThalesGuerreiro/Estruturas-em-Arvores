#ifndef PATRICIA_H
#define PATRICIA_H

namespace patricia{

const int MAX_BITS = 31;

struct PatriciaNode{
    int key;
    int bit;

    PatriciaNode* left;
    PatriciaNode* right;
};

PatriciaNode* createHead();

bool getBit(int key, int bit);

int firstDifferentBit(int a, int b);

bool validKey(int key);

PatriciaNode* searchNode(PatriciaNode* head, int key);

bool search(PatriciaNode* head, int key);

void insert(PatriciaNode* head, int key);

bool remove(PatriciaNode* head, int key);

void freeTreeRecursive(PatriciaNode* Patricianode, int parentBit);

void clear(PatriciaNode* head);

}

#endif