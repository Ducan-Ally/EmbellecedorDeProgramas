//
// Created by fakeb on 4/8/2018.
//

#ifndef EMBELLECEDORDEPROGRAMAS_PROCESADORDEARCHIVOS_H
#define EMBELLECEDORDEPROGRAMAS_PROCESADORDEARCHIVOS_H

class ProcesadorDeArchivos{
    private:

    public:
        ProcesadorDeArchivos();
        ~ProcesadorDeArchivos();
        char** leerArchivo(const char*);
        void escribirArchivo(const char*,char**);
};

#endif //EMBELLECEDORDEPROGRAMAS_PROCESADORDEARCHIVOS_H
