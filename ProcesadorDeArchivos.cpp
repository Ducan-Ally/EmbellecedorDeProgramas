//
// Created by Fabián Álvarez 4/8/2018.
//

#include "ProcesadorDeArchivos.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

ProcesadorDeArchivos::ProcesadorDeArchivos(){
}

ProcesadorDeArchivos::~ProcesadorDeArchivos(){
}

/*
 * param: char* contiene el nombre del archivo que vamos a leer
 *
 * Func: abre un archivo cuya información es transcribida a memoria, para poder ser usada después
 *
 * Ret: el puntero en donde la datos están guardada
 */
char** ProcesadorDeArchivos::leerArchivo(const char* nomArchivo){
    int nLineas;
    char** datos = 0;
    int tamLinea;
    string linea;

    ifstream archivo(nomArchivo);
    if(archivo.is_open()){
        while (!archivo.eof()){
        //Contamos el número de lineas que tiene el archivo, para poder crear un puntero con el
        //espacio suficiente para guardar la información del archivo
            getline(archivo,linea);
            nLineas++;
        }
        archivo.clear();
        archivo.seekg(0); //Regresamos a la primera línea del achivo

        datos = new char* [nLineas+1]; //creamos el puntero capaz de guardar la información del archivo
        for(int i = 0; i < nLineas; ++i){
            getline(archivo,linea);
            tamLinea = linea.length();
            datos[i] = new char [tamLinea+1]; //creamos el espacio en memoria que va a guardar la línea actual del archivo

            for(int e = 0; e < tamLinea; ++e){
            //Copiamos los datos del archivo a memoria
                datos[i][e] = linea[e];
            }

            datos[i][tamLinea] = '\0'; //nos permite saber donde es que termina la hilera de caracteres
        }
        datos[nLineas] = 0; //nos permite saber donde es que termina el vector que contiene las hileras de caracteres
        archivo.close();
    }else{
        cerr << "El archivo no se abrio correctamente" << endl;
    }

    return datos;
}

/*
 * param: char* con el nombre del archivo a crear
 * param: char** con la información que se va a guardar en el archivo
 *
 * Func: copia la información de memoria a el archivo que se creó
 */
void ProcesadorDeArchivos::escribirArchivo(const char* nomArchivo, char** datos){
    int nLinea = 0;
    ofstream archivo ( nomArchivo , ios::out);
    while (datos[nLinea] != 0){
        archivo << datos[nLinea] << endl; //copiamos la línea actual de datos a el archivo que se creó
        ++nLinea;
    }
}