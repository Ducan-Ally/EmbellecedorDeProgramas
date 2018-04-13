//Para compilar g++ main.cpp Aplicacion.cpp AnalizadorDeProgramas.cpp ProcesadorDeArchivos.cpp

#include "Aplicacion.h"

#include <iostream>

int main(int nArg, char** vArg) {
    Aplicacion aplicacion;
    aplicacion. ejecutar(nArg,vArg);
    return 0;
}