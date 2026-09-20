#include <iostream>
#include "splay.h"
using namespace std;
namespace splay{

SplayNode* newSplayNode(int key){
    SplayNode* Splaynode = new SplayNode();
    Splaynode->key = key;
    Splaynode->left = Splaynode->right = nullptr;
    return Splaynode;
}

SplayNode* rightRotate(SplayNode* x){
    SplayNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayNode* leftRotate(SplayNode* x){
    SplayNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayNode* splay(SplayNode* root, int key){
    if (root == nullptr || root->key == key)
        return root;

    SplayNode header;
    header.left = nullptr;
    header.right = nullptr;

    SplayNode* leftTree = &header;
    SplayNode* rightTree = &header;

    while (true){

        if (key < root->key){

            if (root->left == nullptr)
                break;

            if (key < root->left->key){
                root = rightRotate(root);

                if (root->left == nullptr)
                    break;
            }

            rightTree->left = root;
            rightTree = root;
            root = root->left;

        }
        else if (key > root->key){

            if (root->right == nullptr)
                break;

            if (key > root->right->key){
                root = leftRotate(root);

                if (root->right == nullptr)
                    break;
            }

            leftTree->right = root;
            leftTree = root;
            root = root->right;

        }
        else{
            break;
        }
    }

    leftTree->right = root->left;
    rightTree->left = root->right;

    root->left = header.right;
    root->right = header.left;

    return root;
}

SplayNode* insertNode(SplayNode* root, int key){
    if (root == nullptr)
        return newSplayNode(key);

    root = splay(root, key);

    if (root->key == key)
        return root;

    SplayNode* newNode = newSplayNode(key);
    if (root->key > key){
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    }
    else{
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }
    return newNode;
}

void preOrder(SplayNode* Splaynode){
    if (Splaynode != nullptr){
        cout << Splaynode->key << " ";
        preOrder(Splaynode->left);
        preOrder(Splaynode->right);
    }
}

SplayNode* removeNode(SplayNode* root, int key){
    if (root == nullptr)
        return nullptr;

    root = splay(root, key);

    if (root->key != key)
        return root;

    if (root->left == nullptr){
        SplayNode* temp = root->right;
        delete root;
        return temp;
    }

    if (root->right == nullptr){
        SplayNode* temp = root->left;
        delete root;
        return temp;
    }

    SplayNode* leftSubtree = root->left;
    SplayNode* rightSubtree = root->right;
    delete root;

    leftSubtree = splay(leftSubtree, key);
    leftSubtree->right = rightSubtree;
    return leftSubtree;
}

void insert(SplayTree* tree, int key){
    tree->root = insertNode(tree->root, key);
}

bool remove(SplayTree* tree, int key){
    if (!search(tree, key))
        return false;

    tree->root = removeNode(tree->root, key);

    return true;
}

bool search(SplayTree* tree, int key){
    if (tree->root == nullptr)
        return false;

    tree->root = splay(tree->root, key);

    return tree->root->key == key;
}

void clearNode(SplayNode* node) {
    if (node == nullptr)
        return;

    clearNode(node->left);
    clearNode(node->right);

    delete node;
}

void clear(SplayTree* tree) {
    if (tree == nullptr)
        return;

    clearNode(tree->root);
    tree->root = nullptr;
}


}

/* testes antigos pra ver seatava tudo em ordem

int main(){
    SplayNode* root = nullptr;

    // ========================================
    // TESTE DE INSERCAO
    // ========================================

    cout << "=== TESTE DE INSERCAO ===" << endl;

    int valores[] ={50, 30, 70, 20, 40, 60, 80};

    int tamanho = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < tamanho; i++){
        root = insert(root, valores[i]);
    }

    cout << "Elementos inseridos: ";
    for (int i = 0; i < tamanho; i++){
        cout << valores[i] << " ";
    }
    cout << endl;

    cout << "Preorder: ";
    preOrder(root);
    cout << endl;

    cout << "Raiz: " << root->key << endl;


    // ========================================
    // TESTE DE BUSCA
    // ========================================

    cout << "\n=== TESTE DE BUSCA ===" << endl;

    int buscas[] ={20, 40, 80, 50, 100};

    for (int i = 0; i < 5; i++){
        int chave = buscas[i];

        root = splay(root, chave);

        cout << chave << " -> ";

        if (root != nullptr && root->key == chave){
            cout << "1";
        }
        else{
            cout << "0";
        }

        if (root != nullptr){
            cout << " | raiz apos busca: " << root->key;
        }

        cout << endl;
    }


    // ========================================
    // TESTE DE INSERCAO DUPLICADA
    // ========================================

    cout << "\n=== TESTE DE DUPLICATA ===" << endl;

    cout << "Antes: ";
    preOrder(root);
    cout << endl;

    root = insert(root, 40);

    cout << "Inserindo 40 novamente." << endl;

    cout << "Depois: ";
    preOrder(root);
    cout << endl;

    cout << "Raiz apos insercao: " << root->key << endl;


    // ========================================
    // TESTE DE REMOCAO
    // ========================================

    cout << "\n=== TESTE DE REMOCAO ===" << endl;

    int remocoes[] ={20, 70, 50};

    for (int i = 0; i < 3; i++){
        int chave = remocoes[i];

        cout << "\nRemovendo " << chave << "..." << endl;

        root = remove(root, chave);

        cout << "Preorder apos remocao: ";
        preOrder(root);
        cout << endl;

        if (root != nullptr){
            cout << "Raiz: " << root->key << endl;
        }
        else{
            cout << "Arvore vazia." << endl;
        }

        // Verifica se a chave realmente foi removida
        if (root != nullptr){
            root = splay(root, chave);

            if (root->key == chave){
                cout << "Resultado da busca: 1 (ERRO)" << endl;
            }
            else{
                cout << "Resultado da busca: 0" << endl;
            }
        }
        else{
            cout << "Resultado da busca: 0" << endl;
        }
    }


    // ========================================
    // TESTE DE REMOCAO DE CHAVE INEXISTENTE
    // ========================================

    cout << "\n=== TESTE DE REMOCAO DE CHAVE INEXISTENTE ===" << endl;

    cout << "Antes: ";
    preOrder(root);
    cout << endl;

    int chaveInexistente = 999;

    cout << "Tentando remover " << chaveInexistente << "..." << endl;

    root = remove(root, chaveInexistente);

    cout << "Depois: ";
    preOrder(root);
    cout << endl;


    // ========================================
    // TESTE FINAL DE BUSCA
    // ========================================

    cout << "\n=== TESTE FINAL DE BUSCA ===" << endl;

    int buscasFinais[] ={30, 40, 60, 80, 20, 50, 70, 999};

    for (int i = 0; i < 8; i++){
        int chave = buscasFinais[i];

        root = splay(root, chave);

        cout << chave << " -> ";

        if (root != nullptr && root->key == chave){
            cout << "1";
        }
        else{
            cout << "0";
        }

        cout << endl;
    }


    // ========================================
    // ESTADO FINAL
    // ========================================

    cout << "\n=== ESTADO FINAL ===" << endl;

    cout << "Preorder: ";
    preOrder(root);
    cout << endl;

    if (root != nullptr){
        cout << "Raiz: " << root->key << endl;
    }
    else{
        cout << "Arvore vazia." << endl;
    }

    return 0;
}

*/