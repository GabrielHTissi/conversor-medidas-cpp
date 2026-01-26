#ifndef CONVERSORES_H
#define CONVERSORES_H

#include <string>

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