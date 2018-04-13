cmake_minimum_required(VERSION 3.10)
project(EmbellecedorDeProgramas)

set(CMAKE_CXX_STANDARD 11)

add_executable(EmbellecedorDeProgramas main.cpp Aplicacion.cpp Aplicacion.h ProcesadorDeArchivos.cpp ProcesadorDeArchivos.h EmbellecedorDeProgramas.cpp AnalizadorDeProgramas.cpp AnalizadorDeProgramas.h EmbellecedorDeProgramas.h)