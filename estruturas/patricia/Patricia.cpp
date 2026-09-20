#include <iostream>
#include "patricia.h"
using namespace std;
namespace patricia{

PatriciaNode* createHead(){
    PatriciaNode* head = new PatriciaNode;

    head->key = 0;
    head->bit = 0;

    head->left = head;
    head->right = head;

    return head;
}

bool getBit(int key, int bit){
    if (bit <= 0)
        return false;

    return (key >> (bit - 1)) & 1;
}

int firstDifferentBit(int a, int b){
    for (int i = 1; i <= MAX_BITS; i++){
        if (getBit(a, i) != getBit(b, i))
            return i;
    }

    return 0;
}

bool validKey(int key){
    return key >= 0 && static_cast<long long>(key) < (1LL << MAX_BITS);
}

PatriciaNode* searchNode(PatriciaNode* head, int key){
    if (head == nullptr || head->left == head)
        return nullptr;

    PatriciaNode* parent = head;
    PatriciaNode* current = head->left;

    while (parent->bit < current->bit){
        parent = current;

        if (getBit(key, current->bit))
            current = current->right;
        else
            current = current->left;
    }

    if (current != head && current->key == key)
        return current;

    return nullptr;
}

bool search(PatriciaNode* head, int key){
    return searchNode(head, key) != nullptr;
}

void insert(PatriciaNode* head, int key){

    if (!validKey(key)){
        cout << "Chave fora do limite: " << key << '\n';
        return;
    }

    if (head->left == head){

        PatriciaNode* Patricianode = new PatriciaNode;

        Patricianode->key = key;
        Patricianode->bit = 1;

        if (getBit(key, 1)){
            Patricianode->left = head;
            Patricianode->right = Patricianode;
        }
        else{
            Patricianode->left = Patricianode;
            Patricianode->right = head;
        }

        head->left = Patricianode;

        return;
    }

    PatriciaNode* parent = head;
    PatriciaNode* current = head->left;

    while (parent->bit < current->bit){
        parent = current;

        if (getBit(key, current->bit))
            current = current->right;
        else
            current = current->left;
    }

    if (current != head && current->key == key)
        return;

    int bit = firstDifferentBit(current->key, key);

    if (bit == 0)
        return;

    parent = head;
    current = head->left;

    while (parent->bit < current->bit &&
           current->bit < bit){

        parent = current;

        if (getBit(key, current->bit))
            current = current->right;
        else
            current = current->left;
    }

    PatriciaNode* Patricianode = new PatriciaNode;

    Patricianode->key = key;
    Patricianode->bit = bit;

    if (getBit(key, bit)){
        Patricianode->left = current;
        Patricianode->right = Patricianode;
    }
    else{
        Patricianode->left = Patricianode;
        Patricianode->right = current;
    }

    if (getBit(key, parent->bit))
        parent->right = Patricianode;
    else
        parent->left = Patricianode;
}

bool remove(PatriciaNode* head, int key){

    if (head == nullptr)
        return false;

    if (head->left == head)
        return false;

    PatriciaNode* g = head;
    PatriciaNode* p = head;
    PatriciaNode* x = head->left;

    while (p->bit < x->bit){

        g = p;
        p = x;

        if (getBit(key, x->bit))
            x = x->right;
        else
            x = x->left;
    }

    if (x == head || x->key != key)
        return false;

    PatriciaNode* z = head;
    PatriciaNode* y = head;

    while (y != x){

        z = y;

        if (getBit(key, y->bit))
            y = y->right;
        else
            y = y->left;
    }

    /*
        CASO 1
        
        x == p significa que x é o nó que deve ser
        removido diretamente.
    */
    if (x == p){
        PatriciaNode* child;

        if (getBit(key, x->bit))
            child = x->left;
        else
            child = x->right;

        if (getBit(key, z->bit))
            z->right = child;
        else
            z->left = child;

        delete x;

        return true;
    }

    /*
        CASO 2
        
        x != p. p é o nó que deve ocupar o lugar
        de x.
    */

    PatriciaNode* child;

    if (getBit(key, p->bit))
        child = p->left;
    else
        child = p->right;

    if (getBit(key, g->bit))
        g->right = child;
    else
        g->left = child;

    if (getBit(key, z->bit))
        z->right = p;
    else
        z->left = p;

    p->left = x->left;
    p->right = x->right;
    p->bit = x->bit;

    delete x;

    return true;
}

void printTreeRecursive(PatriciaNode* Patricianode, int parentBit, int level){

    if (Patricianode == nullptr)
        return;

    if (Patricianode->bit <= parentBit){
        cout << string(level * 4, ' ')
             << "-> retorno para chave "
             << Patricianode->key << '\n';

        return;
    }

    cout << string(level * 4, ' ')
         << "key=" << Patricianode->key
         << " | bit=" << Patricianode->bit
         << '\n';

    cout << string(level * 4, ' ')
         << "L: ";

    if (Patricianode->left == Patricianode)
        cout << "(self)\n";
    else
        cout << '\n';

    if (Patricianode->left != Patricianode)
        printTreeRecursive(Patricianode->left, Patricianode->bit, level + 1);

    cout << string(level * 4, ' ')
         << "R: ";

    if (Patricianode->right == Patricianode)
        cout << "(self)\n";
    else
        cout << '\n';

    if (Patricianode->right != Patricianode)
        printTreeRecursive(Patricianode->right,
                           Patricianode->bit,
                           level + 1);
}

void printTree(PatriciaNode* head) {

    if (head == nullptr || head->left == head){
        cout << "Arvore vazia.\n";
        return;
    }

    cout << "=== PATRICIA ===\n";

    printTreeRecursive(head->left, head->bit, 0);
}

void freeTreeRecursive(PatriciaNode* Patricianode, int parentBit){

    if (Patricianode == nullptr)
        return;

    if (Patricianode->bit <= parentBit)
        return;

    PatriciaNode* left = Patricianode->left;
    PatriciaNode* right = Patricianode->right;

    freeTreeRecursive(left, Patricianode->bit);
    freeTreeRecursive(right, Patricianode->bit);

    delete Patricianode;
}

void clear(PatriciaNode* head){

    if (head == nullptr)
        return;

    freeTreeRecursive(head->left, head->bit);

    delete head;
}

}


/* Testes antigos pipipipopopo ta tudo em ordem :)
int main() {

    PatriciaNode* head = createHead();

    cout << "========================================\n";
    cout << "       TESTE DA PATRICIA\n";
    cout << "========================================\n\n";


    // =====================================================
    // 1. INSERCAO
    // =====================================================

    cout << "=== TESTE DE INSERCAO ===\n\n";

    int values[] = {
        10, 20, 30, 40, 50,
        60, 70, 80, 90
    };

    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {

        cout << "Inserindo " << values[i] << "...\n";

        insert(head, values[i]);
    }

    cout << "\n";


    // =====================================================
    // 2. IMPRESSAO
    // =====================================================

    cout << "=== ESTRUTURA DA PATRICIA ===\n\n";

    printTree(head);

    cout << "\n";


    // =====================================================
    // 3. BUSCA DE ELEMENTOS EXISTENTES
    // =====================================================

    cout << "=== TESTE DE BUSCA ===\n\n";

    int existing[] = {
        10, 20, 30, 40, 50,
        60, 70, 80, 90
    };

    int nExisting =
        sizeof(existing) / sizeof(existing[0]);

    for (int i = 0; i < nExisting; i++) {

        if (search(head, existing[i]) != nullptr)
            cout << existing[i] << " -> encontrado\n";
        else
            cout << existing[i] << " -> ERRO\n";
    }

    cout << "\n";


    // =====================================================
    // 4. BUSCA DE ELEMENTOS INEXISTENTES
    // =====================================================

    cout << "=== BUSCA DE INEXISTENTES ===\n\n";

    int nonexistent[] = {
        0, 5, 15, 25, 35, 45,
        55, 65, 75, 85, 95, 100
    };

    int nNonexistent =
        sizeof(nonexistent) / sizeof(nonexistent[0]);

    for (int i = 0; i < nNonexistent; i++) {

        if (search(head, nonexistent[i]) == nullptr)
            cout << nonexistent[i]
                 << " -> nao encontrado\n";
        else
            cout << nonexistent[i]
                 << " -> ERRO: encontrado\n";
    }

    cout << "\n";


    // =====================================================
    // 5. DUPLICATA
    // =====================================================

    cout << "=== TESTE DE DUPLICATA ===\n\n";

    cout << "Inserindo 30 novamente...\n";

    insert(head, 30);

    if (search(head, 30) != nullptr)
        cout << "30 continua presente.\n";
    else
        cout << "ERRO: 30 desapareceu.\n";

    cout << "\n";


    // =====================================================
    // 6. REMOCAO DE UMA FOLHA
    // =====================================================

    cout << "=== REMOCAO DE 90 ===\n\n";

    if (remove(head, 90))
        cout << "90 removido com sucesso.\n";
    else
        cout << "ERRO ao remover 90.\n";

    if (search(head, 90) == nullptr)
        cout << "Busca por 90: nao encontrado.\n";
    else
        cout << "ERRO: 90 ainda esta presente.\n";

    cout << "\n";

    printTree(head);

    cout << "\n";


    // =====================================================
    // 7. REMOCAO DE ELEMENTO INTERMEDIARIO
    // =====================================================

    cout << "=== REMOCAO DE 50 ===\n\n";

    if (remove(head, 50))
        cout << "50 removido com sucesso.\n";
    else
        cout << "ERRO ao remover 50.\n";

    if (search(head, 50) == nullptr)
        cout << "Busca por 50: nao encontrado.\n";
    else
        cout << "ERRO: 50 ainda esta presente.\n";

    cout << "\n";

    printTree(head);

    cout << "\n";


    // =====================================================
    // 8. VERIFICAR OS OUTROS ELEMENTOS
    // =====================================================

    cout << "=== VERIFICACAO APOS REMOCOES ===\n\n";

    int expected[] = {
        10, 20, 30, 40,
        60, 70, 80
    };

    int nExpected =
        sizeof(expected) / sizeof(expected[0]);

    for (int i = 0; i < nExpected; i++) {

        if (search(head, expected[i]) != nullptr)
            cout << expected[i]
                 << " -> OK\n";
        else
            cout << expected[i]
                 << " -> ERRO: desapareceu\n";
    }

    cout << "\n";


    // =====================================================
    // 9. REMOCAO DE ELEMENTO INEXISTENTE
    // =====================================================

    cout << "=== REMOCAO DE INEXISTENTE ===\n\n";

    if (remove(head, 999))
        cout << "ERRO: 999 foi removido.\n";
    else
        cout << "999 -> nao encontrado, como esperado.\n";

    cout << "\n";


    // =====================================================
    // 10. REMOVER A PRIMEIRA CHAVE
    // =====================================================

    cout << "=== REMOCAO DE 10 ===\n\n";

    if (remove(head, 10))
        cout << "10 removido com sucesso.\n";
    else
        cout << "ERRO ao remover 10.\n";

    if (search(head, 10) == nullptr)
        cout << "Busca por 10: nao encontrado.\n";
    else
        cout << "ERRO: 10 ainda esta presente.\n";

    cout << "\n";


    // =====================================================
    // 11. TESTAR NOVAMENTE AS CHAVES RESTANTES
    // =====================================================

    cout << "=== CHAVES RESTANTES ===\n\n";

    int remaining[] = {
        20, 30, 40,
        60, 70, 80
    };

    int nRemaining =
        sizeof(remaining) / sizeof(remaining[0]);

    for (int i = 0; i < nRemaining; i++) {

        if (search(head, remaining[i]) != nullptr)
            cout << remaining[i] << " -> OK\n";
        else
            cout << remaining[i]
                 << " -> ERRO\n";
    }

    cout << "\n";


    // =====================================================
    // 12. REMOVER TUDO
    // =====================================================

    cout << "=== REMOVENDO TODOS OS ELEMENTOS ===\n\n";

    for (int i = 0; i < nRemaining; i++) {

        cout << "Removendo "
             << remaining[i]
             << "... ";

        if (remove(head, remaining[i]))
            cout << "OK\n";
        else
            cout << "ERRO\n";
    }

    cout << "\n";


    // =====================================================
    // 13. VERIFICAR ARVORE VAZIA
    // =====================================================

    cout << "=== VERIFICANDO ARVORE VAZIA ===\n\n";

    printTree(head);

    cout << "\n";


    // =====================================================
    // 14. BUSCA EM ARVORE VAZIA
    // =====================================================

    cout << "Busca por 30 em arvore vazia: ";

    if (search(head, 30) == nullptr)
        cout << "nao encontrado\n";
    else
        cout << "ERRO\n";

    cout << "\n";


    // =====================================================
    // 15. REINSERCAO DEPOIS DE ESVAZIAR
    // =====================================================

    cout << "=== REINSERCAO ===\n\n";

    insert(head, 100);
    insert(head, 200);
    insert(head, 300);

    printTree(head);

    cout << "\n";

    cout << "Buscas:\n";

    int reinsertion[] = {
        100, 200, 300
    };

    for (int i = 0; i < 3; i++) {

        if (search(head, reinsertion[i]) != nullptr)
            cout << reinsertion[i] << " -> OK\n";
        else
            cout << reinsertion[i] << " -> ERRO\n";
    }

    cout << "\n";


    // =====================================================
    // 16. LIBREA A ARVORE DA MEMORIA
    // =====================================================

    freeTree(head);

    return 0;
}

*/