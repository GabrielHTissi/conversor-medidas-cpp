///meu primeiro projeto em C++, pretendo aprender o basico da linguagem e implentar alguns algoritmos simples com funcionalidades que ajudem no meu trabalho atual de PCP.

#include <iostream>//controle de entra e saida
#include <iomanip>//formatação de numeros
#include <string>//manipulação de strings
#include <algorithm>//funções de algoritmos padrão
#include <limits>//para manipulação de limites de stream
#include "conversores.h"//inclusão do arquivo de cabeçalho com as funções de conversão
#include <cstdlib>//para usar o comando system("clear") ou system("cls")


int main() { 

double medidaMM, medidaPG; //ocupa o dobro de memória, mas é muito mais preciso que o float
const float CONVERSAO = 25.4;//constante de conversão de polegadas para milímetros(1 polegada = 25,4 mm)
int opcao;//variável para armazenar a opção do usuário
std::string entradaTexto;//string para armazenar a entrada do usuário
Conversor meuConversor;

do {
meuConversor.limparTela();
std::cout << "------------ CONVERSOR TECNICO PCP -----------" << std::endl;
std::cout << "1 - Milimetros para polegadas" << std::endl;
std::cout << "2 - Polegadas para milimetros" << std::endl;
std::cout << "0 - Sair" << std::endl;
std::cout << "Escolha uma opção e precione enter: " << std::endl;
std::cin >> opcao;

if (std::cin.fail()) {
    std::cin.clear(); // Limpa o estado de erro
    // Descarta tudo o que foi digitado de errado até o próximo "Enter"
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "ERRO: Entrada invalida. Digite apenas numeros." << std::endl;
    opcao = -1; // TRAVA DE SEGURANÇA: Garante que o while la embaixo nao saia do programa
    continue; // Volta para o início do loop
}
if(opcao == 0) {
    meuConversor.limparTela();
    std::cout << "saindo do pograma..." << std::endl;//mensagem de saída
    break;}

switch (opcao){
case 1: // MM para POL
    std::cout << "DIGITE MM: ";
    std::cin >> entradaTexto;
    medidaMM = meuConversor.processarEntrada(entradaTexto);
    medidaPG = meuConversor.mmParaPol(medidaMM);
    std::cout << "----------------------------------------------"<< std::endl;
    std::cout << "Resultado: " << std::fixed << std::setprecision(4) << medidaPG << " pol" << std::endl;
    meuConversor.salvarNoLog(medidaMM, "mm", medidaPG, "pol");
    break;

case 2: // POL para MM
    std::cout << "DIGITE POL: ";
    std::cin >> entradaTexto;
    medidaPG = meuConversor.processarEntrada(entradaTexto);
    medidaMM = meuConversor.polParaMm(medidaPG);
    std::cout << "----------------------------------------------"<< std::endl; 
    std::cout << "Resultado: " << std::fixed << std::setprecision(4) << medidaMM << " mm" << std::endl;
    meuConversor.salvarNoLog(medidaPG, "pol", medidaMM, "mm");
    break; // Adicionado para não cair no default
default:
std::cout << "OPÇÃO INVÁLIDA. POR FAVOR, ESCOLHA 1 OU 2." << std::endl;
    break;
}
std::cout << "----------------------------------------------"<< std::endl;

 } while (opcao != 0);//loop continua até o usuário escolher sair

return 0;
}
//g++ main.cpp conversores.cpp -o main && ./main (pra rodar no terminal)