///meu primeiro projeto em C++, pretendo aprender o basico da linguagem e implentar alguns algoritmos simples com funcionalidades que ajudem no meu trabalho atual de PCP.

#include <iostream>//controle de entra e saida
#include <iomanip>//formatação de numeros
#include <string>//manipulação de strings
#include <algorithm>//funções de algoritmos padrão

int main() { 

double medidaMM, medidaPG; //ocupa o dobro de memória, mas é muito mais preciso que o float
const float CONVERSAO = 25.4;//constante de conversão de polegadas para milímetros(1 polegada = 25,4 mm)
int opcao;//variável para armazenar a opção do usuário
std::string entradaTexto;//string para armazenar a entrada do usuário

std::cout << "----- CONVERSOR TECNICO PCP -----" << std::endl;
std::cout << "1 - Milimetros para polegadas" << std::endl;
std::cout << "2 - Polegadas para milimetros" << std::endl;
std::cout << "Escolhe uma opção: " << std::endl;
std::cin >> opcao;

switch (opcao){
case 1: 
std::cout << "DIGITE UMA MEDIDA EM MILIMETROS: ";//solicita ao usuário que insira uma medida em milímetros
std::cin >> entradaTexto;//lê a medida em milímetros fornecida pelo usuárioS
std::setprecision(4);//define a precisão dos números exibidos/* code */
std::replace(entradaTexto.begin(), entradaTexto.end(), ',', '.');//substitui vírgulas por pontos na string de entrada para garantir a conversão correta
medidaMM = std::stod(entradaTexto);
medidaPG=medidaMM/CONVERSAO;//converte a medida de milímetros para polegadas
std::cout << "O valor em polegadas é: " << std::fixed << std::setprecision(4) << medidaPG << " pol" << std::endl;//exibe o valor convertido em polegadas com 4 casas decimais
   break;

case 2: 
std::cout << "DIGITE UMA MEDIDA EM POLEGADAS: ";//solicita ao usuário que insira uma medida em milímetros
std::cin >> entradaTexto;//lê a medida em milímetros fornecida pelo usuárioS
std::setprecision(4);//define a precisão dos números exibidos* code */
std::replace(entradaTexto.begin(), entradaTexto.end(), ',', '.');//substitui vírgulas por pontos na string de entrada para garantir a conversão correta
medidaPG = std::stod(entradaTexto);
medidaMM=medidaPG * CONVERSAO;//converte a medida de polegadas para milímetros
std::cout << "O valor em milimetros é: " << std::fixed << std::setprecision(4) << medidaMM << " mm" << std::endl;
    break;

default:
    break;
}


return 0;
}
