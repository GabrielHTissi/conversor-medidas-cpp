# Conversor Técnico PCP

Este projeto foi desenvolvido para facilitar a conversão de medidas técnicas no setor de PCP, saindo de um script de terminal para uma aplicação desktop robusta.

## 🚀 Evolução do Projeto
O projeto passou por três fases principais de engenharia:
1. **Procedural:** Script básico de conversão no terminal.
2. **Modular & POO:** Separação de lógica em arquivos `.h` e `.cpp` e uso de Classes.
3. **GUI (Qt):** Implementação de interface gráfica profissional e persistência de dados (logs).

## 🛠️ Tecnologias Utilizadas
- **Linguagem:** C++20
- **Framework:** Qt 6 (Widgets)
- **Build System:** CMake
- **Versionamento:** Git/GitHub

## 📐 Lógica de Engenharia
As conversões utilizam precisão de ponto flutuante duplo (double) para garantir a integridade das peças:
- Milímetros para Polegadas: $$medidaPG = \frac{medidaMM}{25.4}$$
- Polegadas para Milímetros: $$medidaMM = medidaPG \cdot 25.4$$

## 📋 Funcionalidades
- [x] Interface Gráfica Intuitiva.
- [x] Tratamento de entradas (vírgula por ponto automático).
- [x] Log de histórico de conversões em arquivo `.txt`.
- [x] Arquitetura Orientada a Objetos para fácil manutenção.