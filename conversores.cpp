#include "conversores.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>

double Conversor::processarEntrada(std::string texto) {
    std::replace(texto.begin(), texto.end(), ',', '.');
    try {
        return std::stod(texto);
    } catch (...) {
        return 0.0;
    }
}

double Conversor::mmParaPol(double mm) { return mm / FATOR; }
double Conversor::polParaMm(double pol) { return pol * FATOR; }

void Conversor::limparTela() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void Conversor::salvarNoLog(double vOrigem, std::string uOrigem, double vDestino, std::string uDestino) {
    std::ofstream arquivoLog("historico.txt", std::ios::app);
    if (arquivoLog.is_open()) {
        std::time_t agora = std::time(0);
        char timestamp[20];
        std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&agora));

        arquivoLog << "[" << timestamp << "] "
                   << "[" << vOrigem << " " << uOrigem << "] -> [" 
                   << vDestino << " " << uDestino << "]" << std::endl;
        arquivoLog.close();
    }
}