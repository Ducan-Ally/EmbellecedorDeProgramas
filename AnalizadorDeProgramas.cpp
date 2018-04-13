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

/*
 * param: char** con las líneas que se quiere analizar
 *
 * Func: Agarra cada línea de chars y la analiza
 *
 * Ret: char** con los datos de las palabras reservadas
 */
char** AnalizadorDeProgramas::analizarPrograma(char** datos){
    for(int i = 0; datos[i] != 0; ++i){
        analizarLinea(datos[i]);
    }
	
	agregarContador();
    return datosAnalizados;
}

/*
 * param: char*  línea que se quiere analizar
 *
 * Func: Separa la línea dejando solo las palabras que no contengan caracteres
 * especiales, esto con el propósito de simplificar la lectura de las palabras
 * reservadas
 */
void AnalizadorDeProgramas::analizarLinea(char* linea){
    char* token = strtok(linea," ();,=<>+-{}[]\n\r");
    //Pide el primer token que no contenga esos símbolos

    while(token != NULL && int(token[0]) != 13){
        analizarPalabra(token);
        token = strtok(NULL," ();,=<>+-{}[]\n\r");
        //Pide el siguiente token en la línea
    }

    comentariosFlag = 0;
}

/*
 * param: char* con la palabra que se va a analizar, se puede tomar por palabra un conjunto de caracteres
 *
 * Func: Revisa sí la palabra es o no una palabra reservada, de ser así aumenta su contador correspondiente
 */
void AnalizadorDeProgramas::analizarPalabra(char* palabra){
    int strTam = strlen(palabra);
    int banderaPalabraRes = 1;
    if(strTam > 1 && !comillasFlag && !comentariosDeLineasFag && !comentariosFlag){
	//La palabra se puede analizar sí no tiene ninguna bandera activa, pues las banderas indican 
	//sí hay o no que ignorar la palabra
	//También debe ser mayor a uno, pues la palabra reservada más pequeña es de tamaño dos
        if(palabra[0] == '/'){
            if(palabra[1] == '/'){
			//Quiere decir que es un comentario de una línea
                comentariosFlag = 1;
            }else{
                if(palabra[1] == '*'){
				//Quiere decir que es un comentario de varias líneas
                    comentariosDeLineasFag = 1;
                }
            }
        }else{
            if(palabra[0] == '"'){
			//Quiere decir que es el comienzo de un string
                comillasFlag = 1;
            }else{
                for(int i = 0; datosAnalizados[i] != 0; ++i){
				//Recorremos el vector de palabras reservadas
                    if(strstr (palabra,datosAnalizados[i]) && strTam <= strlen(datosAnalizados[i])+2){
					//Si encuentra la palabra reservada en la palabra que recibe como parámetro se cuenta
					//El más dos es para considerar sí el caraacter especial es un puntero "char**" o ese tipo de casos
                        ++contadorDeKeyWords[i];
                    }
                }
            }
        }
    }

    if(comillasFlag && palabra[strTam-1] == '"'){
	//Implica que encontró una comilla, que es candidata a ser el fin de un string
        if(strTam > 1){
		//Verifica que sí es solo el " es final de string, sí no debe considerar lo que viene antes
            if(palabra[strTam-2] != '\\'){
			//Sí el caracter anterior al " no es un \ quiere decir que es el final del string
                comillasFlag = 0;
            }
        }else{
            comillasFlag = 0;
        }
    }

    if(comentariosDeLineasFag && strTam > 1){
	//Pregunta sí la palabra tiene un tamaño mayor a un pues el indicador de final
	//de comentario de líneas es */
        if(palabra[strTam-1] == '/' && palabra[strTam-2] == '*'){
		//Implica que lo que encontró sí es el final de un comentario de líneas
            comentariosDeLineasFag = 0;
        }
    }
}

/*
 * Func: Carga todas las palabras reservadas en un vector
 */
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
    datosAnalizados[63] = 0;
}

/*
 * Func: Concatena cada palabra reservada con su contador
 */
void AnalizadorDeProgramas::agregarContador(){
	for(int i = 0; datosAnalizados[i] != 0; ++i){
		strcat(datosAnalizados[i],": ");
		strcat(datosAnalizados[i],std::to_string(contadorDeKeyWords[i]).c_str());
	}
}
