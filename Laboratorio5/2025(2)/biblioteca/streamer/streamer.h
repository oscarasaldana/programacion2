
#ifndef CODIGO_STREAMER_H
#define CODIGO_STREAMER_H

class Streamer {

private:
    char *cuenta;
    long long tiempoEnStream;
    double promEspectadores;
    long long numSeguidores;
    char *categoria;

public:
    Streamer();
    Streamer(char *, long long, double, long long, char *);
    ~Streamer();

    void obtenerCuenta(char *) const;
    void cargarCuenta(char *);
    long long obtenerTiempoStream() const;
    void cargarTiempoStream(long long );
    double obtenerPromEspectadores() const;
    void cargarPromEspectadores(double );
    long long obtenerNumSeguidores() const;
    void cargarNumSeguidores(long long );
    void obtenerCategoria(char *) const;
    void cargarCategoria(char *);

    void leerStreamer(ifstream &);
    void mostrarStreamer(ostream &);
    void copiar(class Streamer &);

};

#endif //CODIGO_STREAMER_H
