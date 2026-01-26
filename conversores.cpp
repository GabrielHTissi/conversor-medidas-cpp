#include "conversores.h"
#include <algorithm>
#include <fstream>
#include <iostream>

// O :: indica que a função pertence à classe Conversor
double Conversor::processarEntrada(std::string texto) {
    std::replace(texto.begin(), texto.end(), ',', '.');
    return std::stod(texto);
}

double Conversor::mmParaPol(double mm) {
    return mm / FATOR; // A classe já conhece o FATOR (25.4)
}

double Conversor::polParaMm(double pol) {
    return pol * FATOR;
}
void Conversor::limparTela() { // O prefixo Conversor:: é obrigatório
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void Conversor::salvarNoLog(double vOrigem, std::string uOrigem, double vDestino, std::string uDestino) {
    std::ofstream arquivoLog("historico.txt", std::ios::app);
    if (arquivoLog.is_open()) {
        arquivoLog << "[" << vOrigem << " " << uOrigem << "] -> [" 
                   << vDestino << " " << uDestino << "]" << std::endl;
        arquivoLog.close();
    }
}