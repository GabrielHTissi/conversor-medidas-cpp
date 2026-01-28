#include <QApplication>// Inclui a classe QApplication
#include <QWidget>      // Inclui a classe QWidget
#include <QVBoxLayout>// Inclui a classe QVBoxLayout
#include <QLineEdit>// Inclui a classe QLineEdit
#include <QPushButton>// Inclui a classe QPushButton
#include <QLabel>// Inclui a classe QLabel
#include <QMessageBox>// Inclui a classe QMessageBox
#include "conversores.h"// Inclui a classe Conversor

class JanelaConversor : public QWidget {
    Conversor motor;
    QLineEdit *campoEntrada;// Campo de entrada de texto
    QLabel *labelResultado;// Label para mostrar o resultado

public:// Construtor
    JanelaConversor() {
        setWindowTitle("PCP Conversor Técnico");
        
        campoEntrada = new QLineEdit(this);// Campo de entrada
        campoEntrada->setPlaceholderText("Digite o valor (ex: 25,4)");
        
        QPushButton *btnParaPol = new QPushButton("Converter para Polegadas", this);// Botão de conversão
        QPushButton *btnParaMm = new QPushButton("Converter para Milímetros", this);
        labelResultado = new QLabel("Resultado: ", this);// Label de resultado

        QVBoxLayout *layout = new QVBoxLayout(this);// Layout vertical
        layout->addWidget(new QLabel("Insira a medida:"));
        layout->addWidget(campoEntrada);// Adiciona o campo de entrada ao layout
        layout->addWidget(btnParaPol);// Adiciona o botão ao layout
        layout->addWidget(btnParaMm);// Adiciona o botão ao layout
        layout->addWidget(labelResultado);// Adiciona o label ao layout

        // Conexões de eventos
        connect(btnParaPol, &QPushButton::clicked, this, &JanelaConversor::aoConverterParaPol);// Liga o clique do botão ao slot
        connect(btnParaMm, &QPushButton::clicked, this, &JanelaConversor::aoConverterParaMm);// Liga o clique do botão ao slot
        connect(campoEntrada, &QLineEdit::returnPressed, this, &JanelaConversor::aoConverterParaPol);// Enter também converte para polegadas
    }

private slots:
    void aoConverterParaPol() {
        QString entradaStr = campoEntrada->text();// Obtém o texto do campo de entrada
        bool ok;
        double valor = entradaStr.replace(",", ".").toDouble(&ok);//    Converte para double
        
        if (!ok || entradaStr.isEmpty()) {
            QMessageBox::warning(this, "Erro", "Digite um número válido.");
            return;
        }

        double pol = motor.mmParaPol(valor);
        labelResultado->setText("Resultado: " + QString::number(pol, 'f', 4) + " pol"); // Atualiza o label com o resultado
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
}; // Fim da classe com ponto e vírgula

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);// Cria a aplicação Qt
    JanelaConversor janela;// Cria a janela do conversor
    janela.show();// Exibe a janela
    return app.exec();// Inicia o loop de eventos
}