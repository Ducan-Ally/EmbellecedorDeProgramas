//
// Created by Fabian Alvarez on 4/8/2018.
//

//
// Created by Fabian Alvarez on 4/8/2018.
//

#ifndef EMBELLECEDORDEPROGRAMAS_EMBELLECEDORDEPROGRAMAS_H
#define EMBELLECEDORDEPROGRAMAS_EMBELLECEDORDEPROGRAMAS_H

#define MAX_FILAS 500
#define MAX_COLUMNAS 300

class EmbellecedorDeProgramas{
private:
    int just = 3;
    int nivelDeJust = 0;
    int filaActual = 0;
    int columnaActual = 0;

    int parentesisFlag = 0; //Banderas para Parentesis
    int comillasFlag = 0; //Banderas para comillas
    int comentariosFlag = 0; //Bandera para comentarios
    int comentarioLineasFlag = 0; //Bandera para comentarios de mas de una linea
    int cambioDeLineaFlag = 0; //Bandera para saber que hay cambi de linea
    int terminoComLineasFlag = 0; //Bandera que indaca el final de un comentario de lineas
    int numeralFlag = 0; //Bandera que indica sí estamos tratando con un #include o #define

    char** datosAcomodados;
public:
    EmbellecedorDeProgramas();
    ~EmbellecedorDeProgramas();

    void setJust(int);

    char** embellecerPrograma(char**);
    void embellecerLinea(char*);
    void embellecerPalabra(char*);

    void ponerCaracter(char,char**,int,int);
    void justificar(char*,int&);
};

#endif //EMBELLECEDORDEPROGRAMAS_EMBELLECEDORDEPROGRAMAS_H