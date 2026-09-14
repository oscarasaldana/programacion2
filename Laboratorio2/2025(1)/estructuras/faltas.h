
#ifndef CODIGO_FALTAS_H
#define CODIGO_FALTAS_H
#include "conductores.h"
#include "infracciones.h"

struct Faltas {
    Conductores conductores;
    Infracciones infracciones;

    char ***placas;
    int *capacidad;
};

#endif //CODIGO_FALTAS_H
