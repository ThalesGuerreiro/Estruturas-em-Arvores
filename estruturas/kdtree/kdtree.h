#ifndef KDTREE_H
#define KDTREE_H

namespace kdtree{

const int k = 2;

struct KDNode{
    int point[k];
    KDNode *left, *right;
};

struct KDTree {
    KDNode* root;
};

KDNode* newKDNode(int arr[]);

KDNode* insertRec(KDNode* root, int point[], unsigned depth);

KDNode* insertNode(KDNode* root, int point[]);

bool arePointsSame(int point1[], int point2[]);

bool searchRec(KDNode* root, int point[], unsigned depth);

bool searchNode(KDNode* root, int point[]);

KDNode* minKDNode(KDNode* x, KDNode* y, KDNode* z, int d);

KDNode* findMinRec(KDNode* root, int d, unsigned depth);

KDNode* findMin(KDNode* root, int d);

void copyPoint(int p1[], int p2[]);

KDNode* deleteRecursive(KDNode* root, int point[], int depth);

KDNode* deleteNode(KDNode* root, int point[]);

void testSearch(KDNode* root, int point[]);

void insert(KDTree* tree, int point[]);

bool remove(KDTree* tree, int point[]);

bool search(KDTree* tree, int point[]);

void clearNode(KDNode* node);

void clear(KDTree* root);

}

#endif