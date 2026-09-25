#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "funciones.h"

#define Incremento (5)

void cargarArchivo(const char *nombArch, ifstream &arch) {

    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo " << nombArch << endl;
        exit(1);
    }

}

void crearArchivo(const char *nombArch, ofstream &arch) {

    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo crear el archivo " << nombArch << endl;
        exit(2);
    }

}

void cargarStreamers(void *&streamers) {

    ifstream arch;

    int numStreamers = 0, capacidad = 1;
    int promEspectadores;
    long long tiempoReproduccion, numSeguidores;
    char caracter;

    char *nombre, *categoria;
    void ***influencers = nullptr;

    cargarArchivo("CarpetaDeDatos/streamers.csv",arch);
    while (true) {
        nombre = leerCadenaCaracteres(arch,',');
        if (arch.eof()) break;
        arch >> tiempoReproduccion >> caracter >> promEspectadores >> caracter >> numSeguidores >> caracter;
        categoria = leerCadenaCaracteres(arch,'\n');
        if (numStreamers == capacidad - 1) incrementarCapacidadStreamers(influencers,numStreamers,capacidad);
        cargarDatosStreamer(influencers[numStreamers],nombre,numSeguidores,categoria);
        numStreamers++;
    }
    streamers = influencers;

}

char *leerCadenaCaracteres(ifstream &arch, char delim) {

    char cadena[200], *ptrCadena;

    arch.getline(cadena,200,delim);
    if (arch.eof()) return nullptr;
    ptrCadena = new char [strlen(cadena) + 1];
    strcpy(ptrCadena,cadena);

    return ptrCadena;

}

void incrementarCapacidadStreamers(void ***&influencers, int numStreamers, int &capacidad) {

    void ***streamers;

    capacidad += Incremento;
    if (!influencers) {
        influencers = new void **[capacidad] {};
    }else {
        streamers = new void **[capacidad] {};
        for (int i = 0; i < numStreamers; i++) streamers[i] = influencers[i];
        delete [] influencers;
        influencers = streamers;
    }

}

void cargarDatosStreamer(void **&influencers, char *nombre, long long numSeguidores, char *categoria) {

    long long  *ptrNumSeguidores;

    ptrNumSeguidores = new long long;
    *ptrNumSeguidores = numSeguidores;

    influencers = new void *[4] {};
    influencers[0] = nombre;
    influencers[1] = ptrNumSeguidores;
    influencers[2] = categoria;
    influencers[3] = nullptr;
}

void cargarComentarios(void *&comentarios) {

    ifstream arch;

    int numComentarios = 0, capacidad = 1;

    char *codigo, *texto, *emisor, *receptor;
    void ***opiniones = nullptr;

    cargarArchivo("CarpetaDeDatos/comentarios.csv",arch);
    while (true) {
        codigo = leerCadenaCaracteres(arch,',');
        if (arch.eof()) break;
        texto = leerCadenaCaracteres(arch,'[');
        emisor = leerCadenaCaracteres(arch,' ');
        receptor = leerCadenaCaracteres(arch,']');
        arch.get();
        if (numComentarios == capacidad - 1) incrementarCapacidadComentarios(opiniones,numComentarios,capacidad);
        cargarDatosComentarios(opiniones[numComentarios],codigo,texto,emisor,receptor);
        numComentarios++;
    }
    comentarios = opiniones;

}

void incrementarCapacidadComentarios(void ***&opiniones, int numComentarios, int &capacidad) {

    void ***comentarios;

    capacidad += Incremento;
    if (!opiniones) {
        opiniones = new void **[capacidad] {};
    }else {
        comentarios = new void **[capacidad] {};
        for (int i = 0; i < numComentarios; i++) comentarios[i] = opiniones[i];
        delete [] opiniones;
        opiniones = comentarios;
    }

}

void cargarDatosComentarios(void **&opiniones, char *codigo, char *texto, char *emisor, char *receptor) {

    opiniones = new void *[4] {};
    opiniones[0] = codigo;
    opiniones[1] = emisor;
    opiniones[2] = receptor;
    opiniones[3] = texto;

}

void actualizarComentarios(void *&streamers, void *comentarios) {

    int numComentarios, capacidad;

    char ***comentario;
    void ***influencers, ***opiniones, **creador, **opinion;

    influencers = (void ***)streamers;
    for (int i = 0; influencers[i]; i++) {
        opiniones = (void ***)comentarios;
        creador = (void **)influencers[i];
        comentario = nullptr;
        numComentarios = 0;
        capacidad = 1;
        for (int a = 0; opiniones[a]; a++) {
            opinion = (void **)opiniones[a];
            if (strcmp((char *)creador[0],(char *)opinion[1]) == 0) {
                cargarComentarioStreamer(comentario,(char *)opinion[2],(char *)opinion[3],numComentarios,
                                         capacidad)
                ;
                creador[3] = comentario;
            }
        }
    }

}

void cargarComentarioStreamer(char ***&comentario, char *receptor, char *texto, int &numComentarios, int &capacidad) {

    char ***ptrComentario, **ptrOpinion;

    if (numComentarios == capacidad - 1) {
        capacidad += Incremento;
    }
    ptrOpinion = new char *[2] {};
    ptrOpinion[0] = receptor;
    ptrOpinion[1] = texto;
    if (!comentario) {
        comentario = new char **[capacidad] {};
        comentario[numComentarios] = ptrOpinion;
    }else {
        ptrComentario = new char **[capacidad] {};
        for (int i = 0; i < numComentarios; i++) ptrComentario[i] = comentario[i];
        ptrComentario[numComentarios] = ptrOpinion;
        delete [] comentario;
        comentario = ptrComentario;
    }
    numComentarios++;

}

void imprimirStreamers(void *streamers) {

    ofstream arch;

    void ***influencers, **creador;

    crearArchivo("CarpetaDeReportes/reporte.txt",arch);
    influencers = (void ***)streamers;
    for (int i = 0; influencers[i]; i++) {
        creador = (void **)influencers[i];
        imprimirDatosStreamers(arch,creador);
    }

}

void imprimirDatosStreamers(ofstream &arch, void **creador) {

    char *nombre;
    long long *numSeguidores;
    char ***comentarios, **opinion;

    nombre = (char *)creador[0];
    numSeguidores = (long long *)creador[1];
    comentarios = (char ***)creador[3];

    arch << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    arch << left << setw (15) << "Cuenta" << setw(15) << "Seguidores" << endl;
    arch << left << setw (15) << nombre << setw(15) << *numSeguidores << endl;
    arch << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
    arch << "Comentarios emitidos: " << endl;
    arch << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
    arch << left << setw (15) << "Receptor" << setw(15) << "Texto" << endl;
    arch << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
    if (!comentarios) arch << "No se encontraron comentarios de este creador" << endl;
    else {
        for (int i = 0; comentarios[i]; i++) {
            opinion = comentarios[i];
            arch << left << setw(15) << opinion[0] << opinion[1] << endl;
        }
    }

}
