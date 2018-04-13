//
// Created by fakeb on 4/8/2018.
//

#include "Aplicacion.h"

#include <iostream>
#include <cstring>

using namespace std;

Aplicacion::Aplicacion(){
    procesadorDeArchivos = new ProcesadorDeArchivos();
    embellecedorDeProgramas = new EmbellecedorDeProgramas();
    analizadorDeProgramas = new AnalizadorDeProgramas();
    just = 3;
    nomArchivoOriginal =  new char [MAX_LENGTH];
    nomArchivoFinal = new char [MAX_LENGTH];
}

Aplicacion::~Aplicacion(){
    delete procesadorDeArchivos;
    delete embellecedorDeProgramas;
}

/*
 * param: int con el número de argunmentos escritos desde la consola
 * param: char** con la lista de argumentos escritos desde la consola
 *
 * Func: es el encargado de ejecutar el programa
 */
void Aplicacion::ejecutar(int nArg, char** vArg){
    separadorDeComandos(nArg,vArg);
    datosOriginales = procesadorDeArchivos->leerArchivo(nomArchivoOriginal);
    datosAcomodados = embellecedorDeProgramas->embellecerPrograma(datosOriginales);
    analizadorDeProgramas->analizarPrograma(datosAcomodados);
    //Realiza el analisis
    //Crea nuevos archivos
    //Termina
}

/*
 * param: int con el número de argumentos escritos desde la línea de comandos
 * param: char** con la lista de argumentos escritos desde la línea de comandos
 *
 * Func: Se encarga de asociar los comandos a su función correspondiente, permitiendo poder
 * usar estos luego.
 */
void Aplicacion::separadorDeComandos(int nArg, char** vArg){
    char* comando;

    for(int i = 1; i < nArg; ++i){
    //Este for es para revisar cada uno de los argumentos que vienen en el vector de
    //argumentos "vArg"
        comando = strtok(vArg[i]," [],");
        if(0 == strcmp(comando,"-e")){
            ++i;
            comando = strtok (vArg[i], " [],");
            just = atoi(comando);
            justFlag = 1;
        }else{
            if(0 == strcmp(comando,"-o")){
                ++i;
                comando = strtok (vArg[i], " [],");
                strcpy(nomArchivoFinal,comando);

                finalFlag = 1;
            }else{
                strcpy(nomArchivoOriginal,comando);
                originalFlag = 1;
            }
        }
    }

    if(!justFlag){
        cout << "Porfvor escriba el valor para justificar: ";
        cin >> just;
    }

    if(!originalFlag){
        cout << "Porfvor escriba el nombre del archivo a leer: ";
        cin >> nomArchivoOriginal;
    }

    if(!finalFlag){
        cout << "Porfvor escriba el nombre del archivo en el que vamos a escribir: ";
        cin >> nomArchivoFinal;
    }
}


