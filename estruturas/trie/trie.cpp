#include <bits/stdc++.h>
#include "trie.h"
using namespace std;

namespace trie{

//Insere uma chave
void insert(TrieNode *root, const std::string& key){

    TrieNode *curr = root;

    for (char c : key){
        if (curr->children[c - 'a'] == nullptr){
            TrieNode *newNode = new TrieNode();
            curr->children[c - 'a'] = newNode;
        }

        curr = curr->children[c - 'a'];
    }

    curr->isEndofWorld = true;
}

//Busca uma chave
bool search(TrieNode *root, const std::string& key){

    if (root == nullptr){
        return false;
    }

    TrieNode *curr = root;

    for (char c : key){
        if (curr->children[c - 'a'] == nullptr)
            return false;

        curr = curr->children[c - 'a'];
    }

    return curr->isEndofWorld;
}

//Verifica se prefixo existe
bool isPrefix(TrieNode *root, const std::string& prefix){
    TrieNode *curr = root;

    for (char c : prefix){
        if (curr->children[c - 'a'] == nullptr){
            return false;
        }

        curr = curr->children[c - 'a'];
    }

    return true;
}

//Verifica se raiz tem filho
bool isEmpty(TrieNode* root){
    for (int i = 0; i < 26; i++)
        if (root->children[i])
            return false;
    return true;
}

//Remove chave
TrieNode* removeRecursive(TrieNode* root, const std::string& key, int depth){
    if (!root)
        return NULL;

    if (depth == key.size()){
        if (root->isEndofWorld)
            root->isEndofWorld = false;

        if (isEmpty(root)) {
            delete (root);
            root = NULL;
        }

        return root;
    }

    int index = key[depth] - 'a';
    root->children[index] = removeRecursive(root->children[index], key, depth + 1);

    if (isEmpty(root) && root->isEndofWorld == false){
        delete (root);
        root = NULL;
    }

    return root;
}

bool remove(TrieNode*& root, const std::string& key){

    if (!search(root, key))
        return false;

    root = removeRecursive(root, key);

    return true;
}

void clear(TrieNode* root) {
    if (root == nullptr)
        return;

    for (int i = 0; i < 26; i++) {
        clear(root->children[i]);
    }

    delete root;
}

}

/* Testes antigos pra ver se tava tudo em ordem 

int main(){

    TrieNode *root = new TrieNode();

    // =========================
    // TESTE DE INSERÇÃO
    // =========================

    insert(root, "car");
    insert(root, "card");
    insert(root, "care");
    insert(root, "cat");
    insert(root, "dog");

    cout << "=== TESTE DE BUSCA ===\n";

    cout << "car  -> " << search(root, "car") << '\n';
    cout << "card -> " << search(root, "card") << '\n';
    cout << "care -> " << search(root, "care") << '\n';
    cout << "cat  -> " << search(root, "cat") << '\n';
    cout << "dog  -> " << search(root, "dog") << '\n';

    cout << "c     -> " << search(root, "c") << '\n';
    cout << "ca    -> " << search(root, "ca") << '\n';
    cout << "cars  -> " << search(root, "cars") << '\n';
    cout << "do    -> " << search(root, "do") << '\n';

    // =========================
    // TESTE DE PREFIXO
    // =========================

    cout << "\n=== TESTE DE PREFIXO ===\n";

    cout << "ca    -> " << isPrefix(root, "ca") << '\n';
    cout << "car   -> " << isPrefix(root, "car") << '\n';
    cout << "do    -> " << isPrefix(root, "do") << '\n';
    cout << "z     -> " << isPrefix(root, "z") << '\n';
    cout << "cars  -> " << isPrefix(root, "cars") << '\n';

    // =========================
    // TESTE DE REMOÇÃO
    // =========================

    cout << "\n=== TESTE DE REMOCAO ===\n";

    cout << "Removendo 'card'...\n";
    root = remove(root, "card");

    cout << "card -> " << search(root, "card") << '\n';
    cout << "car  -> " << search(root, "car") << '\n';
    cout << "care -> " << search(root, "care") << '\n';

    cout << "\nRemovendo 'car'...\n";
    root = remove(root, "car");

    cout << "car  -> " << search(root, "car") << '\n';
    cout << "care -> " << search(root, "care") << '\n';

    cout << "\nRemovendo 'care'...\n";
    root = remove(root, "care");

    cout << "care -> " << search(root, "care") << '\n';
    cout << "cat  -> " << search(root, "cat") << '\n';

    // =========================
    // REMOÇÃO DE PALAVRA INEXISTENTE
    // =========================

    cout << "\n=== REMOCAO DE PALAVRA INEXISTENTE ===\n";

    cout << "Removendo 'banana'...\n";
    root = remove(root, "banana");

    cout << "cat -> " << search(root, "cat") << '\n';
    cout << "dog -> " << search(root, "dog") << '\n';

    return 0;
}*/