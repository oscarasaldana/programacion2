
#ifndef CODIGO_MULTA_H
#define CODIGO_MULTA_H

class Multa {

private:
    char *placa;
    int fechaInfraccion;
    int fechaPago;
    int codigoInfraccion;
    double multa;

public:
    Multa();
    ~Multa();

    void cargarPlaca(char *);
    void obtenerPlaca(char *) const;
    void cargarFechaInfraccion(int );
    void obtenerFechaInfraccion(int &) const;
    void cargarFechaPago(int );
    void obtenerFechaPago(int &) const;
    void cargarCodigoInfraccion(int );
    void obtenerCodigoInfraccion(int &) const;
    void cargarMulta(double );
    void obtenerMulta(double &) const;

};

void operator >> (ifstream &, class Multa &);
void operator << (ofstream &, class Multa &);

#endif //CODIGO_MULTA_H
