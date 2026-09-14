#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "funciones.h"
#include "../estructuras/conductores.h"
#include "../estructuras/infracciones.h"
#include "../estructuras/faltas.h"

#define NoEncontrado (-1)
#define Incremento (2)

void cargarArchivo(const char *nombArch, ifstream &arch) {

    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR; No se pudo acceder al archivo " << nombArch << endl;
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

void operator += (struct Conductores &conductores, const char *nombArch) {

    ifstream arch;

    char caracter;

    int bDnis[150] {};
    char *bNombres[150] {};

    cargarArchivo(nombArch,arch);
    while (true) {
        arch >> bDnis[conductores.cantidad];
        if (arch.eof()) break;
        arch >> caracter;
        bNombres[conductores.cantidad] = leerCadenaCaracteres(arch,'\n');
        conductores.cantidad++;
    }
    conductores.dnis = new int [conductores.cantidad + 1] {};
    conductores.nombres = new char *[conductores.cantidad + 1] {};
    for (int i = 0; i < conductores.cantidad; i++) {
        conductores.dnis[i] = bDnis[i];
        conductores.nombres[i] = bNombres[i];
    }

}

char *leerCadenaCaracteres(ifstream &arch, char delim) {

    char cadena[200], *ptrCadena;

    arch.getline(cadena,200,delim);
    if (arch.eof()) return nullptr;
    ptrCadena = new char[strlen(cadena) + 1];
    strcpy(ptrCadena,cadena);

    return ptrCadena;

}

void operator += (struct Infracciones &infracciones, const char *nombArch) {

    ifstream arch;

    int bCodigo[120] {};
    double precio;
    char *bDescripcion[120] {}, *bTipos[120] {}, caracter;

    cargarArchivo(nombArch,arch);
    while (true) {
        arch >> bCodigo[infracciones.cantidad];
        if (arch.eof()) break;
        arch >> caracter;
        bDescripcion[infracciones.cantidad] = leerCadenaCaracteres(arch,',');
        bTipos[infracciones.cantidad] = leerCadenaCaracteres(arch,',');
        arch >> precio;
        infracciones.cantidad++;
    }
    infracciones.codigo = new int [infracciones.cantidad + 1] {};
    infracciones.descripcion = new char *[infracciones.cantidad + 1] {};
    infracciones.tipos = new char *[infracciones.cantidad + 1] {};
    for (int i = 0; i < infracciones.cantidad; i++) {
        infracciones.codigo[i] = bCodigo[i];
        infracciones.descripcion[i] = bDescripcion[i];
        infracciones.tipos[i] = bTipos[i];
    }

}

void cargarFaltasConductores(const char *archConductores, const char *archInfracciones,
                             const char *archFaltas, struct Faltas &faltas) {

    ifstream arch;

    int dni, codigoInfraccion, dia, mes, año, posicion;
    char caracter, *placa;

    cargarArchivo(archFaltas,arch);
    faltas.conductores += archConductores;
    faltas.infracciones += archInfracciones;
    faltas.placas = new char **[faltas.conductores.cantidad + 1] {};
    faltas.capacidad = new int [faltas.conductores.cantidad + 1] {};
    while (true) {
        arch >> dni;
        if (arch.eof()) break;
        arch >> caracter;
        placa = leerCadenaCaracteres(arch,',');
        arch >> dia >> caracter >> mes >> caracter >> año >> caracter >> codigoInfraccion;
        posicion = encontrarPosicionDni(faltas.conductores.dnis,dni,faltas.conductores.cantidad);
        cargarPlacas(faltas,placa,posicion);
    }

}

int encontrarPosicionDni(const int *dnis, int dni, int numDnis) {

    for (int i = 0; i < numDnis; i++) {
        if (dnis[i] == dni) return i;
    }
    return NoEncontrado;

}

void cargarPlacas(struct Faltas &faltas, char *placa, int posicion) {

    int contador = 0;
    bool repetida = true;

    if (!faltas.placas[posicion]) {
        faltas.placas[posicion] = new char *[2] {};
        faltas.placas[posicion][0] = placa;
        faltas.capacidad[posicion] = 2;
    }else {
        for (int i = 0; faltas.placas[posicion][i] != nullptr; i++) contador++;
        repetida = placaRepetida(faltas.placas[posicion],placa);
        if (!repetida) {
            if (contador == faltas.capacidad[posicion] - 1) {
                incrementarCapacidad(faltas.placas[posicion],faltas.capacidad[posicion]);
            }
            faltas.placas[posicion][contador] = placa;
        }
    }

}

bool placaRepetida(char **placas, char *placa) {

    for (int i = 0; placas[i] != nullptr; i++) {
        if (strcmp(placas[i],placa) == 0) return true;
    }
    return false;

}

void incrementarCapacidad(char **&placas, int &capacidad) {

    char **placasAux;

    capacidad += Incremento;
    placasAux = new char *[capacidad] {};
    for (int i = 0; i < capacidad - 2; i++) placasAux[i] = placas[i];
    delete [] placas;
    placas = placasAux;

}

void imprimirFaltasConductores(const char *nombArch, struct Faltas &faltas) {

    ofstream arch;

    crearArchivo(nombArch,arch);
    arch << setw(5) << "DNI" << setw(15) << "CLIENTE" << setw(55) << "CANT VEHICULOS" << endl;
    arch << setfill('=') << setw(120) << "=" << setfill(' ') << endl;

    for (int i = 0; i < faltas.conductores.cantidad; i++) {
        arch << faltas.conductores.dnis[i] << setw(5) << " " << left << setw(40)
             << faltas.conductores.nombres[i] << right
        ;
        if (faltas.placas[i] != nullptr) {
            arch << setw(15) << faltas.capacidad[i] - 1 << endl;
        }else {
            arch << setw(15) << faltas.capacidad[i] << endl;
        }
    }

}
