
#ifndef CODIGO_INFRACCION_H
#define CODIGO_INFRACCION_H

class Infraccion {

private:
    int codigo;
    char *descripcion;
    char *gravedad;
    double multa;

public:
    Infraccion();
    ~Infraccion();

    void cargarCodigo(int );
    void obtenerCodigo(int &) const;
    void cargarDescripcion(char *);
    void obtenerDescripcion(char *) const;
    void cargarGravedad(char *);
    void obtenerGravedad(char *) const;
    void cargarMulta(double );
    void obtenerMulta(double &) const;

};

void operator >> (ifstream &, class Infraccion &);
void operator << (ofstream &, class Infraccion &);

#endif //CODIGO_INFRACCION_H
