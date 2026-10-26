
#ifndef CODIGO_PILA_H
#define CODIGO_PILA_H

#include "../operacion/operaciones.h"

class Pila {

private:
    class Operaciones arrPila[900];
    int cantidad;

public:
    Pila();
    ~Pila();

    int obtenerCantidad();
    void apilar(class Operaciones &);
    void desapilar();
    bool esPilaVacia();
    int cima();
    void mostrarDatos(ofstream &);

};

#endif //CODIGO_PILA_H

