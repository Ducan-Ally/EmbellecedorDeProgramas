//
// Created by Fabian Alvarez on 4/8/2018.
//

#include "EmbellecedorDeProgramas.h"
#include <iostream>
#include <cstring>

using namespace std;

EmbellecedorDeProgramas::EmbellecedorDeProgramas(){
    cout << "Construyendo Analizador de Programas" << endl;
    datosAcomodados = new char* [MAX_FILAS];
    for(int i = 0; i < MAX_FILAS; ++i){
        datosAcomodados[i] = new char [MAX_COLUMNAS];
    }
}

EmbellecedorDeProgramas::~EmbellecedorDeProgramas(){
    cout << "Destruyendo Analizador de Programas" << endl;
}

/*
 * param: char** con las líneas que se quiere embellecer
 *
 * Func: Agarra cada línea de chars y la embellece
 *
 * Ret: char** con la las líneas embellecidas
 */
char** EmbellecedorDeProgramas::embellecerPrograma(char** datos){
    for(int i = 0; datos[i] != 0; ++i){
        embellecerLinea(datos[i]);
    }

    datosAcomodados[filaActual] = 0;

    return datosAcomodados;
}

/*
 * param: char*  línea que se quiere embellecer
 *
 * Func: controla sí hay cambio de líneas o no en la línea embellecida o sí es
 * más bien debe seguir en la misma línea, además envpia a embellecer las las
 * diferentes partes de la oración
 */
void EmbellecedorDeProgramas::embellecerLinea(char* linea){
    char* token = strtok(linea," \n\r");

    while(token != NULL){
        embellecerPalabra(token);
        token = strtok(NULL," \n\r");

        if(token != NULL){
        //Quiere deci que aún hay tokens por leer en la línea
            if(cambioDeLineaFlag){
                if(token[0] != '/'){
                //Se sabe que lo que sigue no es un comentario
                //Por lo que se debe realizar el cambio de linea
                    ponerCaracter(char(13),datosAcomodados,filaActual,columnaActual);
                    ++columnaActual;
                    ponerCaracter('\0',datosAcomodados,filaActual,columnaActual);
                    ++filaActual;
                    columnaActual = 0;
                    justificar(datosAcomodados[filaActual],columnaActual);
                }else{
                //Lo que sigue es un comentario, entonces no se hace cambio de línea
                //si no que se hace hasta que el comentario termine
                    ponerCaracter(' ',datosAcomodados,filaActual,columnaActual);
                    ++columnaActual;
                }
                cambioDeLineaFlag = 0;
            }else{
            //No hay cambio de línea por lo que simplemente debe separar la siguente palabra de la actual
                ponerCaracter(' ',datosAcomodados,filaActual,columnaActual);
                ++columnaActual;
            }

        }else{
        //Se acabó la línea, entonces hay que ver sí se debe o no hacer un salto de línea
            if(terminoComLineasFlag || cambioDeLineaFlag || comentariosFlag || comentarioLineasFlag || numeralFlag){
            //Sí una de esas baneras está activada se debe realizar un cambio de línea
                ponerCaracter(char(13),datosAcomodados,filaActual,columnaActual);
                ++columnaActual;
                ponerCaracter('\0',datosAcomodados,filaActual,columnaActual);
                ++filaActual;
                columnaActual = 0;
                justificar(datosAcomodados[filaActual],columnaActual);

                terminoComLineasFlag = 0;
                comentariosFlag = 0;
                cambioDeLineaFlag = 0;
                numeralFlag = 0;
            }else{
            //Ninguna bandera está activa, por lo que no hay que gacer ningún cambio de línea
                ponerCaracter(' ',datosAcomodados,filaActual,columnaActual);
                ++columnaActual;
            }
        }
    }

    terminoComLineasFlag = 0;
    comentariosFlag = 0;
    cambioDeLineaFlag = 0;
}

/*
 * param: char* con la palabra que se va a embellecer, se puede tomar por palabra un conjunto de caracteres
 *
 * Func: Analiza cada char de la palbra y activa o desactiva banderas dependiendo del char que encuentra.
 * Finaliza copiando la palabra
 */
void EmbellecedorDeProgramas::embellecerPalabra(char* palabra){
    if(!strcmp(palabra,"#include") || !strcmp(palabra,"#define")){
        numeralFlag = 1;
    }

    for(int i = 0; palabra[i] != '\0' && int(palabra[i]) != 13; ++i){
        if(palabra[i] == '/' && !comentarioLineasFlag && !comentariosFlag && !comillasFlag){
        //Activacion de banderas para el caso de comentarios
            if(palabra[i+1] == '/'){
            //Caso para los comentarios de una linea
                comentariosFlag = 1;
            }else{
                if(palabra[i+1] == '*'){
                //Caso para los omentarios de varias lineas
                    comentarioLineasFlag = 1;
                }
            }
        }

        if(palabra[i] == '"'){
            if(i == 0 || palabra[i-1] != '\\'){
            //Preguntamos sí es un posible indicador de string
                if(comillasFlag) {
                //Desactivación de bandera string, pues aquí termina un string
                    comillasFlag = 0;
                }else{
                    if(!comentarioLineasFlag && !comentariosFlag && !numeralFlag){
                    //Activación de bandera string, pues aquí comienza un string
                        comillasFlag = 1;
                    }
                }
            }
        }

        if(comentarioLineasFlag && palabra[i] == '*') {
        //Preguntamos sí este es un posible fin de comentario de varias líneas
            if (palabra[i + 1] == '/') {
            //Desactivar bandera de comentarios en varias lineas
                comentarioLineasFlag = 0;
                terminoComLineasFlag = 1;
            }
        }

        if((palabra[i] == '(' || palabra[i] == '[') && !comentariosFlag && !comentarioLineasFlag && !comillasFlag){
        //Activacion de la bandera para parentesis
            ++parentesisFlag;
        }

        if((palabra[i] == ')' || palabra[i] == ']') && !comentariosFlag && !comentarioLineasFlag && !comillasFlag){
        //Desactivacion de la bandera para parentesis
            --parentesisFlag;
        }

        if(palabra[i] == '{' && !comentariosFlag && !comentarioLineasFlag && !comillasFlag){
        //Agregado de justificacion
        //Activación del cambio de línea
            ++nivelDeJust;
            cambioDeLineaFlag = 1;
        }

        if(palabra[i] == '}' && !comentariosFlag && !comentarioLineasFlag && !comillasFlag){
        //Desagregado de justificacion
        //Activación del cambio de línea
            --nivelDeJust;
            columnaActual -= just;
            cambioDeLineaFlag = 1;
        }

        if(palabra[i] == ';' && !parentesisFlag && !comentariosFlag && !comentarioLineasFlag && !comillasFlag){
        //Activación del cambio de línea
            cambioDeLineaFlag = 1;
        }

        if(palabra[i] != '\0'){
            ponerCaracter(palabra[i],datosAcomodados,filaActual,columnaActual);
            ++columnaActual;
        }
    }
}

/*
 * param: char caracter que vamos a poner
 * param: char** lugar en donde vams a colocar el char
 * param: int que indica en que fila del lugar
 * param: int que indica en que columna del lugar
 *
 * Func: coloca caracteres en la posición que se le indique
 */
void EmbellecedorDeProgramas::ponerCaracter(char caracter, char ** lineasDeChar, int fila, int columna){
    lineasDeChar[fila][columna] = caracter;
}

/*
 * param: char* linea a justificar
 * param: int posición donde comienza la justificación
 *
 * Func: justificar líneas
 */
void EmbellecedorDeProgramas::justificar(char* linea, int& pos){
    for(int i = 0; i < nivelDeJust*just; ++i){
        linea[pos+i] = ' ';
    }
    pos += nivelDeJust*just;
}
