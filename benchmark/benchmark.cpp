#include "benchmark.h"

#include "../estruturas/trie/trie.h"
#include "../estruturas/patricia/patricia.h"
#include "../estruturas/splay/splay.h"
#include "../estruturas/treap/treap.h"
#include "../estruturas/kdtree/kdtree.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace std::chrono;


// ============================================================
// GERAÇÃO DOS DADOS
// ============================================================

vector<int> gerarDados(int n, const string& cenario) {
    vector<int> dados(n);

    for (int i = 0; i < n; i++)
        dados[i] = i + 1;

    if (cenario == "aleatorio") {
        static mt19937 gerador(123456);

        shuffle(
            dados.begin(),
            dados.end(),
            gerador
        );
    }
    else if (cenario == "invertido") {
        reverse(
            dados.begin(),
            dados.end()
        );
    }

    return dados;
}


// ============================================================
// FUNÇÕES AUXILIARES
// ============================================================

double tempoMs(
    const steady_clock::time_point& inicio,
    const steady_clock::time_point& fim
) {
    return duration<double, milli>(fim - inicio).count();
}

string chaveTrie(int valor) {
    string resultado;

    while (valor > 0) {
        valor--;
        resultado.push_back('a' + (valor % 26));
        valor /= 26;
    }

    reverse(resultado.begin(), resultado.end());

    return resultado;
}


// ============================================================
// TRIE
// ============================================================

Resultado benchmarkTrie(
    int n,
    const string& cenario,
    const vector<int>& dados
) {
    Resultado resultado;

    resultado.estrutura = "Trie";
    resultado.n = n;
    resultado.cenario = cenario;

    vector<string> chaves;
    chaves.reserve(n);

    for (int valor : dados)
        chaves.push_back(chaveTrie(valor));


    // --------------------------------------------------------
    // INSERÇÃO
    // --------------------------------------------------------

    {
        trie::TrieNode* root = new trie::TrieNode();

        auto inicio = steady_clock::now();

        for (const string& chave : chaves)
            trie::insert(root, chave);

        auto fim = steady_clock::now();

        resultado.insercao_ms = tempoMs(inicio, fim);

        trie::clear(root);
    }


    // --------------------------------------------------------
    // BUSCA EXISTENTE
    // --------------------------------------------------------

    {
        trie::TrieNode* root = new trie::TrieNode();

        for (const string& chave : chaves)
            trie::insert(root, chave);

        auto inicio = steady_clock::now();

        for (const string& chave : chaves)
            trie::search(root, chave);

        auto fim = steady_clock::now();

        resultado.busca_existente_ms = tempoMs(inicio, fim);

        trie::clear(root);
    }


    // --------------------------------------------------------
    // BUSCA INEXISTENTE
    // --------------------------------------------------------

    {
        trie::TrieNode* root = new trie::TrieNode();

        for (const string& chave : chaves)
            trie::insert(root, chave);

        auto inicio = steady_clock::now();

        for (int i = n + 1; i <= 2 * n; i++)
            trie::search(root, chaveTrie(i));

        auto fim = steady_clock::now();

        resultado.busca_inexistente_ms = tempoMs(inicio, fim);

        trie::clear(root);
    }


    // --------------------------------------------------------
    // REMOÇÃO
    // --------------------------------------------------------

    {
        trie::TrieNode* root = new trie::TrieNode();

        for (const string& chave : chaves)
            trie::insert(root, chave);

        auto inicio = steady_clock::now();

        for (const string& chave : chaves)
            trie::remove(root, chave);

        auto fim = steady_clock::now();

        resultado.remocao_ms = tempoMs(inicio, fim);

        trie::clear(root);
    }

    return resultado;
}


// ============================================================
// PATRICIA
// ============================================================

Resultado benchmarkPatricia(
    int n,
    const string& cenario,
    const vector<int>& dados
) {
    Resultado resultado;

    resultado.estrutura = "Patricia";
    resultado.n = n;
    resultado.cenario = cenario;


    // --------------------------------------------------------
    // INSERÇÃO
    // --------------------------------------------------------

    {
        patricia::PatriciaNode* head =
            patricia::createHead();

        auto inicio = steady_clock::now();

        for (int chave : dados)
            patricia::insert(head, chave);

        auto fim = steady_clock::now();

        resultado.insercao_ms = tempoMs(inicio, fim);

        patricia::clear(head);
    }


    // --------------------------------------------------------
    // BUSCA EXISTENTE
    // --------------------------------------------------------

    {
        patricia::PatriciaNode* head =
            patricia::createHead();

        for (int chave : dados)
            patricia::insert(head, chave);

        auto inicio = steady_clock::now();

        for (int chave : dados)
            patricia::search(head, chave);

        auto fim = steady_clock::now();

        resultado.busca_existente_ms = tempoMs(inicio, fim);

        patricia::clear(head);
    }


    // --------------------------------------------------------
    // BUSCA INEXISTENTE
    // --------------------------------------------------------

    {
        patricia::PatriciaNode* head =
            patricia::createHead();

        for (int chave : dados)
            patricia::insert(head, chave);

        auto inicio = steady_clock::now();

        for (int chave = n + 1; chave <= 2 * n; chave++)
            patricia::search(head, chave);

        auto fim = steady_clock::now();

        resultado.busca_inexistente_ms = tempoMs(inicio, fim);

        patricia::clear(head);
    }


    // --------------------------------------------------------
    // REMOÇÃO
    // --------------------------------------------------------

    {
        patricia::PatriciaNode* head =
            patricia::createHead();

        for (int chave : dados)
            patricia::insert(head, chave);

        auto inicio = steady_clock::now();

        for (int chave : dados)
            patricia::remove(head, chave);

        auto fim = steady_clock::now();

        resultado.remocao_ms = tempoMs(inicio, fim);

        patricia::clear(head);
    }

    return resultado;
}


// ============================================================
// SPLAY
// ============================================================

Resultado benchmarkSplay(
    int n,
    const string& cenario,
    const vector<int>& dados
) {
    Resultado resultado;

    resultado.estrutura = "Splay";
    resultado.n = n;
    resultado.cenario = cenario;


    // --------------------------------------------------------
    // INSERÇÃO
    // --------------------------------------------------------

    {
        splay::SplayTree tree{nullptr};
        cout << "  Splay - insercao..." << endl;
        auto inicio = steady_clock::now();
        
        for (int chave : dados)
            splay::insert(&tree, chave);

        auto fim = steady_clock::now();

        resultado.insercao_ms = tempoMs(inicio, fim);

        splay::clear(&tree);
    }


    // --------------------------------------------------------
    // BUSCA EXISTENTE
    // --------------------------------------------------------

    {
        splay::SplayTree tree{nullptr};
        cout << "  Splay - existente..." << endl;
        for (int chave : dados)
            splay::insert(&tree, chave);

        auto inicio = steady_clock::now();

        for (int chave : dados)
            splay::search(&tree, chave);

        auto fim = steady_clock::now();

        resultado.busca_existente_ms = tempoMs(inicio, fim);

        splay::clear(&tree);
    }


    // --------------------------------------------------------
    // BUSCA INEXISTENTE
    // --------------------------------------------------------

    {
        splay::SplayTree tree{nullptr};
        cout << "  Splay - inexistente..." << endl;
        for (int chave : dados)
            splay::insert(&tree, chave);

        auto inicio = steady_clock::now();

        for (int chave = n + 1; chave <= 2 * n; chave++)
            splay::search(&tree, chave);

        auto fim = steady_clock::now();

        resultado.busca_inexistente_ms = tempoMs(inicio, fim);

        splay::clear(&tree);
    }


    // --------------------------------------------------------
    // REMOÇÃO
    // --------------------------------------------------------

    {
        splay::SplayTree tree{nullptr};
        cout << "  Splay - remocao..." << endl;
        for (int chave : dados)
            splay::insert(&tree, chave);

        auto inicio = steady_clock::now();

        for (int chave : dados)
            splay::remove(&tree, chave);

        auto fim = steady_clock::now();

        resultado.remocao_ms = tempoMs(inicio, fim);

        splay::clear(&tree);
    }
    cout << "  Splay - concluido" << endl;
    return resultado;
}


// ============================================================
// TREAP
// ============================================================

Resultado benchmarkTreap(
    int n,
    const string& cenario,
    const vector<int>& dados
) {
    Resultado resultado;

    resultado.estrutura = "Treap";
    resultado.n = n;
    resultado.cenario = cenario;


    // --------------------------------------------------------
    // INSERÇÃO
    // --------------------------------------------------------

    {
        treap::TreapTree tree{nullptr};

        auto inicio = steady_clock::now();

        for (int chave : dados)
            treap::insert(&tree, chave);

        auto fim = steady_clock::now();

        resultado.insercao_ms = tempoMs(inicio, fim);

        treap::clear(&tree);
    }


    // --------------------------------------------------------
    // BUSCA EXISTENTE
    // --------------------------------------------------------

    {
        treap::TreapTree tree{nullptr};

        for (int chave : dados)
            treap::insert(&tree, chave);

        auto inicio = steady_clock::now();

        for (int chave : dados)
            treap::search(&tree, chave);

        auto fim = steady_clock::now();

        resultado.busca_existente_ms = tempoMs(inicio, fim);

        treap::clear(&tree);
    }


    // --------------------------------------------------------
    // BUSCA INEXISTENTE
    // --------------------------------------------------------

    {
        treap::TreapTree tree{nullptr};

        for (int chave : dados)
            treap::insert(&tree, chave);

        auto inicio = steady_clock::now();

        for (int chave = n + 1; chave <= 2 * n; chave++)
            treap::search(&tree, chave);

        auto fim = steady_clock::now();

        resultado.busca_inexistente_ms = tempoMs(inicio, fim);

        treap::clear(&tree);
    }


    // --------------------------------------------------------
    // REMOÇÃO
    // --------------------------------------------------------

    {
        treap::TreapTree tree{nullptr};

        for (int chave : dados)
            treap::insert(&tree, chave);

        auto inicio = steady_clock::now();

        for (int chave : dados)
            treap::remove(&tree, chave);

        auto fim = steady_clock::now();

        resultado.remocao_ms = tempoMs(inicio, fim);

        treap::clear(&tree);
    }

    return resultado;
}


// ============================================================
// KD-TREE
// ============================================================

Resultado benchmarkKDTree(
    int n,
    const string& cenario,
    const vector<int>& dados
) {
    Resultado resultado;

    resultado.estrutura = "KD-Tree";
    resultado.n = n;
    resultado.cenario = cenario;


    //Cada chave vira um ponto: (chave, y). O segundo eixo é gerado de forma determinística, mas diferente do primeiro para evitar colocar todos os pontos na reta y = 2x.

    vector<array<int, 2>> pontos;
    pontos.reserve(n);

    mt19937 gerador(987654);

    vector<int> valoresY(n);

    for (int i = 0; i < n; i++)
        valoresY[i] = i + 1;

    shuffle(
        valoresY.begin(),
        valoresY.end(),
        gerador
    );

    for (int chave : dados) {
        array<int, 2> ponto;

        ponto[0] = chave;
        ponto[1] = valoresY[chave - 1];

        pontos.push_back(ponto);
    }


    // --------------------------------------------------------
    // INSERÇÃO
    // --------------------------------------------------------

    {
        kdtree::KDTree tree{nullptr};

        auto inicio = steady_clock::now();

        for (auto& ponto : pontos) {
            int p[2] = {
                ponto[0],
                ponto[1]
            };

            kdtree::insert(&tree, p);
        }

        auto fim = steady_clock::now();

        resultado.insercao_ms = tempoMs(inicio, fim);

        kdtree::clear(&tree);
    }


    // --------------------------------------------------------
    // BUSCA EXISTENTE
    // --------------------------------------------------------

    {
        kdtree::KDTree tree{nullptr};

        for (auto& ponto : pontos) {
            int p[2] = {
                ponto[0],
                ponto[1]
            };

            kdtree::insert(&tree, p);
        }

        auto inicio = steady_clock::now();

        for (auto& ponto : pontos) {
            int p[2] = {
                ponto[0],
                ponto[1]
            };

            kdtree::search(&tree, p);
        }

        auto fim = steady_clock::now();

        resultado.busca_existente_ms = tempoMs(inicio, fim);

        kdtree::clear(&tree);
    }


    // --------------------------------------------------------
    // BUSCA INEXISTENTE
    // --------------------------------------------------------

    {
        kdtree::KDTree tree{nullptr};

        for (auto& ponto : pontos) {
            int p[2] = {
                ponto[0],
                ponto[1]
            };

            kdtree::insert(&tree, p);
        }

        auto inicio = steady_clock::now();

        for (int chave = n + 1; chave <= 2 * n; chave++) {
            int p[2] = {
                chave,
                chave
            };

            kdtree::search(&tree, p);
        }

        auto fim = steady_clock::now();

        resultado.busca_inexistente_ms = tempoMs(inicio, fim);

        kdtree::clear(&tree);
    }


    // --------------------------------------------------------
    // REMOÇÃO
    // --------------------------------------------------------

    {
        kdtree::KDTree tree{nullptr};

        for (auto& ponto : pontos) {
            int p[2] = {
                ponto[0],
                ponto[1]
            };

            kdtree::insert(&tree, p);
        }

        auto inicio = steady_clock::now();

        for (auto& ponto : pontos) {
            int p[2] = {
                ponto[0],
                ponto[1]
            };

            kdtree::remove(&tree, p);
        }

        auto fim = steady_clock::now();

        resultado.remocao_ms = tempoMs(inicio, fim);

        kdtree::clear(&tree);
    }

    return resultado;
}


// ============================================================
// SALVAR CSV
// ============================================================

void salvarCSV(
    const vector<Resultado>& resultados,
    const string& caminho
) {
    ofstream arquivo(caminho);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir arquivo CSV: "
             << caminho << endl;
        return;
    }

    arquivo
        << "estrutura,"
        << "n,"
        << "cenario,"
        << "insercao_ms,"
        << "busca_existente_ms,"
        << "busca_inexistente_ms,"
        << "remocao_ms\n";

    for (const Resultado& resultado : resultados) {
        arquivo
            << resultado.estrutura << ","
            << resultado.n << ","
            << resultado.cenario << ","
            << resultado.insercao_ms << ","
            << resultado.busca_existente_ms << ","
            << resultado.busca_inexistente_ms << ","
            << resultado.remocao_ms
            << "\n";
    }

    arquivo.close();
}


// ============================================================
// EXECUÇÃO GERAL
// ============================================================

void executarBenchmark() {

    const vector<int> tamanhos = {
        100,
        1000,
        10000,
        100000,
    };

    const vector<string> cenarios = {
        "aleatorio",
        "ordenado",
        "invertido"
    };

    vector<Resultado> resultados;


    for (int n : tamanhos) {

        for (const string& cenario : cenarios) {

            cout << "\n========================================\n";
            cout << "N = " << n
                 << " | Cenario = " << cenario
                 << "\n";
            cout << "========================================\n";


            vector<int> dados =
                gerarDados(n, cenario);


            // ------------------------------------------------
            // TRIE
            // ------------------------------------------------

            cout << "Trie..." << endl;

            Resultado trieResultado =
                benchmarkTrie(
                    n,
                    cenario,
                    dados
                );

            resultados.push_back(trieResultado);


            // ------------------------------------------------
            // PATRICIA
            // ------------------------------------------------

            cout << "Patricia..." << endl;

            Resultado patriciaResultado =
                benchmarkPatricia(
                    n,
                    cenario,
                    dados
                );

            resultados.push_back(patriciaResultado);


            // ------------------------------------------------
            // SPLAY
            // ------------------------------------------------

            cout << "Splay..." << endl;

            Resultado splayResultado =
                benchmarkSplay(
                    n,
                    cenario,
                    dados
                );

            resultados.push_back(splayResultado);


            // ------------------------------------------------
            // TREAP
            // ------------------------------------------------

            cout << "Treap..." << endl;

            Resultado treapResultado =
                benchmarkTreap(
                    n,
                    cenario,
                    dados
                );

            resultados.push_back(treapResultado);


            // ------------------------------------------------
            // KD-TREE
            // ------------------------------------------------

            cout << "KD-Tree..." << endl;

            Resultado kdResultado =
                benchmarkKDTree(
                    n,
                    cenario,
                    dados
                );

            resultados.push_back(kdResultado);
        }
    }


    salvarCSV(
        resultados,
        "resultados/resultados.csv"
    );

    cout << "\n========================================\n";
    cout << "Benchmark concluido!\n";
    cout << "Resultados salvos em:\n";
    cout << "resultados/resultados.csv\n";
    cout << "========================================\n";
}