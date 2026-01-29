#ifndef CONVERSORES_H
#define CONVERSORES_H

#include <string>

class Conversor {
private:
    const double FATOR = 25.4; // Constante técnica de precisão

public:
    double processarEntrada(std::string texto);
    double mmParaPol(double mm);
    double polParaMm(double pol);
    void limparTela();
    void salvarNoLog(double vOrigem, std::string uOrigem, double vDestino, std::string uDestino);
};

#endif