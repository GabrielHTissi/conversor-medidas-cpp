#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "conversores.h"

class JanelaConversor : public QWidget {
    Conversor motor;
    QLineEdit *campoEntrada;
    QLabel *labelResultado;

public:
    JanelaConversor() {
        aplicarEstilo(); // Agora o compilador encontra esta função
        setWindowTitle("Conversor Técnico");
        
        campoEntrada = new QLineEdit(this);
        campoEntrada->setPlaceholderText("Digite o valor (ex: 25,4)");
        
        QPushButton *btnParaPol = new QPushButton("Converter para Polegadas", this);
        QPushButton *btnParaMm = new QPushButton("Converter para Milímetros", this);
        labelResultado = new QLabel("Resultado: ", this);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(new QLabel("Insira a medida:"));
        layout->addWidget(campoEntrada);
        layout->addWidget(btnParaPol);
        layout->addWidget(btnParaMm);
        layout->addWidget(labelResultado);

        connect(btnParaPol, &QPushButton::clicked, this, &JanelaConversor::aoConverterParaPol);
        connect(btnParaMm, &QPushButton::clicked, this, &JanelaConversor::aoConverterParaMm);
        connect(campoEntrada, &QLineEdit::returnPressed, this, &JanelaConversor::aoConverterParaPol);

        QPushButton *btnParaCm = new QPushButton("Converter para Centímetros", this);
    layout->addWidget(btnParaCm);
    connect(btnParaCm, &QPushButton::clicked, this, &JanelaConversor::aoConverterParaCm);
    } // Fim do Construtor

private:
    void aplicarEstilo() {
        this->setStyleSheet(
            "QWidget { background-color: #1e1e1e; color: #ffffff; font-family: 'Segoe UI', Arial; }"
            "QLineEdit { background-color: #2d2d2d; border: 2px solid #3d3d3d; border-radius: 5px; padding: 8px; }"
            "QPushButton { background-color: #0078d4; color: white; border-radius: 5px; padding: 10px; font-weight: bold; }"
            "QPushButton:hover { background-color: #2b88d8; }"
            "QLabel { font-size: 15px; margin-top: 10px; color: #ffffff; }"
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
        motor.salvarNoLog(valor, "mm", pol, "pol");
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
        motor.salvarNoLog(valor, "pol", mm, "mm");
    }
    void aoConverterParaCm() {
    QString entradaStr = campoEntrada->text();
    bool ok;
    double valor = entradaStr.replace(",", ".").toDouble(&ok);
    
    if (!ok || entradaStr.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Digite um número válido.");
        return;
    }

    double cm = motor.polParaCm(valor); // Usa o novo motor
    labelResultado->setText("Resultado: " + QString::number(cm, 'f', 4) + " cm");
    motor.salvarNoLog(valor, "pol", cm, "cm");
}
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    JanelaConversor janela;
    janela.show();
    return app.exec();
}