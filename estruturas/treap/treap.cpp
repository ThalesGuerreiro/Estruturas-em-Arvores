#include <bits/stdc++.h>
#include "treap.h"
using namespace std;

namespace treap{

TreapNode *rightRotate(TreapNode *y){
    TreapNode *x = y->left,  *T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

TreapNode *leftRotate(TreapNode *x){
    TreapNode *y = x->right, *T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

TreapNode* newNode(int key){
    TreapNode* temp = new TreapNode;
    temp->key = key;
    temp->priority = rand()%100;
    temp->left = temp->right = NULL;
    return temp;
}

TreapNode* searchRecursive(TreapNode* root, int key){
    if (root == NULL || root->key == key)
       return root;

    if (root->key < key)
       return searchRecursive(root->right, key);

    return searchRecursive(root->left, key);
}

TreapNode* insertRecursive(TreapNode* root, int key){
    if (!root)
        return newNode(key);

    if (key == root->key)
        return root;

    if (key <= root->key){
        root->left = insertRecursive(root->left, key);

        if (root->left->priority > root->priority)
            root = rightRotate(root);
    }

    else{
        root->right = insertRecursive(root->right, key);

        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }

    return root;
}

TreapNode* deleteRecursive(TreapNode* root, int key){
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteRecursive(root->left, key);
    else if (key > root->key)
        root->right = deleteRecursive(root->right, key);


    else if (root->left == NULL){
        TreapNode *temp = root->right;
        delete(root);
        root = temp;
    }

    else if (root->right == NULL){
        TreapNode *temp = root->left;
        delete(root);
        root = temp;
    }

    else if (root->left->priority < root->right->priority){
        root = leftRotate(root);
        root->left = deleteRecursive(root->left, key);
    }
    else{
        root = rightRotate(root);
        root->right = deleteRecursive(root->right, key);
    }

    return root;
}

void insert(TreapTree* tree, int key){
    tree->root = insertRecursive(tree->root, key);
}

bool remove(TreapTree* tree, int key){
    if (searchRecursive(tree->root, key) == NULL)
        return false;

    tree->root = deleteRecursive(tree->root, key);

    return true;
}

bool search(TreapTree* tree, int key){
    return searchRecursive(tree->root, key) != NULL;
}

//Printa arvore
void inorder(TreapNode* root)
{
    if (root)
    {
        inorder(root->left);
        cout << "key: "<< root->key << " | priority: "
            << root->priority;
        if (root->left)
            cout << " | left child: " << root->left->key;
        if (root->right)
            cout << " | right child: " << root->right->key;
        cout << endl;
        inorder(root->right);
    }
}

void clearNode(TreapNode* node) {
    if (node == nullptr)
        return;

    clearNode(node->left);
    clearNode(node->right);

    delete node;
}

void clear(TreapTree* tree) {
    if (tree == nullptr)
        return;

    clearNode(tree->root);
    tree->root = nullptr;
}


}

/* testes anteriores pra vir se tava tudo certo

int main() {
    TreapNode* root = NULL;

    // ========================================
    // TESTE DE INSERCAO
    // ========================================

    cout << "=== TESTE DE INSERCAO ===" << endl;

    int valores[] = {50, 30, 70, 20, 40, 60, 80};

    int tamanho = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < tamanho; i++) {
        root = insert(root, valores[i]);
    }

    cout << "Elementos inseridos: ";

    for (int i = 0; i < tamanho; i++) {
        cout << valores[i] << " ";
    }

    cout << endl;

    cout << "\nArvore em ordem:" << endl;
    inorder(root);


    // ========================================
    // TESTE DE BUSCA
    // ========================================

    cout << "\n=== TESTE DE BUSCA ===" << endl;

    int buscas[] = {20, 40, 80, 50, 100};

    for (int i = 0; i < 5; i++) {
        int chave = buscas[i];

        TreapNode* resultado = search(root, chave);

        cout << chave << " -> ";

        if (resultado != NULL)
            cout << "1";
        else
            cout << "0";

        cout << endl;
    }


    // ========================================
    // TESTE DE DUPLICATA
    // ========================================

    cout << "\n=== TESTE DE DUPLICATA ===" << endl;

    cout << "Antes de inserir 40 novamente:" << endl;
    inorder(root);

    root = insert(root, 40);

    cout << "\nDepois de inserir 40 novamente:" << endl;
    inorder(root);


    // ========================================
    // TESTE DE REMOCAO
    // ========================================

    cout << "\n=== TESTE DE REMOCAO ===" << endl;

    int remocoes[] = {20, 70, 50};

    for (int i = 0; i < 3; i++) {
        int chave = remocoes[i];

        cout << "\nRemovendo " << chave << "..." << endl;

        root = deleteRecursive(root, chave);

        cout << "Arvore apos remocao:" << endl;
        inorder(root);

        TreapNode* resultado = search(root, chave);

        cout << "Busca por " << chave << ": ";

        if (resultado != NULL)
            cout << "1 (ERRO)";
        else
            cout << "0";

        cout << endl;
    }


    // ========================================
    // TESTE DE REMOCAO INEXISTENTE
    // ========================================

    cout << "\n=== TESTE DE REMOCAO INEXISTENTE ===" << endl;

    cout << "Antes:" << endl;
    inorder(root);

    cout << "\nTentando remover 999..." << endl;

    root = deleteRecursive(root, 999);

    cout << "\nDepois:" << endl;
    inorder(root);


    // ========================================
    // TESTE FINAL DE BUSCA
    // ========================================

    cout << "\n=== TESTE FINAL DE BUSCA ===" << endl;

    int buscasFinais[] = {30, 40, 60, 80, 20, 50, 70, 999};

    for (int i = 0; i < 8; i++) {
        int chave = buscasFinais[i];

        TreapNode* resultado = search(root, chave);

        cout << chave << " -> ";

        if (resultado != NULL)
            cout << "1";
        else
            cout << "0";

        cout << endl;
    }


    // ========================================
    // ESTADO FINAL
    // ========================================

    cout << "\n=== ESTADO FINAL ===" << endl;

    if (root != NULL) {
        cout << "Arvore em ordem:" << endl;
        inorder(root);
    }
    else {
        cout << "Arvore vazia." << endl;
    }

    return 0;
}
*/