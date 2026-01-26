#ifndef CONVERSORES_H
#include <algorithm>//funções de algoritmos padrão
#include <fstream>//manipulação de arquivos

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
void salvarNoLog(double valorOrigem, std::string unidadeOrigem, double valorDestino, std::string unidadeDestino) {
    // Abre (ou cria) o arquivo historico.txt para adicionar texto no final
    std::ofstream arquivoLog("historico.txt", std::ios::app);

    if (arquivoLog.is_open()) {
        arquivoLog << "[" << valorOrigem << " " << unidadeOrigem << "] -> "
                   << "[" << valorDestino << " " << unidadeDestino << "]" << std::endl;
        arquivoLog.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo de log!" << std::endl;
    }
}

#endif // CONVERSORES_H