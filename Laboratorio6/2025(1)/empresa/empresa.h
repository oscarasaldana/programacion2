
#ifndef CODIGO_EMPRESA_H
#define CODIGO_EMPRESA_H

#include "../multa/multa.h"

class Empresa {

private:
    int dni;
    char *nombre;
    char *placas[10] {};
    int numPlacas;

    class Multa listaDeMultas[100];
    int numMultas;

public:
    Empresa();
    ~Empresa();

    void cargarDni(int );
    void obtenerDni(int &) const;
    void cargarNombre(char *);
    void obtenerNombre(char *) const;
    void cargarPlaca(const char *);
    void obtenerPlaca(char *, int ) const;
    void obtenerNumPlacas(int &) const;
    void obtenerNumMultas(int &) const;

    void operator += (class Multa &);

    void imprimirListaDeMultas(ofstream &, int );

};

void operator >> (ifstream &, class Empresa &);
void operator << (ofstream &, class Empresa &);

#endif //CODIGO_EMPRESA_H
