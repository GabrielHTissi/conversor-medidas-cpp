#ifndef CONVERSORES_H
#define CONVERSORES_H
#include <QtSql/QSqlDatabase>

#include <string>

// Definição da classe Conversor
class Conversor {
private:
    const double FATOR = 25.4; // Constante técnica de precisão
// Métodos
public:
    bool configurarBancoDados(); // Cria o arquivo e a tabela
    double cmParaPol(double cm);  // Novo método para converter cm para polegadas
    double polParaCm(double pol);  // Novo método para converter polegadas para cm
    double processarEntrada(std::string texto); // Processa a entrada do usuário
    double mmParaPol(double mm); // Converte mm para pol
    double polParaMm(double pol); // Converte pol para mm
    void limparTela(); // Limpa a tela do console
    void salvarNoLog(double vOrigem, std::string uOrigem, double vDestino, std::string uDestino); // Salva a conversão no log
    void salvarNoBanco(double vOrigem, std::string uOrigem, double vDestino, std::string uDestino);
    double pesoBarraQuadrada(double ladoA, double comprimentoC, double densidade);
    double pesoChapa(double largura, double comprimento, double espessura, double densidade);
    double pesoBarraRedonda(double diametro, double comprimento, double densidade);
};

#endif