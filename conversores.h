#ifndef CONVERSORES_H
#include <algorithm>//funções de algoritmos padrão

const double FATOR = 25.4;//constante de conversão de polegadas para milímetros(1 polegada = 25,4 mm)

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
void limparTela() {
    // No Mac/Linux usamos "clear", no Windows seria "cls"
    std::system("clear");
}


#endif // CONVERSORES_H