
#ifndef CODIGO_PLATO_H
#define CODIGO_PLATO_H

class Plato {

private:
    char *codigo;
    char *nombre;
    double precio;
    char *categoria;
    int preparados;
    double descuento;
    int atendidos;
    int noAtendidos;
    double totalBruto;
    double totalEsperado;
    double totalNeto;

public:
    Plato();
    ~Plato();

    void cargarCodigo(char *);
    void obtenerCodigo(char *) const;
    void cargarNombre(char *);
    void obtenerNombre(char *) const;
    void cargarPrecio(double );
    void obtenerPrecio(double &) const;
    void cargarCategoria(char *);
    void obtenerCategoria(char *) const;
    void cargarPreparados(int );
    void obtenerPreparados(int &) const;
    void cargarDescuento(double );
    void obtenerDescuento(double &) const;
    void cargarAtendidos(int );
    void obtenerAtendidos(int &) const;
    void cargarNoAtendidos(int );
    void obtenerNoAtendidos(int &) const;
    void cargarTotalEsperado(double );
    void obtenerTotalEsperado(double &) const;
    void cargarTotalBruto(double );
    void obtenerTotalBruto(double &) const;
    void cargarTotalNeto(double );
    void obtenerTotalNeto(double &) const;

};

void operator >> (ifstream &, class Plato &);
void operator << (ofstream &, const class Plato &);

#endif //CODIGO_PLATO_H
