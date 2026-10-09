
#ifndef CODIGO_GESTORSTREAMERS_H
#define CODIGO_GESTORSTREAMERS_H

class GestorStreamers {

private:
    class Streamer *data {};
    class Streamer *dataVista {};
    int numData;
    int numDataVista;

public:
    GestorStreamers();
    ~GestorStreamers();

    int obtenerNumData();
    void cargarNumData(int );
    int obtenerNumDataVista();
    void cargarNumDataVista(int );

    void cargarDatos();
    void mostrarMenu();
    void mostrarOpcionesMenu();
    void mostrarSubOpciones();
    void mostrarReporte(int , bool );
    void formatoReporte(const char *, bool , int );
    void mostrarDatosReporte(ostream &, int );
    void cargarDataVista(ostream &, int );
    void mostrarDatosDataVista(ostream &);

    static int comparaNumSeguidores(const void *, const void *);
    static int comparaTiempoEnStream(const void *, const void *);
    static int comparaPromEspectadores(const void *, const void *);
    static int comparaCategoria(const void *, const void *);
    static int comparaInfluencia(const void *, const void *);

    void generarReportes();

    void copiarDatos();
    void cortarDatos(int );

};

#endif //CODIGO_GESTORSTREAMERS_H
