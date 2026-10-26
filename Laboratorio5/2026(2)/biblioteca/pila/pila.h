
#ifndef CODIGO_PROCESA_H
#define CODIGO_PROCESA_H

#include "../pila/pila.h"

class Procesa {

private:
    class Pila pilaOperaciones;

public:
    Procesa();
    ~Procesa();

    void cargarOperaciones(const char *);
    void descargaOperaciones(int , int );
    void imprimeOperaciones(const char *);

};

#endif //CODIGO_PROCESA_H
