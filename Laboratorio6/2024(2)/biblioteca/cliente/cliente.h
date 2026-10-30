
#ifndef CODIGO_CLIENTE_H
#define CODIGO_CLIENTE_H

class Cliente {

private:
    int dni;
    char *nombre;
    char *distrito;
    double descuento;
    double totalPagado;

public:
    Cliente();
    ~Cliente();

    void cargarDni(int );
    void obtenerDni(int &) const;
    void cargarNombre(char *);
    void obtenerNombre(char *) const;
    void cargarDistrito(char *);
    void obtenerDistrito(char *) const;
    void cargarDescuento(double );
    void obtenerDescuento(double &) const;
    void cargarTotalPagado(double );
    void obtenerTotalPagado(double &) const;

};

void operator >> (ifstream &, class Cliente &);
void operator << (ofstream &, const class Cliente &);

#endif //CODIGO_CLIENTE_H
