//
// Created by Fabián Álvarez on 4/8/2018.
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

    if(datosOriginales){
        datosAcomodados = embellecedorDeProgramas->embellecerPrograma(datosOriginales);

        if(finalFlag){
            procesadorDeArchivos->escribirArchivo(nomArchivoFinal,datosAcomodados);
        }else{
            for(int i = 0; datosAcomodados[i] != 0; ++i){
                cout << datosAcomodados[i] << endl;
            }
        }

        cantidadPalabrasReservadas = analizadorDeProgramas->analizarPrograma(datosAcomodados);
        procesadorDeArchivos->escribirArchivo("Contador.txt",cantidadPalabrasReservadas);
    }

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
    int strTam = 0;

    for(int i = 1; i < nArg; ++i){
        //Este for es para revisar cada uno de los argumentos que vienen en el vector de
        //argumentos "vArg"
        comando = strtok(vArg[i]," [],");
        strTam = strlen(comando);
        if(0 == strcmp(comando,"-e")){
            ++i;
            comando = strtok (vArg[i], " [],");
            just = atoi(comando);
            justFlag = 1;
        }else{
            if(0 == strcmp(comando,"-o")){
                ++i;
                comando = strtok (vArg[i], " [],");
                strTam = strlen(comando);
                if(strTam > 4 && comando[strTam-1] == 'p' && comando[strTam-2] == 'p' && comando[strTam-3] == 'c' && comando[strTam-4] == '.'){
                    strcpy(nomArchivoFinal,comando);
                    finalFlag = 1;
                }else{
                    cout << "El tipo de archivo no es .cpp" << endl;
                    finalFlag = 0;
                }
            }else{
                if(strTam > 4 && comando[strTam-1] == 'p' && comando[strTam-2] == 'p' && comando[strTam-3] == 'c' && comando[strTam-4] == '.'){
                    strcpy(nomArchivoOriginal,comando);
                }else{
                    cout << "El tipo de archivo no es .cpp" << endl;
                }
                originalFlag = 1;
            }
        }
    }

    if(!justFlag){
        cout << "Porfvor escriba el valor para justificar: ";
        cin >> just;
    }

    embellecedorDeProgramas->setJust(just);

    if(!originalFlag){
        cout << "Porfvor escriba el nombre del archivo a leer: ";
        cin >> nomArchivoOriginal;
    }
}


