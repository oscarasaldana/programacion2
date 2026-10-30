
#ifndef CODIGO_RESTAURANTE_H
#define CODIGO_RESTAURANTE_H

class Restaurante {

private:
    class Cliente *listaDeClientes;
    int numClientes;

    class Plato *listaDePlatos;
    int numPlatos;
    int capacidadPlatos;

public:
    Restaurante();
    ~Restaurante();

    void obtenerCantidadDeClientes(int &) const;
    void obtenerCantidadDePlatos(int &) const;
    void obtenerCapacidadDePlatos(int &) const;

    void operator < (const char *);
    void operator <= (const char *);
    void operator <<= (const char *);

    int encontrarPosicionCliente(int );
    int encontrarPosicionPlato(const char *);

    void operator >> (const char *);

    void encabezadoDePlatos(ofstream &);
    void encabezadoDeClientes(ofstream &);

};

#endif //CODIGO_RESTAURANTE_H
