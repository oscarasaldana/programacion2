
#ifndef CODIGO_MINISTERIO_H
#define CODIGO_MINISTERIO_H

#include "../infraccion/infraccion.h"
#include "../empresa/empresa.h"

class Ministerio {

private:
    class Infraccion *listaDeInfracciones;
    int numInfracciones;

    class Empresa listaDeEmpresas[50];
    int numEmpresas;

public:
    Ministerio();
    ~Ministerio();

    void obtenerNumInfracciones(int &) const;
    void obtenerNumEmpresas(int &) const;
    int encontrarPosicionInfraccion(int );
    int encontrarPosicionEmpresa(char *);

    void operator < (const char *);
    void operator <= (const char *);
    void operator <<= (const char *);
    void operator >> (const char *);

    void encabezadoTablaInfracciones(ofstream &);
    void encabezadoListaDeMultas(ofstream &);

};

#endif //CODIGO_MINISTERIO_H
