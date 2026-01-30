#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "conversores.h"

class JanelaConversor : public QWidget {
    Conversor motor;
    QLineEdit *campoEntrada;
    QLabel *labelResultado;

public:
    JanelaConversor() {
        aplicarEstilo();
        setWindowTitle("PCP Conversor Técnico - MHM");

        campoEntrada = new QLineEdit(this);
        campoEntrada->setPlaceholderText("Digite o valor (ex: 25,4)");

        QPushButton *btnParaPol = new QPushButton("Converter para Polegadas", this);
        QPushButton *btnParaMm = new QPushButton("Converter para Milímetros", this);
        QPushButton *btnParaCm = new QPushButton("Converter para Centímetros", this);
        QPushButton *btnHistorico = new QPushButton("Ver Histórico", this);
        
        labelResultado = new QLabel("Resultado: ", this);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(new QLabel("Insira a medida:"));
        layout->addWidget(campoEntrada);
        layout->addWidget(btnParaPol);
        layout->addWidget(btnParaMm);
        layout->addWidget(btnParaCm);
        layout->addWidget(btnHistorico);
        layout->addWidget(labelResultado);

        // Conexões
        connect(btnParaPol, &QPushButton::clicked, this, &JanelaConversor::aoConverterParaPol);
        connect(btnParaMm, &QPushButton::clicked, this, &JanelaConversor::aoConverterParaMm);
        connect(btnParaCm, &QPushButton::clicked, this, &JanelaConversor::aoConverterParaCm);
        connect(btnHistorico, &QPushButton::clicked, this, &JanelaConversor::mostrarHistorico);
        connect(campoEntrada, &QLineEdit::returnPressed, this, &JanelaConversor::aoConverterParaPol);
    }

private:
    void aplicarEstilo() {
        this->setStyleSheet(
            "QWidget { background-color: #1e1e1e; color: #ffffff; font-family: 'Segoe UI', Arial; }"
            "QLineEdit { background-color: #2d2d2d; border: 2px solid #3d3d3d; border-radius: 5px; padding: 8px; }"
            "QPushButton { background-color: #0078d4; color: white; border-radius: 5px; padding: 10px; font-weight: bold; }"
            "QPushButton:hover { background-color: #2b88d8; }"
            "QLabel { font-size: 15px; margin-top: 10px; color: #ffffff; }"
            "QTableWidget { background-color: #2d2d2d; gridline-color: #3d3d3d; color: white; }"
            "QHeaderView::section { background-color: #3d3d3d; color: white; padding: 4px; }"
        );
    }

private slots:
    void aoConverterParaPol() {
        QString entradaStr = campoEntrada->text();
        bool ok;
        double valor = entradaStr.replace(",", ".").toDouble(&ok);
        if (!ok || entradaStr.isEmpty()) {
            QMessageBox::warning(this, "Erro", "Digite um número válido.");
            return;
        }
        double pol = motor.mmParaPol(valor);
        labelResultado->setText("Resultado: " + QString::number(pol, 'f', 4) + " pol");
        motor.salvarNoBanco(valor, "mm", pol, "pol");
    }

    void aoConverterParaMm() {
        QString entradaStr = campoEntrada->text();
        bool ok;
        double valor = entradaStr.replace(",", ".").toDouble(&ok);
        if (!ok || entradaStr.isEmpty()) {
            QMessageBox::warning(this, "Erro", "Digite um número válido.");
            return;
        }
        double mm = motor.polParaMm(valor);
        labelResultado->setText("Resultado: " + QString::number(mm, 'f', 4) + " mm");
        motor.salvarNoBanco(valor, "pol", mm, "mm");
    }

    void aoConverterParaCm() {
        QString entradaStr = campoEntrada->text();
        bool ok;
        double valor = entradaStr.replace(",", ".").toDouble(&ok);
        if (!ok || entradaStr.isEmpty()) {
            QMessageBox::warning(this, "Erro", "Digite um número válido.");
            return;
        }
        double cm = motor.polParaCm(valor);
        labelResultado->setText("Resultado: " + QString::number(cm, 'f', 4) + " cm");
        motor.salvarNoBanco(valor, "pol", cm, "cm");
    }

    void mostrarHistorico() {
        QDialog janelaLog(this);
        janelaLog.setWindowTitle("Histórico PCP - MHM");
        janelaLog.setMinimumSize(600, 400);

        QTableWidget *tabela = new QTableWidget(&janelaLog);
        tabela->setColumnCount(4);
        tabela->setHorizontalHeaderLabels({"Data/Hora", "Origem", "Destino", "Unidade"});
        tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        QSqlQuery query("SELECT data_hora, valor_origem, valor_destino, unidade_destino FROM conversoes ORDER BY id DESC");
        int linha = 0;
        while (query.next()) {
            tabela->insertRow(linha);
            tabela->setItem(linha, 0, new QTableWidgetItem(query.value(0).toString()));
            tabela->setItem(linha, 1, new QTableWidgetItem(query.value(1).toString()));
            tabela->setItem(linha, 2, new QTableWidgetItem(query.value(2).toString()));
            tabela->setItem(linha, 3, new QTableWidgetItem(query.value(3).toString()));
            linha++;
        }

        QVBoxLayout *layoutLog = new QVBoxLayout(&janelaLog);
        layoutLog->addWidget(tabela);
        janelaLog.exec(); // Usa exec() para ser modal (travar a janela principal enquanto aberta)
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    Conversor meuConversor;
    if (!meuConversor.configurarBancoDados()) {
        QMessageBox::critical(nullptr, "Erro de Banco", "Não foi possível abrir o banco de dados.");
    }

    JanelaConversor janela;
    janela.show();
    return app.exec();
}