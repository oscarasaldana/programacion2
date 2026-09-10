
#ifndef SOLUCION_FALTAS_H
#define SOLUCION_FALTAS_H

struct Faltas {
    struct Conductores conductores {};
    struct Infracciones infracciones {};
    char ***placa {};
    int *capacidades {};
};

#endif //SOLUCION_FALTAS_H
