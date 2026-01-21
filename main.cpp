///meu primeiro projeto em C++, pretendo aprender o basico da linguagem e implentar alguns algoritmos simples com funcionalidades que ajudem no meu trabalho atual de PCP.

#include <iostream>//controle de entra e saida
#include <iomanip>//formatação de numeros
#include <string>//manipulação de strings
#include <algorithm>//funções de algoritmos padrão
#include <limits>//para manipulação de limites de stream

double processarEntrada(std::string texto) {
    std::replace(texto.begin(), texto.end(), ',', '.');
    return std::stod(texto);
}//função para processar a entrada do usuário, substituindo vírgulas por pontos e convertendo a string para double

int main() { 

double medidaMM, medidaPG; //ocupa o dobro de memória, mas é muito mais preciso que o float
const float CONVERSAO = 25.4;//constante de conversão de polegadas para milímetros(1 polegada = 25,4 mm)
int opcao;//variável para armazenar a opção do usuário
std::string entradaTexto;//string para armazenar a entrada do usuário

do {

std::cout << "----- CONVERSOR TECNICO PCP -----" << std::endl;
std::cout << "1 - Milimetros para polegadas" << std::endl;
std::cout << "2 - Polegadas para milimetros" << std::endl;
std::cout << "0 - Sair" << std::endl;
std::cout << "Escolhe uma opção: " << std::endl;
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
    std::cout << "saindo do pograma..." << std::endl;//mensagem de saída
    break;}

switch (opcao){
case 1: 
std::cout << "DIGITE UMA MEDIDA EM MILIMETROS: ";//solicita ao usuário que insira uma medida em milímetros
std::cin >> entradaTexto;//lê a medida em milímetros fornecida pelo usuárioS
medidaMM = processarEntrada(entradaTexto);//converte a string para double
medidaPG=medidaMM/CONVERSAO;//converte a medida de milímetros para polegadas
std::cout << "O valor em polegadas é: " << std::fixed << std::setprecision(4) << medidaPG << " pol" << std::endl;//exibe o valor convertido em polegadas com 4 casas decimais
   break;

case 2: 
std::cout << "DIGITE UMA MEDIDA EM POLEGADAS: ";//solicita ao usuário que insira uma medida em milímetros
std::cin >> entradaTexto;//lê a medida em milímetros fornecida pelo usuárioS
medidaPG = processarEntrada(entradaTexto);
medidaMM=medidaPG * CONVERSAO;//converte a medida de polegadas para milímetros
std::cout << "O valor em milimetros é: " << std::fixed << std::setprecision(4) << medidaMM << " mm" << std::endl;
    break;

default:
std::cout << "OPÇÃO INVÁLIDA. POR FAVOR, ESCOLHA 1 OU 2." << std::endl;
    break;
}
std::cout << "----------------------------------------------"<< std::endl;

 } while (opcao != 0);//loop continua até o usuário escolher sair

return 0;
}
