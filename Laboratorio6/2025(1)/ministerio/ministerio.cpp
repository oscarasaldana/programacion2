#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "../multa/multa.h"
#include "../infraccion/infraccion.h"
#include "../empresa/empresa.h"
#include "ministerio.h"

Ministerio::Ministerio() {

    listaDeInfracciones = nullptr;
    numInfracciones = 0;
    numEmpresas = 0;

}
Ministerio::~Ministerio() {

    delete [] listaDeInfracciones;

}

void Ministerio::obtenerNumInfracciones(int &dato) const {

    dato = this->numInfracciones;

}

void Ministerio::obtenerNumEmpresas(int &dato) const {

    dato = this->numEmpresas;

}

void Ministerio::operator < (const char *nombArch) {

    ifstream arch;

    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo TablaDeInfracciones.csv" << endl;
        exit(1);
    }

    class Infraccion infraccion[200];

    int codigo;
    double precio;
    char gravedad[50] {}, descripcion[200] {};

    while (true) {
        arch >> infraccion[numInfracciones];
        if (arch.eof()) break;
        numInfracciones++;
    }
    listaDeInfracciones = new Infraccion [numInfracciones];
    for (int i = 0; i < numInfracciones; i++) {
        infraccion[i].obtenerCodigo(codigo);
        infraccion[i].obtenerMulta(precio);
        infraccion[i].obtenerGravedad(gravedad);
        infraccion[i].obtenerDescripcion(descripcion);
        listaDeInfracciones[i].cargarCodigo(codigo);
        listaDeInfracciones[i].cargarMulta(precio);
        listaDeInfracciones[i].cargarGravedad(gravedad);
        listaDeInfracciones[i].cargarDescripcion(descripcion);
    }

}

void Ministerio::operator <= (const char *nombArch) {

    ifstream arch;

    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo EmpresasRegistradas.csv" << endl;
        exit(1);
    }

    while (true) {
        arch >> listaDeEmpresas[numEmpresas];
        if (arch.eof()) break;
        numEmpresas++;
    }

}

void Ministerio::operator <<= (const char *nombArch) {

    ifstream arch;

    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo InfraccionesCometidas.csv" << endl;
        exit(1);
    }

    class Multa multa;

    int posicionInfraccion = -1, posicionEmpresa = -1, codigo;
    double precioMulta;
    char placa[10] {};

    while (true) {
        arch >> multa;
        if (arch.eof()) break;
        multa.obtenerCodigoInfraccion(codigo);
        posicionInfraccion = encontrarPosicionInfraccion(codigo);
        listaDeInfracciones[posicionInfraccion].obtenerMulta(precioMulta);
        multa.cargarMulta(precioMulta);
        if (posicionInfraccion != -1) {
            multa.obtenerPlaca(placa);
            posicionEmpresa = encontrarPosicionEmpresa(placa);
            if (posicionEmpresa != -1) {
                listaDeEmpresas[posicionEmpresa] += multa;
            }
        }
    }

}

int Ministerio::encontrarPosicionInfraccion(int codigo) {

    int codigoInfraccion;

    for (int i = 0; i < numInfracciones; i++) {
        listaDeInfracciones[i].obtenerCodigo(codigoInfraccion);
        if (codigoInfraccion == codigo) return i;
    }
    return -1;

}

int Ministerio::encontrarPosicionEmpresa(char *placa) {

    int numPlacas;
    char placaVehiculo[10] {};

    for (int i = 0; i < numEmpresas; i++) {
        listaDeEmpresas[i].obtenerNumPlacas(numPlacas);
        for (int a = 0; a < numPlacas; a++) {
            listaDeEmpresas[i].obtenerPlaca(placaVehiculo,a);
            if (strcmp(placaVehiculo,placa) == 0) return i;
        }
    }
    return -1;

}

void Ministerio::operator >> (const char *nombArch) {

    ofstream arch;

    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo crear el archivo reporteParaElMinisterio.txt" << endl;
        exit(1);
    }

    encabezadoTablaInfracciones(arch);
    arch << setfill('-') << setw(200) << "-" << setfill(' ') << endl;
    for (int i = 0; i < numInfracciones; i++) {
        arch << listaDeInfracciones[i];
    }
    encabezadoListaDeMultas(arch);
    for (int i = 0; i < numEmpresas; i++) {
        arch << listaDeEmpresas[i];
    }
    arch << setfill('=') << setw(200) << "=" << setfill(' ') << endl;

}

void Ministerio::encabezadoTablaInfracciones(ofstream &arch) {

    arch << setw(88) << "MINISTERIO DE TRANSPORTE" << endl;
    arch << setfill('=') << setw(200) << "=" << setfill(' ') << endl;
    arch << setw(86) << "TABLA DE INFRACCIONES" << endl;
    arch << setfill('-') << setw(200) << "-" << setfill(' ') << endl;
    arch << setw(8) << "CODIGO" << setw(15) << "MULTA" << setw(20) << "GRAVEDAD"
         << setw(20) << "DESCRIPCION" << endl;
    ;

}


void Ministerio::encabezadoListaDeMultas(ofstream &arch) {

    arch << setfill('=') << setw(200) << "=" << setfill(' ') << endl;
    arch << setw(75) << "RELACION DE EMPRESAS CON INFRACCIONES DE TRANSITO" << endl;
    arch << setfill('-') << setw(200) << "-" << setfill(' ') << endl;
    arch << setw(5) << "DNI" << setw(16) << "NOMBRE"
         << setw(66) << "PLACA DE SUS VEHICULOS" << endl
    ;
    arch << setfill('-') << setw(200) << "-" << setfill(' ') << endl;

}
