#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <string>
#include <vector>

struct Resultado {
    std::string estrutura;
    int n;
    std::string cenario;

    double insercao_ms;
    double busca_existente_ms;
    double busca_inexistente_ms;
    double remocao_ms;
};

std::vector<int> gerarDados(int n, const std::string& cenario);

void executarBenchmark();

void salvarCSV(
    const std::vector<Resultado>& resultados,
    const std::string& caminho
);

#endif