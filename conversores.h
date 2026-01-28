#ifndef CONVERSORES_H// Proteção contra inclusão múltipla
#define CONVERSORES_H// Proteção contra inclusão múltipla
#include <ctime>// Necessário para std::time_t
#include <string>// Necessário para std::string

class Conversor {
private:
    const double FATOR = 25.4; // Atributo: O dado fica "escondido" e protegido

public:
    // Métodos: O que o objeto sabe fazer
    void limparTela(); 
    double processarEntrada(std::string texto);
    double mmParaPol(double mm);
    double polParaMm(double pol);
    void salvarNoLog(double vOrigem, std::string uOrigem, double vDestino, std::string uDestino);
};

#endif