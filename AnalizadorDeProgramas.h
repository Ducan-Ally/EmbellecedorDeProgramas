//
// Created by Fabian Alvarez on 4/8/2018.
//

#ifndef EMBELLECEDORDEPROGRAMAS_ANALIZADORDEPROGRAMAS_H
#define EMBELLECEDORDEPROGRAMAS_ANALIZADORDEPROGRAMAS_H

class AnalizadorDeProgramas{
private:
    char** datosAnalizados;
    int* contadorDeKeyWords;

    int comillasFlag = 0;
    int comentariosDeLineasFag = 0;
    int comentariosFlag = 0;


public:
    AnalizadorDeProgramas();
    ~AnalizadorDeProgramas();

    char** analizarPrograma(char**);
    void analizarLinea(char*);
    void analizarPalabra(char*);
    void crearPalabrasReservadas();
    void agregarContador();
};

#endif //EMBELLECEDORDEPROGRAMAS_ANALIZADORDEPROGRAMAS_H
