#include <bits/stdc++.h>
#include "kdtree.h"
using namespace std;
namespace kdtree{

KDNode* newKDNode(int arr[]) {
    KDNode* temp = new KDNode;

    for (int i = 0; i < k; i++)
        temp->point[i] = arr[i];

    temp->left = temp->right = nullptr;

    return temp;
}

KDNode* insertRec(KDNode *root, int point[], unsigned depth){
    if (root == NULL)
       return newKDNode(point);

    unsigned cd = depth % k;

    if (point[cd] < (root->point[cd]))
        root->left  = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);

    return root;
}

KDNode* insertNode(KDNode *root, int point[]){
    return insertRec(root, point, 0);
}

bool arePointsSame(int point1[], int point2[]){
    for (int i = 0; i < k; ++i)
        if (point1[i] != point2[i])
            return false;

    return true;
}

bool searchRec(KDNode* root, int point[], unsigned depth){
    if (root == NULL)
        return false;
    if (arePointsSame(root->point, point))
        return true;

    unsigned cd = depth % k;

    if (point[cd] < root->point[cd])
        return searchRec(root->left, point, depth + 1);

    return searchRec(root->right, point, depth + 1);
}

bool searchNode(KDNode* root, int point[]){
    return searchRec(root, point, 0);
}

KDNode *minKDNode(KDNode *x, KDNode *y, KDNode *z, int d){
    KDNode *res = x;
    if (y != NULL && y->point[d] < res->point[d])
       res = y;
    if (z != NULL && z->point[d] < res->point[d])
       res = z;
    return res;
}

KDNode *findMinRec(KDNode* root, int d, unsigned depth){
    if (root == NULL)
        return NULL;

    unsigned cd = depth % k;

    if (cd == d)
    {
        if (root->left == NULL)
            return root;
        return findMinRec(root->left, d, depth+1);
    }

    return minKDNode(root, findMinRec(root->left, d, depth+1), findMinRec(root->right, d, depth+1), d);
}

KDNode *findMin(KDNode* root, int d){
    return findMinRec(root, d, 0);
}

void copyPoint(int p1[], int p2[]){
   for (int i=0; i<k; i++)
       p1[i] = p2[i];
}

KDNode *deleteRecursive(KDNode *root, int point[], int depth){
    if (root == NULL)
        return NULL;

    int cd = depth % k;

    if (arePointsSame(root->point, point)){
        if (root->right != NULL){
            KDNode *min = findMin(root->right, cd);
            copyPoint(root->point, min->point);
            root->right = deleteRecursive(root->right, min->point, depth+1);
        }

        else if (root->left != NULL){
            KDNode *min = findMin(root->left, cd);
            copyPoint(root->point, min->point);
            root->left = deleteRecursive(root->left, min->point, depth+1);
        }

        else{
            delete root;
            return NULL;
        }

        return root;
    }

    if (point[cd] < root->point[cd])
        root->left = deleteRecursive(root->left, point, depth+1);
    else
        root->right = deleteRecursive(root->right, point, depth+1);

    return root;
}

 KDNode* deleteNode(KDNode *root, int point[]){
   return deleteRecursive(root, point, 0);
}

void testSearch(KDNode* root, int point[]){
    cout << "(" << point[0] << ", " << point[1] << ") -> ";

    if (searchNode(root, point))
        cout << "encontrado";
    else
        cout << "nao encontrado";

    cout << endl;
}



void insert(KDTree* tree, int point[]){
    tree->root = insertNode(tree->root, point);
}

bool remove(KDTree* tree, int point[]){
    if (!searchNode(tree->root, point))
        return false;

    tree->root = deleteNode(tree->root, point);

    return true;
}

bool search(KDTree* tree, int point[]){
    return searchNode(tree->root, point);
}

void clearNode(KDNode* node) {
    if (node == nullptr)
        return;

    clearNode(node->left);
    clearNode(node->right);

    delete node;
}

void clear(KDTree* tree) {
    if (tree == nullptr)
        return;

    clearNode(tree->root);
    tree->root = nullptr;
}

}

/* testes antigos pra ver se tava tudo certo
int main(){

    KDNode* root = NULL;

    // ==========================================
    // 1. INSERÇÃO
    // ==========================================

    int points[][2] = {
        {30, 40},
        {5, 25},
        {10, 12},
        {70, 70},
        {50, 30},
        {35, 45},
        {20, 10}
    };

    int n = sizeof(points) / sizeof(points[0]);

    cout << "=== INSERCAO ===" << endl;

    for (int i = 0; i < n; i++) {
        root = insert(root, points[i]);

        cout << "Inserido: ("
             << points[i][0] << ", "
             << points[i][1] << ")" << endl;
    }

    // ==========================================
    // 2. BUSCA
    // ==========================================

    cout << "\n=== BUSCA ===" << endl;

    int p1[] = {30, 40};
    int p2[] = {35, 45};
    int p3[] = {100, 100};
    int p4[] = {10, 10};

    testSearch(root, p1);
    testSearch(root, p2);
    testSearch(root, p3);
    testSearch(root, p4);


    // ==========================================
    // 3. DUPLICATA
    // ==========================================

    cout << "\n=== DUPLICATA ===" << endl;

    int duplicate[] = {30, 40};

    root = insert(root, duplicate);

    cout << "Inserindo novamente (30, 40)." << endl;

    cout << "Busca: ";
    testSearch(root, duplicate);


    // ==========================================
    // 4. FIND MIN
    // ==========================================

    cout << "\n=== FIND MIN ===" << endl;

    KDNode* minX = findMin(root, 0);
    KDNode* minY = findMin(root, 1);

    if (minX != NULL) {
        cout << "Menor X: ("
             << minX->point[0] << ", "
             << minX->point[1] << ")" << endl;
    }

    if (minY != NULL) {
        cout << "Menor Y: ("
             << minY->point[0] << ", "
             << minY->point[1] << ")" << endl;
    }


    // ==========================================
    // 5. REMOÇÃO
    // ==========================================

    cout << "\n=== REMOCAO ===" << endl;

    int remove1[] = {20, 10};

    cout << "Removendo (20, 10)..." << endl;
    root = deleteKDNode(root, remove1);

    testSearch(root, remove1);


    // ==========================================
    // 6. REMOÇÃO DE OUTRO PONTO
    // ==========================================

    int remove2[] = {5, 25};

    cout << "\nRemovendo (5, 25)..." << endl;
    root = deleteKDNode(root, remove2);

    testSearch(root, remove2);


    // ==========================================
    // 7. REMOÇÃO DE PONTO INEXISTENTE
    // ==========================================

    int remove3[] = {100, 100};

    cout << "\nTentando remover (100, 100)..." << endl;
    root = deleteKDNode(root, remove3);

    testSearch(root, remove3);


    // ==========================================
    // 8. ARVORE FINAL
    // ==========================================

    //cout << "\n=== ARVORE FINAL ===" << endl;
    //printTree(root);


    // ==========================================
    // 9. BUSCAS FINAIS
    // ==========================================

    cout << "\n=== BUSCAS FINAIS ===" << endl;

    int final1[] = {30, 40};
    int final2[] = {50, 30};
    int final3[] = {35, 45};
    int final4[] = {5, 25};
    int final5[] = {20, 10};

    testSearch(root, final1);
    testSearch(root, final2);
    testSearch(root, final3);
    testSearch(root, final4);
    testSearch(root, final5);

    return 0;
}
*/