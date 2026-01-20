///meu primeiro projeto em C++, pretendo aprender o basico da linguagem e implentar 
//alguns algoritmos simples com funcionalidades que ajudem no meu trabalho atual de PCP.


#include <iostream>//controle de entra e saida
#include <iomanip>//formatação de numeros
#include <string>//manipulação de strings


int main() { 

double medidaMM, medidaPG; //ocupa o dobro de memória, mas é muito mais preciso que o float
const float CONVERSAO = 25.4;//constante de conversão de polegadas para milímetros(1 polegada = 25,4 mm)

std::cout <<"DIGITE UMA MEDIDA EM MILÍMETROS: ";//solicita ao usuário que digite uma medida em milímetros
std::cin >> medidaMM;//lê a medida em milímetros fornecida pelo usuárioS
std::setprecision(4);//define a precisão dos números exibidos

medidaPG=medidaMM/CONVERSAO;//converte a medida de milímetros para polegadas
std::cout << "O valor em polegadas é: " << std::fixed << std::setprecision(4) << medidaPG << " pol" << std::endl;//exibe o valor convertido em polegadas com 4 casas decimais





return 0;
}
