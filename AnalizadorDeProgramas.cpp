//
// Created by Fabian Alvarez on 4/8/2018.
//

#include "AnalizadorDeProgramas.h"

#include <iostream>
#include <cstring>

using namespace std;

AnalizadorDeProgramas::AnalizadorDeProgramas(){
    crearPalabrasReservadas();
}

AnalizadorDeProgramas::~AnalizadorDeProgramas(){
}

char** AnalizadorDeProgramas::analizarPrograma(char** datos){
    for(int i = 0; datos[i] != '\0'; ++i){
        analizarLinea(datos[i]);
    }

    return datosAnalizados;
}

void AnalizadorDeProgramas::analizarLinea(char* linea){
    char* token = strtok(linea," ();,=<>+-{}[]\n\r");

    while(token != NULL && int(token[0]) != 13){
        analizarPalabra(token);
        token = strtok(NULL," ();,=<>+-{}[]\n\r");
    }

    comentariosFlag = 0;
}

void AnalizadorDeProgramas::analizarPalabra(char* palabra){
    int strTam = strlen(palabra);
    int banderaPalabraRes = 1;
    if(strTam > 1 && !comillasFlag && !comentariosDeLineasFag && !comentariosFlag){
        if(palabra[0] == '/'){
            if(palabra[1] == '/'){
                comentariosFlag = 1;
            }else{
                if(palabra[1] == '*'){
                    comentariosDeLineasFag = 1;
                }
            }
        }else{
            if(palabra[0] == '"'){
                comillasFlag = 1;
            }else{
                for(int i = 0; datosAnalizados[i] != '\0'; ++i){
                    if(!strcmp(palabra,datosAnalizados[i])){
                        ++contadorDeKeyWords[i];
                        cout << datosAnalizados[i] << ":" << contadorDeKeyWords[i] << endl;
                    }
                }
            }
        }
    }

    if(comillasFlag && palabra[strTam-1] == '"'){
        if(strTam > 1){
            if(palabra[strTam-2] != '\\'){
                comillasFlag = 0;
            }
        }else{
            comillasFlag = 0;
        }
    }

    if(comentariosDeLineasFag && strTam > 1){
        if(palabra[strTam-1] == '/' && palabra[strTam-2] == '*'){
            comentariosDeLineasFag = 0;
        }
    }
}

void AnalizadorDeProgramas::crearPalabrasReservadas(){
    datosAnalizados = new char*[64];
    contadorDeKeyWords = new int[63];

    for(int i = 0; i < 64; ++i){
        datosAnalizados[i] = new char[30];
    }

    strcpy(datosAnalizados[0],"register");
    strcpy(datosAnalizados[1],"reinterpret_cast");
    strcpy(datosAnalizados[2],"return");
    strcpy(datosAnalizados[3],"short");
    strcpy(datosAnalizados[4],"signed");
    strcpy(datosAnalizados[5],"sizeof");
    strcpy(datosAnalizados[6],"static");
    strcpy(datosAnalizados[7],"static_cast");
    strcpy(datosAnalizados[8],"struct");
    strcpy(datosAnalizados[9],"switch");
    strcpy(datosAnalizados[10],"template");
    strcpy(datosAnalizados[11],"this");
    strcpy(datosAnalizados[12],"throw");
    strcpy(datosAnalizados[13],"true");
    strcpy(datosAnalizados[14],"try");
    strcpy(datosAnalizados[15],"typedef");
    strcpy(datosAnalizados[16],"typeid");
    strcpy(datosAnalizados[17],"typename");
    strcpy(datosAnalizados[18],"union");
    strcpy(datosAnalizados[19],"unsigned");
    strcpy(datosAnalizados[20],"using");
    strcpy(datosAnalizados[21],"virtual");
    strcpy(datosAnalizados[22],"void");
    strcpy(datosAnalizados[23],"volatile");
    strcpy(datosAnalizados[24],"wchar_t");
    strcpy(datosAnalizados[25],"while");
    strcpy(datosAnalizados[26],"asm");
    strcpy(datosAnalizados[27],"auto");
    strcpy(datosAnalizados[28],"bool");
    strcpy(datosAnalizados[29],"break");
    strcpy(datosAnalizados[30],"case");
    strcpy(datosAnalizados[31],"catch");
    strcpy(datosAnalizados[32],"char");
    strcpy(datosAnalizados[33],"class");
    strcpy(datosAnalizados[34],"const");
    strcpy(datosAnalizados[35],"const_cast");
    strcpy(datosAnalizados[36],"continue");
    strcpy(datosAnalizados[37],"default");
    strcpy(datosAnalizados[38],"delete");
    strcpy(datosAnalizados[39],"do");
    strcpy(datosAnalizados[40],"double");
    strcpy(datosAnalizados[41],"dynamic_cast");
    strcpy(datosAnalizados[42],"else");
    strcpy(datosAnalizados[43],"enum");
    strcpy(datosAnalizados[44],"explicit");
    strcpy(datosAnalizados[45],"export");
    strcpy(datosAnalizados[46],"extern");
    strcpy(datosAnalizados[47],"false");
    strcpy(datosAnalizados[48],"float");
    strcpy(datosAnalizados[49],"for");
    strcpy(datosAnalizados[50],"friend");
    strcpy(datosAnalizados[51],"goto");
    strcpy(datosAnalizados[52],"if");
    strcpy(datosAnalizados[53],"inline");
    strcpy(datosAnalizados[54],"int");
    strcpy(datosAnalizados[55],"long");
    strcpy(datosAnalizados[56],"mutable");
    strcpy(datosAnalizados[57],"namespace");
    strcpy(datosAnalizados[58],"new");
    strcpy(datosAnalizados[59],"operator");
    strcpy(datosAnalizados[60],"private");
    strcpy(datosAnalizados[61],"protected");
    strcpy(datosAnalizados[62],"public");
    datosAnalizados[63] = '\0';
}