
#ifndef SOLUCION_INFRACCIONES_H
#define SOLUCION_INFRACCIONES_H

struct Infracciones {
    int *codigo;
    char **descripciones;
    char **tipos;
    double *valores;
    int cantidad;
};

#endif //SOLUCION_INFRACCIONES_H
