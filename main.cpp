#include <QApplication>// Inclusão da biblioteca principal do Qt
#include <QWidget>// Classe base para todas as janelas do Qt
#include <QVBoxLayout>// Layout em coluna
#include <QLineEdit>// Campo de entrada de texto
#include <QPushButton>// Botão clicável
#include <QLabel>// Rótulo de texto
#include "conversores.h"// Inclusão da classe Conversor

class JanelaConversor : public QWidget { //Isso se chama Herança. Você está dizendo que sua janela é um "filho" da classe QWidget (que já vem pronta no Qt). Ela "herda" todas as habilidades de ser uma janela (abrir, fechar, minimizar) de forma pública.
    Conversor motor; // O motor de cálculo que você já criou
    QLineEdit *campoEntrada; // Campo para o usuário digitar o valor
    QLabel *labelResultado; // Rótulo para mostrar o resultado

public: // Construtor da janela
    JanelaConversor() {
        setWindowTitle("PCP Conversor"); // Título da janela
        
        // 1. Criar os componentes
        campoEntrada = new QLineEdit(this); // Campo de entrada
        campoEntrada->setPlaceholderText("Digite o valor (ex: 25,4)");
        
        QPushButton *btnParaPol = new QPushButton("Converter para Polegadas", this);
        QPushButton *btnParaMm = new QPushButton("Converter para Milímetros", this);
        labelResultado = new QLabel("Resultado: ", this);

        // 2. Organizar em uma coluna (Layout)
        QVBoxLayout *layout = new QVBoxLayout(this); // Layout em coluna
        layout->addWidget(new QLabel("Insira a medida:")); // Rótulo de instrução
        layout->addWidget(campoEntrada); // Campo de entrada
        layout->addWidget(btnParaPol); // Botão para converter para polegadas
        layout->addWidget(btnParaMm); // Botão para converter para milímetros
        layout->addWidget(labelResultado); // Rótulo de resultado

        // 3. Conectar os botões às funções
        connect(btnParaPol, &QPushButton::clicked, this, &JanelaConversor::aoConverterParaPol); // Liga o clique do botão à função
        connect(btnParaMm, &QPushButton::clicked, this, &JanelaConversor::aoConverterParaMm); // Liga o clique do botão à função
    }

private slots:// Funções que respondem aos cliques dos botões
    void aoConverterParaPol() {
        std::string texto = campoEntrada->text().toStdString();// Pega o texto do campo de entrada
        double mm = motor.processarEntrada(texto);// Processa o texto para obter o valor numérico em mm
        double pol = motor.mmParaPol(mm); // Converte mm para polegadas
        labelResultado->setText("Resultado: " + QString::number(pol, 'f', 4) + " pol"); // Mostra o resultado formatado com 4 casas decimais
        motor.salvarNoLog(mm, "mm", pol, "pol"); // Salva a conversão no log
    }

    void aoConverterParaMm() {
        std::string texto = campoEntrada->text().toStdString(); 
        double pol = motor.processarEntrada(texto);
        double mm = motor.polParaMm(pol);
        labelResultado->setText("Resultado: " + QString::number(mm, 'f', 4) + " mm");
        motor.salvarNoLog(pol, "pol", mm, "mm");
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Cria a aplicação Qt
    JanelaConversor janela; // Cria a janela do conversor
    janela.show(); // Mostra a janela
    return app.exec(); // Executa o loop principal da aplicação
}