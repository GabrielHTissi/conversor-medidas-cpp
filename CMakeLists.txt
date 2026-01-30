cmake_minimum_required(VERSION 3.10)
project(ConversorPCP)

# Avisa o CMake para usar o Qt6 (ou Qt5, dependendo do que o brew instalou)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets sql)

# Adiciona os seus arquivos ao projeto
add_executable(ConversorPCP
    main.cpp
    conversores.cpp
    conversores.h
)

# Conecta o seu código com as bibliotecas de interface do Qt
target_link_libraries(ConversorPCP PRIVATE Qt6::Widgets Qt6::Sql)