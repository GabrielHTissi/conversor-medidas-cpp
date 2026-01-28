#include "conversores.h"// Implementação da classe Conversor
#include <algorithm>// Necessário para std::replace
#include <fstream>// Necessário para std::ofstream
#include <iostream>// Necessário para std::system
#include <ctime>// Necessário para std::time_t

// O :: indica que a função pertence à classe Conversor
double Conversor::processarEntrada(std::string texto) {
    std::replace(texto.begin(), texto.end(), ',', '.');
    return std::stod(texto);
}
// Converte milímetros para polegadas
double Conversor::mmParaPol(double mm) {
    return mm / FATOR; // A classe já conhece o FATOR (25.4)
}
// Converte polegadas para milímetros
double Conversor::polParaMm(double pol) {
    return pol * FATOR;
}// Limpa a tela do console
void Conversor::limparTela() { // O prefixo Conversor:: é obrigatório
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}
// Salva a conversão no arquivo de log
void Conversor::salvarNoLog(double vOrigem, std::string uOrigem, double vDestino, std::string uDestino) {
    std::ofstream arquivoLog("historico.txt", std::ios::app);
    
    if (arquivoLog.is_open()) {
        // Bloco do Tempo
        std::time_t agora = std::time(0);
        char timestamp[20];
        std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&agora));

        // Gravação do Log
        arquivoLog << "[" << timestamp << "] "
                   << "[" << vOrigem << " " << uOrigem << "] -> [" 
                   << vDestino << " " << uDestino << "]" << std::endl;
        
        arquivoLog.close(); /
    } 
} 