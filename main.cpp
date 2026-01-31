#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem> // ADICIONADO: Necessário para as células da tabela
#include <QHeaderView>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QFileDialog>
#include <QFile>            // ADICIONADO: Necessário para manipulação de arquivos
#include <QTextStream>
#include <QTabWidget> 
#include "conversores.h"

class JanelaConversor : public QWidget {
    Conversor motor;
    QLineEdit *campoEntrada;
    QLabel *labelResultado;
    QLineEdit *inputLado, *inputComp;
    QLabel *labelPeso;

public:
    JanelaConversor() {
        aplicarEstilo();
        setWindowTitle("PCP Conversor Técnico");
        setMinimumSize(500, 600);

        // Layout principal que contém as abas
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        QTabWidget *abas = new QTabWidget(this);

        QWidget *abaConversor = new QWidget();
        setupAbaConversor(abaConversor);
        
        QWidget *abaPeso = new QWidget();
        setupAbaPeso(abaPeso);

        abas->addTab(abaConversor, "Conversor de Medidas");
        abas->addTab(abaPeso, "Cálculo de Peso");

        mainLayout->addWidget(abas);        
    }

private:
    void setupAbaConversor(QWidget *aba) {
        QVBoxLayout *layout = new QVBoxLayout(aba);
        
        campoEntrada = new QLineEdit(aba);
        campoEntrada->setPlaceholderText("Digite o valor (ex: 25,4)");

        QPushButton *btnParaPol = new QPushButton("Converter para Polegadas", aba);
        QPushButton *btnParaMm = new QPushButton("Converter para Milímetros", aba);
        QPushButton *btnParaCm = new QPushButton("Converter para Centímetros", aba);
        QPushButton *btnHistorico = new QPushButton("Ver Histórico", aba);
        QPushButton *btnExportar = new QPushButton("Exportar CSV", aba);
        
        labelResultado = new QLabel("Resultado: ", aba);

        layout->addWidget(new QLabel("Insira a medida:"));
        layout->addWidget(campoEntrada);
        layout->addWidget(btnParaPol);
        layout->addWidget(btnParaMm);
        layout->addWidget(btnParaCm);
        layout->addWidget(btnHistorico);
        layout->addWidget(btnExportar);
        layout->addWidget(labelResultado);

        connect(btnParaPol, &QPushButton::clicked, this, &JanelaConversor::aoConverterParaPol);
        connect(btnParaMm, &QPushButton::clicked, this, &JanelaConversor::aoConverterParaMm);
        connect(btnParaCm, &QPushButton::clicked, this, &JanelaConversor::aoConverterParaCm);
        connect(btnHistorico, &QPushButton::clicked, this, &JanelaConversor::mostrarHistorico);
        connect(btnExportar, &QPushButton::clicked, this, &JanelaConversor::exportarParaCSV);
        connect(campoEntrada, &QLineEdit::returnPressed, this, &JanelaConversor::aoConverterParaPol);
        btnParaPol->setToolTip("Converte o valor de Milímetros para Polegadas");
        btnParaMm->setToolTip("Converte o valor de Polegadas para Milímetros");
        btnExportar->setToolTip("Gera um arquivo .csv com todo o histórico do banco de dados");
        inputLado->setToolTip("Insira a medida do lado da barra em milímetros");
    }

    void setupAbaPeso(QWidget *aba) {
        QVBoxLayout *layout = new QVBoxLayout(aba);
        layout->addWidget(new QLabel("Cálculo para Barra Quadrada (Aço Carbono):"));
        
        inputLado = new QLineEdit(aba);
        inputLado->setPlaceholderText("Lado A (mm)");
        inputComp = new QLineEdit(aba);
        inputComp->setPlaceholderText("Comprimento C (mm)");
        
        QPushButton *btnCalcular = new QPushButton("Calcular Peso Estimado", aba);
        labelPeso = new QLabel("Peso: 0.00 kg", aba);

        layout->addWidget(new QLabel("Lado A (mm):"));
        layout->addWidget(inputLado);
        layout->addWidget(new QLabel("Comprimento C (mm):"));
        layout->addWidget(inputComp);
        layout->addWidget(btnCalcular);
        layout->addWidget(labelPeso);

        connect(btnCalcular, &QPushButton::clicked, this, &JanelaConversor::aoCalcularPeso);
    }

    void aplicarEstilo() {
        this->setStyleSheet(
            "QWidget { background-color: #1e1e1e; color: #ffffff; font-family: 'Segoe UI', Arial; }"
            "QTabWidget::pane { border: 1px solid #3d3d3d; top: -1px; }"
            "QTabBar::tab { background: #2d2d2d; padding: 12px; min-width: 150px; border: 1px solid #3d3d3d; }"
            "QTabBar::tab:selected { background: #0078d4; border-bottom-color: #0078d4; }"
            "QLineEdit { background-color: #2d2d2d; border: 2px solid #3d3d3d; border-radius: 5px; padding: 8px; font-size: 14px; }"
            "QPushButton { background-color: #0078d4; color: white; border-radius: 5px; padding: 10px; font-weight: bold; margin-top: 5px; }"
            "QPushButton:hover { background-color: #2b88d8; }"
            "QLabel { font-size: 14px; margin-top: 5px; color: #ffffff; }"
            "QTableWidget { background-color: #2d2d2d; gridline-color: #3d3d3d; color: white; }"
            "QHeaderView::section { background-color: #3d3d3d; color: white; padding: 4px; }"
        );
    }

private slots:
    void aoCalcularPeso() {
        bool ok1, ok2;
        double lado = inputLado->text().replace(",", ".").toDouble(&ok1);
        double comp = inputComp->text().replace(",", ".").toDouble(&ok2);

        if (ok1 && ok2) {
            // Cálculo: (Lado * Lado * Comprimento * Densidade do Aço) / 1.000.000
            double peso = motor.pesoBarraQuadrada(lado, comp, 7.85); 
            labelPeso->setText("Peso Estimado: " + QString::number(peso, 'f', 2) + " kg");
        } else {
            QMessageBox::warning(this, "Erro de Input", "Certifique-se de inserir apenas números nos campos de medida.");
        }
    }

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
        QVBoxLayout *layoutLog = new QVBoxLayout(&janelaLog);

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

        layoutLog->addWidget(tabela);
        janelaLog.exec();
    }

    void exportarParaCSV() {
        QString nomeArquivo = QFileDialog::getSaveFileName(this, "Exportar Histórico", "", "CSV Files (*.csv);;All Files (*)");
        if (nomeArquivo.isEmpty()) return;

        QFile arquivo(nomeArquivo);
        if (arquivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&arquivo);
            out << "Data/Hora;Valor Origem;Unidade Origem;Valor Destino;Unidade Destino\n";

            QSqlQuery query("SELECT data_hora, valor_origem, unidade_origem, valor_destino, unidade_destino FROM conversoes");
            while (query.next()) {
                out << query.value(0).toString() << ";"
                    << query.value(1).toString() << ";"
                    << query.value(2).toString() << ";"
                    << query.value(3).toString() << ";"
                    << query.value(4).toString() << "\n";
            }
            arquivo.close();
            QMessageBox::information(this, "Sucesso", "Histórico exportado com sucesso!");
        }
    }
    campoEntrada->setFocus(); // O cursor já nasce piscando pronto para o trabalho
    QPushButton *btnLimpar = new QPushButton("Limpar Campos", aba);
layout->addWidget(btnLimpar);

// Conexão rápida (usando Lambda do C++):
connect(btnLimpar, &QPushButton::clicked, this, [=]() {
    campoEntrada->clear();
    labelResultado->setText("Resultado: ");
});

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