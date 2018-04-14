//
// Created by Fabian Alvarez on 4/8/2018.
//

//
// Created by Fabian Alvarez on 4/8/2018.
//

#ifndef EMBELLECEDORDEPROGRAMAS_APLICACION_H
#define EMBELLECEDORDEPROGRAMAS_APLICACION_H

#define MAX_LENGTH 20

#include "ProcesadorDeArchivos.h"
#include "EmbellecedorDeProgramas.h"
#include "AnalizadorDeProgramas.h"

class Aplicacion{
private:
    ProcesadorDeArchivos* procesadorDeArchivos;
    EmbellecedorDeProgramas* embellecedorDeProgramas;
    AnalizadorDeProgramas* analizadorDeProgramas;

    int just;
    char* nomArchivoOriginal = 0;
    char* nomArchivoFinal = 0;
    char** datosAcomodados = 0;
    char** datosOriginales = 0;
    char** cantidadPalabrasReservadas = 0;

    int originalFlag = 0; //Bandera que indica si en los parametros viene el nombre del archivo Original
    int finalFlag = 0; //Bandera que indica si en los parametros viene el nombre del archivo Final
    int justFlag = 0; //Bansdera que indeica si en los parametros viene la justificacion
public:
    Aplicacion();
    ~Aplicacion();
    void ejecutar(int,char**);
    void separadorDeComandos(int,char**);
};

#endif //EMBELLECEDORDEPROGRAMAS_APLICACION_H
