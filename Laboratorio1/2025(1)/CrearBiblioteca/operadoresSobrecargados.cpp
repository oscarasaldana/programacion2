#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "funciones.h"
#include "operadoresSobrecargados.h"
#include "estructura.h"

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

void cargarInfracciones(ifstream &archInfraccion, int *arrDni, struct CadenaCaracteres *arrConductores,
                        struct CadenaCaracteres *arrPlacas, int &numConductores) {

    cargarArchivo("CarpetaDeDatos/InfraccionesDeTransito.txt",archInfraccion);

    int codInfraccion;
    char *cadenaCaracter, caracter;
    bool primeraCadena;

    numConductores = 0;
    while (true) {
        archInfraccion >> arrDni[numConductores];
        if (archInfraccion.eof()) break;
        primeraCadena = true;
        while (true) {
            archInfraccion >> ws;
            caracter = archInfraccion.peek();
            if (caracter >= '0' and caracter <= '9') break;
            cadenaCaracter = leerCadenaExacta(archInfraccion,' ');
            if (primeraCadena) {
                !arrConductores[numConductores];
                arrConductores[numConductores] <= cadenaCaracter;
                primeraCadena = false;
            }else {
                arrConductores[numConductores] += cadenaCaracter;
            }
        }
        archInfraccion >> codInfraccion;
        archInfraccion >> ws;
        cadenaCaracter = leerCadenaCaracter(archInfraccion,'\n');
        arrPlacas[numConductores] <= cadenaCaracter;
        numConductores++;
    }

}

char *leerCadenaExacta(ifstream &arch, char delim) {

    char cadena[30], *ptrCadena;

    arch.getline(cadena,30,delim);
    if (cadena[0] >= 'a' and cadena[0] <= 'z') cadena[0] -= 'a' - 'A';
    for (int i = 1; cadena[i] != '\0'; i++) {
        if (cadena[i] >= 'A' and cadena[i] <= 'Z') cadena[i] += 'a' - 'A';
    }
    if (arch.eof()) return nullptr;
    ptrCadena = new char[strlen(cadena) + 1];
    strcpy(ptrCadena,cadena);

    return ptrCadena;

}

char *leerCadenaCaracter(ifstream &arch, char delim) {

    char cadena[30], *ptrCadena;

    arch.getline(cadena,30,delim);
    if (arch.eof()) return nullptr;
    ptrCadena = new char[strlen(cadena) + 1];
    strcpy(ptrCadena,cadena);

    return ptrCadena;

}

void qsort(int *arrDni, struct CadenaCaracteres *arrConductores, struct CadenaCaracteres *arrPlacas,
           int inicio, int final) {

    int medio, puntero;

    if (inicio >= final) return;

    medio = (inicio + final) / 2;
    puntero = inicio;
    cambiar(arrDni,arrConductores,arrPlacas,inicio,medio);
    for (int i = inicio + 1; i <= final; i++) {
        if (strcmp(arrConductores[i].cadena,arrConductores[inicio].cadena) < 0) {
            puntero++;
            cambiar(arrDni,arrConductores,arrPlacas,i,puntero);
        }
    }
    cambiar(arrDni,arrConductores,arrPlacas,inicio,puntero);
    qsort(arrDni,arrConductores,arrPlacas,inicio,puntero - 1);
    qsort(arrDni,arrConductores,arrPlacas,puntero + 1,final);

}

void cambiar(int *arrDni, struct CadenaCaracteres *arrConductores, struct CadenaCaracteres *arrPlacas,
             int a, int b) {

    int dniAux;

    dniAux = arrDni[a];
    arrDni[a] = arrDni[b];
    arrDni[b] = dniAux;

    arrConductores[a] && arrConductores[b];

    arrPlacas[a] && arrPlacas[b];

}

void reporte(ofstream &archReporte, int *arrDni, struct CadenaCaracteres *arrConductores,
             struct CadenaCaracteres *arrPlacas, int numConductores) {

    int contador;

    crearArchivo("CarpetaDeReportes/ReporteDeTransito",archReporte);

    archReporte << setw(50) << "REPORTE DE INFRACCIONES DE TRANSITO" << endl;
    archReporte << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
    archReporte << "DNI" << setw(25) << "INFRACTOR" << setw(35) << "PLACA" << endl;
    archReporte << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    for (int i = 0; i < numConductores; i++) {
        archReporte << arrDni[i] << setw(5) << " ";
        archReporte << arrConductores[i];
        contador = contarCaracteres(arrConductores[i].cadena);
        archReporte << setw(51 - contador);
        archReporte << arrPlacas[i];
        archReporte << endl;
    }

}

int contarCaracteres(char *cadena) {

    int contador = 0;

    for (int i = 0; cadena[i] != '\0'; i++) {
        contador++;
    }

    return contador;

}
