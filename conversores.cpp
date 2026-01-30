#include "conversores.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDateTime>

bool Conversor::configurarBancoDados() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("historico_pcp.db");

    if (!db.open()) return false;

    QSqlQuery query;
    // Cria a tabela se ela não existir
    return query.exec("CREATE TABLE IF NOT EXISTS conversoes ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "data_hora TEXT, "
                      "valor_origem REAL, "
                      "unidade_origem TEXT, "
                      "valor_destino REAL, "
                      "unidade_destino TEXT)");
}

void Conversor::salvarNoBanco(double vOrigem, std::string uOrigem, double vDestino, std::string uDestino) {
    QSqlQuery query;
    query.prepare("INSERT INTO conversoes (data_hora, valor_origem, unidade_origem, valor_destino, unidade_destino) "
                  "VALUES (:data, :vO, :uO, :vD, :uD)");
    
    query.bindValue(":data", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":vO", vOrigem);
    query.bindValue(":uO", QString::fromStdString(uOrigem));
    query.bindValue(":vD", vDestino);
    query.bindValue(":uD", QString::fromStdString(uDestino));
    
    query.exec();
}
// Implementação dos métodos da classe Conversor
double Conversor::processarEntrada(std::string texto) {
    std::replace(texto.begin(), texto.end(), ',', '.');
    try {
        return std::stod(texto);
    } catch (...) {
        return 0.0;
    }
}
double Conversor::cmParaPol(double cm) {
    return cm / 2.54; // Cálculo direto para centímetros
}

double Conversor::polParaCm(double pol) {
    return pol * 2.54; // Cálculo direto para polegadas
}
double Conversor::pesoBarraQuadrada(double lado, double comprimento, double densidade) {
    // Volume em mm³ / 1.000.000 = Volume em cm³
    return (lado * lado * comprimento * densidade) / 1000000.0;
}

double Conversor::pesoChapa(double largura, double comprimento, double espessura, double densidade) {
    return (largura * comprimento * espessura * densidade) / 1000000.0;
}
// Métodos de conversão entre mm e polegadas
double Conversor::mmParaPol(double mm) { return mm / FATOR; }
double Conversor::polParaMm(double pol) { return pol * FATOR; }

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