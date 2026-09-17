#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "funciones.h"

#define Capacidad (5)
#define NoEncontrado (-1)

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

void cargarCategorias(const char *nombArch, char ***&categorias) {

    ifstream arch;

    int numCategorias = 0, capacidad = 1;
    char *codigo, *nombre, *descripcion;

    cargarArchivo(nombArch,arch);
    while (true) {
        codigo = leerCadenaCaracteres(arch,',');
        if (arch.eof()) break;
        nombre = leerCadenaCaracteres(arch,',');
        descripcion = leerCadenaCaracteres(arch,'\n');
        if (numCategorias == capacidad - 1) aumentarCapacidadCategorias(categorias,numCategorias,
                                                                        capacidad);
        categorias[numCategorias] = new char *[4] {};
        categorias[numCategorias][0] = codigo;
        categorias[numCategorias][1] = nombre;
        categorias[numCategorias][2] = descripcion;
        numCategorias++;
    }

}

char *leerCadenaCaracteres(ifstream &arch, char delim) {

    char cadena[150], *ptrCadena;

    arch.getline(cadena,150,delim);
    if (arch.eof()) return nullptr;
    ptrCadena = new char [strlen(cadena) + 1];
    strcpy(ptrCadena,cadena);

    return ptrCadena;

}

void aumentarCapacidadCategorias(char ***&categorias, int numCategorias, int &capacidad) {

    char ***bCategorias;

    capacidad += Capacidad;
    if (!categorias) {
        categorias = new char **[capacidad] {};
    }else {
        bCategorias = new char **[capacidad] {};
        for (int i = 0; i < numCategorias; i++) bCategorias[i] = categorias[i];
        delete [] categorias;
        categorias = bCategorias;
    }

}

void cargarStreamers(const char *nombArch, char ***&streamers, int **&fechasPromedios,
                     long long **&tiempoRepSeguidores) {

    ifstream arch;

    int diaC, mesC, añoC, diaT, mesT, añoT, promEspectadores, fechaCreacion,
        fechaTransmision, numStreamers = 0, capacidad = 1
    ;
    long long tiempoReproduccion, numSeguidores;
    char *nombre, *categoria, caracter;

    cargarArchivo(nombArch,arch);
    while (true) {
        nombre = leerCadenaCaracteres(arch,',');
        if (arch.eof()) break;
        arch >> diaC >> caracter >> mesC >> caracter >> añoC >> caracter >> diaT >> caracter
             >> mesT >> caracter >> añoT >> caracter >> tiempoReproduccion >> caracter
             >> promEspectadores >> caracter >> numSeguidores >> caracter
        ;
        categoria = leerCadenaCaracteres(arch,'\n');
        fechaCreacion = construirFecha(diaC,mesC,añoC);
        fechaTransmision = construirFecha(diaT,mesT,añoT);
        if (numStreamers == capacidad - 1) aumentarCapacidadStreamers(streamers,fechasPromedios,
                                                                      tiempoRepSeguidores,numStreamers,
                                                                      capacidad);
        streamers[numStreamers] = new char *[3] {};
        streamers[numStreamers][0] = nombre;
        streamers[numStreamers][1] = categoria;
        fechasPromedios[numStreamers] = new int [4] {};
        fechasPromedios[numStreamers][0] = fechaCreacion;
        fechasPromedios[numStreamers][1] = fechaTransmision;
        fechasPromedios[numStreamers][2] = promEspectadores;
        tiempoRepSeguidores[numStreamers] = new long long [3] {};
        tiempoRepSeguidores[numStreamers][0] = tiempoReproduccion;
        tiempoRepSeguidores[numStreamers][1] = numSeguidores;
        numStreamers++;
    }

}

int construirFecha(int dia, int mes, int año) {

    return año * 10000 + mes * 100 + dia;

}

void aumentarCapacidadStreamers(char ***&streamers, int **&fechasPromedios, long long **&tiempoRepSeguidores,
                                int numStreamers, int &capacidad) {

    char ***bStreamers;
    int **bFechasPromedios;
    long long **bTiempoRepSeguidores;

    capacidad += Capacidad;
    if (!streamers) {
        streamers = new char **[capacidad] {};
        fechasPromedios = new int *[capacidad] {};
        tiempoRepSeguidores = new long long *[capacidad] {};
    }else {
        bStreamers = new char **[capacidad] {};
        bFechasPromedios = new int *[capacidad] {};
        bTiempoRepSeguidores = new long long *[capacidad] {};
        for (int i = 0; i < numStreamers; i++) {
            bStreamers[i] = streamers[i];
            bFechasPromedios[i] = fechasPromedios[i];
            bTiempoRepSeguidores[i] = tiempoRepSeguidores[i];
        }
        delete [] streamers;
        delete [] fechasPromedios;
        delete [] tiempoRepSeguidores;
        streamers = bStreamers;
        fechasPromedios = bFechasPromedios;
        tiempoRepSeguidores = bTiempoRepSeguidores;
    }

}

void cargarEtiquetasComentarios(const char *nombArch, char ***&comentarios, char ***&etiquetas) {

    ifstream arch;

    int numEtiquetas = 0, numComentarios = 0, capacidad = 1;
    char *etiqueta, *comentarioParte1, *comentarioParte2, *streamers;

    char **bEtiquetas[400];

    cargarArchivo(nombArch,arch);
    while (true) {
        etiqueta = leerCadenaCaracteres(arch,',');
        if (arch.eof()) break;
        arch >> ws;
        comentarioParte1 = leerCadenaCaracteres(arch,'[');
        streamers = leerCadenaCaracteres(arch,']');
        bEtiquetas[numEtiquetas] = new char *[2] {};
        bEtiquetas[numEtiquetas][0] = streamers;
        comentarioParte2 = leerCadenaCaracteres(arch,'\n');
        concatenarComentarios(comentarioParte1,comentarioParte2);
        if (numComentarios == capacidad - 1) aumentarCapacidad(comentarios,numComentarios,capacidad);
        comentarios[numComentarios] = new char *[3] {};
        comentarios[numComentarios][0] = etiqueta;
        comentarios[numComentarios][1] = comentarioParte1;
        numComentarios++;
        numEtiquetas++;
    }
    etiquetas = new char **[numComentarios + 1] {};
    for (int i = 0; i < numComentarios; i++) etiquetas[i] = bEtiquetas[i];

}

void concatenarComentarios(char *&comentarioParte1, char *comentarioParte2) {

    int espacioComentario1, espacioComentario2;
    char *ptrComentario;

    espacioComentario1 = strlen(comentarioParte1) + 1;
    espacioComentario2 = strlen(comentarioParte2) + 1;
    ptrComentario = new char [espacioComentario1 + espacioComentario2 + 1] {};
    strcpy(ptrComentario,comentarioParte1);
    strcat(ptrComentario,comentarioParte2);
    delete [] comentarioParte1;
    comentarioParte1 = new char [strlen(ptrComentario) + 1] {};
    strcpy(comentarioParte1,ptrComentario);

}

void aumentarCapacidad(char ***&comentarios, int numComentarios, int &capacidad) {

    char ***comentariosAux;

    capacidad += Capacidad;
    if (!comentarios) {
        comentarios = new char **[capacidad] {};
    }else {
        comentariosAux = new char **[capacidad] {};
        for (int i = 0; i < numComentarios; i++) comentariosAux[i] = comentarios[i];
        delete [] comentarios;
        comentarios = comentariosAux;
    }

}

void imprimirReportes(const char *nombArch, char ***categorias, char ***streamers, int **fechasPromedios,
                      long long **tiempoRepSeguidores, char ***comentarios, char ***etiquetas) {

    int contador, linea;
    char *encontrado;
    bool seEncontro;

    ofstream arch;

    crearArchivo(nombArch,arch);

    for (int i = 0; categorias[i] != nullptr; i++) {
        contador = 0;
        for (int b = 0; categorias[i][1][b] != '\0'; b++) contador++;
        linea = 200 - contador;
        arch << setfill('*') << setw(linea / 2) << "*" << setfill(' ');
        arch << categorias[i][1];
        arch << setfill('*') << setw(linea / 2) << "*" << setfill(' ') << endl;
        arch << "CUENTA" << setw(25) << "FECHA CREACION" << setw(22) << "FECHA ULT. STREAM"
             << setw(20) << "TIEMPO REP." << setw(23) << "CANT. SEGUIDORES"
             << setw(35) << "ETIQUETAS" << endl
        ;
        arch << setfill('=') << setw(200) << "=" << setfill(' ') << endl;
        for (int a = 0; streamers[a] != nullptr; a++) {
            if (strcmp(streamers[a][1],categorias[i][0]) == 0) {
                arch << left << setw(20) << streamers[a][0] << right << fechasPromedios[a][0]
                     << setw(20) << fechasPromedios[a][1] << setw(24) << tiempoRepSeguidores[a][0]
                     << setw(20) << tiempoRepSeguidores[a][1] << setw(10) << " "
                ;
                seEncontro = false;
                for (int b = 0; etiquetas[b] != nullptr; b++) {
                    encontrado = nullptr;
                    encontrado = strstr(etiquetas[b][0],streamers[a][0]);
                    if (encontrado) {
                        arch << "[" << comentarios[b][0] << "]" << setw(5) << " "
                             << left << setw(120) << comentarios[b][1]  << right << endl
                        ;
                        seEncontro = true;
                    }
                }
                if (!seEncontro) arch << endl;
            }
        }
    }

}
