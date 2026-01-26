#ifndef CONVERSORES_H
#include <algorithm>

const double FATOR = 25.4;

double processarEntrada(std::string texto) {
    std::replace(texto.begin(), texto.end(), ',', '.');
    return std::stod(texto);
}

double mmParaPol(double mm) {
    return mm / FATOR;
}

double polParaMm(double pol) {
    return pol * FATOR;
}

#endif // CONVERSORES_H