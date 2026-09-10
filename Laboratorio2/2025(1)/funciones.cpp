#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "funciones.h"
#include "conductores.h"
#include "infracciones.h"
#include "faltas.h"

#define Incremento (2)
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
        cout << "ERROR: No se pudo creer el archivo " << nombArch << endl;
        exit(2);
    }

}

void operator += (struct Conductores &conductor, const char *nombArch) {

    ifstream arch;

    int  dni, capacidad = 0;
    char *nombre;

    cargarArchivo(nombArch,arch);
    while (true) {
        arch >> dni;
        if (arch.eof()) break;
        arch.get();
        nombre = leerCadenaCaracteres(arch,'\n');
        if (conductor.cantidad == capacidad) incrementarCapacidad(conductor,conductor.cantidad,capacidad);
        conductor.dnis[conductor.cantidad] = dni;
        conductor.nombres[conductor.cantidad] = nombre;
        conductor.cantidad++;
    }

}

char *leerCadenaCaracteres(ifstream &arch, char delim) {

    char cadena[200], *ptrCadena;

    arch.getline(cadena,200,delim);
    if (arch.eof()) return nullptr;
    ptrCadena = new char[strlen(cadena) + 1] {};
    strcpy(ptrCadena,cadena);

    return ptrCadena;

}

void incrementarCapacidad(struct Conductores &conductor, int &numDatos, int &capacidad) {

    struct Conductores aux {};

    capacidad += Incremento;
    if (conductor.dnis == nullptr and conductor.nombres == nullptr) {
        conductor.dnis = new int [capacidad] {};
        conductor.nombres = new char *[capacidad] {};
    }else {
        aux.dnis = new int [capacidad] {};
        aux.nombres = new char *[capacidad] {};
        for (int i = 0; i < numDatos; i++) {
            aux.dnis[i] = conductor.dnis[i];
            aux.nombres[i] = conductor.nombres[i];
        }
        delete [] conductor.dnis;
        delete [] conductor.nombres;
        conductor.dnis = aux.dnis;
        conductor.nombres = aux.nombres;
    }

}

void operator += (struct Infracciones &infraccion, const char *nombArch) {

    ifstream arch;

    int codInfraccion, capacidad = 0;
    char *descripcion, *gravedad;
    double precio;

    cargarArchivo(nombArch,arch);
    while (true) {
        arch >> codInfraccion;
        if (arch.eof()) break;
        arch.get();
        descripcion = leerCadenaCaracteres(arch,',');
        gravedad = leerCadenaCaracteres(arch,',');
        arch >> precio;
        if (infraccion.cantidad == capacidad) aumentarCapacidad(infraccion,infraccion.cantidad,capacidad);
        infraccion.codigo[infraccion.cantidad] = codInfraccion;
        infraccion.descripciones[infraccion.cantidad] = descripcion;
        infraccion.tipos[infraccion.cantidad] = gravedad;
        infraccion.valores[infraccion.cantidad] = precio;
        infraccion.cantidad++;
    }

}

void aumentarCapacidad(struct Infracciones &infraccion, int &numDatos, int &capacidad) {

    struct Infracciones aux {};

    capacidad += Incremento;
    if (infraccion.descripciones == nullptr and infraccion.tipos == nullptr and
        infraccion.cantidad == 0 and infraccion.valores == 0) {
        infraccion.codigo = new int [capacidad] {};
        infraccion.descripciones = new char *[capacidad] {};
        infraccion.tipos = new char *[capacidad] {};
        infraccion.valores = new double [capacidad] {};
    }else {
        aux.codigo = new int [capacidad] {};
        aux.descripciones = new char *[capacidad] {};
        aux.tipos = new char *[capacidad] {};
        aux.valores = new double [capacidad] {};
        for (int i = 0; i < numDatos; i++) {
            aux.codigo[i] = infraccion.codigo[i];
            aux.descripciones[i] = infraccion.descripciones[i];
            aux.tipos[i] = infraccion.tipos[i];
            aux.valores[i] = infraccion.valores[i];
        }
        delete [] infraccion.codigo;
        delete [] infraccion.descripciones;
        delete [] infraccion.tipos;
        delete [] infraccion.valores;
        infraccion.codigo = aux.codigo;
        infraccion.descripciones = aux.descripciones;
        infraccion.tipos = aux.tipos;
        infraccion.valores = aux.valores;
    }

}

void cargarFaltasDeLosConductores(const char *archFaltas, const char *nombConductores,
                                  const char *nombInfracciones, struct Faltas &falta) {

    ifstream arch;

    int dni, posicion;
    char *placa;

    falta.conductores += nombConductores;
    falta.infracciones += nombInfracciones;
    cargarArchivo(archFaltas,arch);
    falta.capacidades = new int [falta.conductores.cantidad + 1] {};
    falta.placa = new char **[falta.conductores.cantidad + 1] {};
    while (true) {
        arch >> dni;
        if (arch.eof()) break;
        arch.get();
        placa = leerCadenaCaracteres(arch,',');
        while (arch.get() != '\n');
        posicion = encontrarPosicion(falta.conductores.dnis,dni,falta.conductores.cantidad);
        if (posicion != NoEncontrado) {
            agregarPlaca(falta.placa,posicion,placa);
            falta.capacidades[posicion] += 1;
        }
    }

}

int encontrarPosicion(const int *arrDni, const int dni, const int cantDnis) {

    for (int i = 0; i < cantDnis; i++) {
        if (arrDni[i] == dni) return i;
    }
    return NoEncontrado;

}

void agregarPlaca(char ***&placas, int posicion, char *placa) {

    int contador = 0;
    char **placaAux;

    if (!placas[posicion]) {
        placas[posicion] = new char *[2] {};
        placas[posicion][0] = placa;
        placas[posicion][1] = nullptr;
    }else {
        for (int i = 0; placas[posicion][i] != nullptr; i++) contador++;
        placaAux = new char *[contador + 2] {};
        for (int i = 0; i < contador; i++) placaAux[i] = placas[posicion][i];
        placaAux[contador] = placa;
        placaAux[contador + 1] = nullptr;
        delete [] placas[posicion];
        placas[posicion] = placaAux;
    }

}

void imprimirFaltasDeLosConductores(const char *nombArch, struct Faltas &falta) {

    ofstream arch;

    int cont;

    crearArchivo(nombArch,arch);
    arch << setfill('=') << setw(75) << "=" << setfill(' ') << endl;
    arch << setw(5) << "DNI" << setw(25) << "CLIENTE" << setw(40) << "CANT.VEHICULOS" << endl;
    arch << setfill('-') << setw(75) << "-" << setfill(' ') << endl;
    for (int i = 0; i < falta.conductores.cantidad; i++) {
        arch << falta.conductores.dnis[i] << setw(5) << " ";
        cont = 0;
        for (int m = 0; falta.conductores.nombres[i][m] != '\0'; m++) {
            arch << falta.conductores.nombres[i][m];
            cont++;
        }
        arch << setw(50 - cont) << " " << falta.capacidades[i] << endl;
    }
    arch << setfill('=') << setw(75) << "=" << setfill(' ') << endl;

}
