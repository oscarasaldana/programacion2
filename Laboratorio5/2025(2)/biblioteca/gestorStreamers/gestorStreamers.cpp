#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

#include "../streamer/streamer.h"
#include "../gestorStreamers/gestorStreamers.h"

GestorStreamers::GestorStreamers() {

    data = new Streamer [300];
    dataVista = new Streamer [300];
    numData = 0;
    numDataVista = 0;

}

GestorStreamers::~GestorStreamers() {

    delete [] data;
    delete [] dataVista;

}

int GestorStreamers::obtenerNumData() {

    return numData;

}

void GestorStreamers::cargarNumData(int dato) {

    this->numData = dato;

}

int GestorStreamers::obtenerNumDataVista() {

    return numDataVista;

}

void GestorStreamers::cargarNumDataVista(int dato) {

    this->numDataVista = dato;

}

void GestorStreamers::cargarDatos() {

    ifstream arch;

    arch.open("CarpetaDeDatos/streamers.csv",ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo streamers.csv" << endl;
        exit(1);
    }

    numData = 0;
    while (true) {
        data[numData].leerStreamer(arch);
        if (arch.eof()) break;
        numData++;
    }

}

void GestorStreamers::mostrarMenu() {

    int opcionNum;
    char opcion;

    while (true) {
        mostrarOpcionesMenu();
        cin >> opcion;
        switch (opcion) {
            case 'a':
                cargarDatos();
                break;
            case 'b':
                mostrarSubOpciones();
                cin >> opcionNum;
                mostrarReporte(opcionNum,false);
                break;
            case 'c':
                mostrarSubOpciones();
                cin >> opcionNum;
                mostrarReporte(opcionNum,true);
                break;
            case 'd':
                generarReportes();
                break;
            case 'e':
                return;
        }
    }

}

void GestorStreamers::mostrarOpcionesMenu() {

    cout << "Seleccione alguna de las siguientes opciones: " << endl;
    cout << "a) CargarDatos" << endl;
    cout << "b) Mostrar reporte" << endl;
    cout << "c) Generar reporte" << endl;
    cout << "d) Generar todos los reportes" << endl;
    cout << "e) Terminar" << endl;

}

void GestorStreamers::mostrarSubOpciones() {

    cout << "Elige algunas de las siguientes sub-opciones:" << endl;
    cout << "1. Reporte Top 10 streamers por numero de seguidores." << endl;
    cout << "2. Reporte Bottom 10  streamers por tiempo total transmitido" << endl;
    cout << "3. reporte Top 5 categorias con mayor promedio de espectadores." << endl;
    cout << "4. Reporte de categorias" << endl;
    cout << "5. Reporte de influencia" << endl;

}

void GestorStreamers::mostrarReporte(int opcionNum, bool generarArchivo) {

    switch (opcionNum) {
        case 1:
            formatoReporte("CarpetaDeReportes/reporteTop10NumSeguidores.txt",generarArchivo,opcionNum);
            break;
        case 2:
            formatoReporte("CarpetaDeReportes/reporteBottom10TiempoTransmitido.txt",generarArchivo,opcionNum);
            break;
        case 3:
            formatoReporte("CarpetaDeReportes/reporteTop5CategoriasMayorPromEspectadores.txt",generarArchivo,opcionNum);
            break;
        case 4:
            formatoReporte("CarpetaDeReportes/reporteCategorias.txt",generarArchivo,opcionNum);
            break;
        case 5:
            formatoReporte("CarpetaDeReportes/reporteInfluencia.txt",generarArchivo,opcionNum);
            break;
    }

}

void GestorStreamers::formatoReporte(const char *nombArch, bool generarArchivo, int numero) {

    ofstream arch;

    if (generarArchivo) {
        arch.open(nombArch,ios::out);
        mostrarDatosReporte(arch,numero);
    }else {
        mostrarDatosReporte(cout,numero);
    }

}

void GestorStreamers::mostrarDatosReporte(ostream &salida, int numero) {

    salida << setfill('=') << setw(100) << "=" << setfill(' ') << endl;
    switch(numero) {
        case 1:
            salida << setw(65) << "TOP 10 STREAMERS CON MAYOR NUMERO DE SEGUIDORES" << endl;
            break;
        case 2:
            salida << setw(70) << "BOTTOM 10 STREAMERS CON MAYOR TIEMPO TRANSMITIDO" << endl;
            break;
        case 3:
            salida << setw(75) << "TOP 5 CATEGORIAS CON MAYOR PROMEDIO DE ESPECTADORES" << endl;
            break;
        case 4:
            salida << setw(50) << "CATEGORIAS" << endl;
            break;
        case 5:
            salida << setw(50) << "INFLUENCIA" << endl;
            break;
    }
    cargarDataVista(salida,numero);

}

void GestorStreamers::cargarDataVista(ostream &salida, int numero) {

    copiarDatos();
    switch (numero) {
        case 1:
            qsort(dataVista,numDataVista,sizeof (dataVista[0]),comparaNumSeguidores);
            cortarDatos(10);
            break;
        case 2:
            qsort(dataVista,numDataVista,sizeof (dataVista[0]),comparaTiempoEnStream);
            cortarDatos(10);
            break;
        case 3:
            qsort(dataVista,numDataVista,sizeof (dataVista[0]),comparaPromEspectadores);
            cortarDatos(5);
            break;
        case 4:
            qsort(dataVista,numDataVista,sizeof (dataVista[0]),comparaCategoria);
            break;
        case 5:
            qsort(dataVista,numDataVista,sizeof (dataVista[0]),comparaInfluencia);
            break;
    }
    mostrarDatosDataVista(salida);

}

void GestorStreamers::copiarDatos() {

    delete [] dataVista;
    dataVista = new Streamer [numData];
    for (int i = 0; i < numData; i++) dataVista[i].copiar(data[i]);
    numDataVista = numData;

}

void GestorStreamers::cortarDatos(int numero) {

    class Streamer *dataCopia {};

    dataCopia = new Streamer [numero] {};
    for (int i = 0; i < numero; i++) dataCopia[i].copiar(dataVista[i]);
    delete [] dataVista;
    dataVista = dataCopia;
    numDataVista = numero;

}

int GestorStreamers::comparaNumSeguidores(const void *a, const void *b) {

    const Streamer *streamerA {}, *streamerB {};

    streamerA = (const Streamer *)a;
    streamerB = (const Streamer *)b;

    if (streamerA->obtenerNumSeguidores() < streamerB->obtenerNumSeguidores()) return 1;
    else if (streamerA->obtenerNumSeguidores() > streamerB->obtenerNumSeguidores()) return -1;
    return 0;

};

int GestorStreamers::comparaTiempoEnStream(const void *a, const void *b) {

    const Streamer *streamerA {}, *streamerB {};

    streamerA = (const Streamer *)a;
    streamerB = (const Streamer *)b;

    if (streamerA->obtenerTiempoStream() > streamerB->obtenerTiempoStream()) return 1;
    else if (streamerA->obtenerTiempoStream() < streamerB->obtenerTiempoStream()) return -1;
    return 0;

}

int GestorStreamers::comparaPromEspectadores(const void *a, const void *b) {

    const Streamer *streamerA {}, *streamerB {};

    streamerA = (const Streamer *)a;
    streamerB = (const Streamer *)b;

    if (streamerA->obtenerPromEspectadores() < streamerB->obtenerPromEspectadores()) return 1;
    else if (streamerA->obtenerPromEspectadores() > streamerB->obtenerPromEspectadores()) return -1;
    return 0;


}

int GestorStreamers::comparaCategoria(const void *a, const void *b) {

    char categoriaA[50] {}, categoriaB[50] {};

    const Streamer *streamerA {}, *streamerB {};

    streamerA = (const Streamer *)a;
    streamerB = (const Streamer *)b;

    streamerA->obtenerCategoria(categoriaA);
    streamerB->obtenerCategoria(categoriaB);

    return strcmp(categoriaA,categoriaB);

}

int GestorStreamers::comparaInfluencia(const void *a, const void *b) {

    double influenciaA = 0, influenciaB = 0;

    const Streamer *streamerA {}, *streamerB {};

    streamerA = (const Streamer *)a;
    streamerB = (const Streamer *)b;
    influenciaA = (streamerA->obtenerPromEspectadores() * streamerA->obtenerTiempoStream()) /
                  log((double)streamerA->obtenerNumSeguidores() + 1)
    ;
    influenciaB = (streamerB->obtenerPromEspectadores() * streamerB->obtenerTiempoStream()) /
                  log((double)streamerB->obtenerNumSeguidores() + 1)
    ;

    if (influenciaA < influenciaB) return 1;
    else if (influenciaA > influenciaB) return -1;
    else return 0;

}


void GestorStreamers::mostrarDatosDataVista(ostream &salida) {

    salida << setfill('=') << setw(100) << "=" << setfill(' ') << endl;
    salida << "Canal " << setw(25) << "Tiempo em Stream" << setw(25)
           << "Promedio Espectadores" << setw(25) << "Numero Seguidores"
           << setw(15) << "Categoria" << endl
    ;
    salida << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
    for (int i = 0; i < numDataVista; i++) {
        dataVista[i].mostrarStreamer(salida);
    }
    salida << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
    cout << endl;

}

void GestorStreamers::generarReportes() {

    int numero = 1;

    while (numero < 6) {
        mostrarReporte(numero,true);
        numero++;
    }

}
