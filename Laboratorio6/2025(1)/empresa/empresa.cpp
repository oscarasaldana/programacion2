#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "../multa/multa.h"
#include "empresa.h"

Empresa::Empresa() {

    dni = 0;
    nombre = nullptr;
    numPlacas = 0;
    numMultas = 0;

}

Empresa::~Empresa() {

    delete [] nombre;
    for (int i = 0; i < numPlacas; i++) delete [] placas[i];

}

void Empresa::cargarDni(int dato) {

    this->dni = dato;

}

void Empresa::obtenerDni(int &dato) const {

    dato = this->dni;

}

void Empresa::cargarNombre(char *cadena) {

    delete [] nombre;
    nombre = new char[strlen(cadena) + 1];
    strcpy(this->nombre,cadena);

}

void Empresa::obtenerNombre(char *cadena) const {

    if (!nombre) cadena[0] = 0;
    else strcpy(cadena,this->nombre);

};

void Empresa::cargarPlaca(const char *cadena) {

    placas[numPlacas] = new char [strlen(cadena) + 1] {};
    strcpy(this->placas[numPlacas],cadena);
    numPlacas++;

}

void Empresa::obtenerPlaca(char *cadena, const int posicion) const {

    if (!placas[posicion]) cadena[0] = 0;
    else strcpy(cadena,this->placas[posicion]);

}

void Empresa::obtenerNumPlacas(int &dato) const {

    dato = this->numPlacas;

}

void Empresa::obtenerNumMultas(int &dato) const {

    dato = this->numMultas;

}

void operator >> (ifstream &arch, class Empresa &empresa) {

    int dni, numPlacas;
    char nombre[50] {}, *placas[10] {}, placa[9] {};

    arch >> dni;
    if (arch.eof()) return;
    arch.get();
    arch.getline(nombre,50,',');
    while (true) {
        empresa.obtenerNumPlacas(numPlacas);
        placas[numPlacas] = new char [9] {};
        arch.get(placa,9);
        strcpy(placas[numPlacas],placa);
        empresa.cargarPlaca(placas[numPlacas]);
        if (arch.get() == '\n') break;
    }
    empresa.cargarDni(dni);
    empresa.cargarNombre(nombre);

}

void Empresa::operator += (class Multa &multa) {

    int codigo, fechaInfraccion, fechaPago;
    double precio;
    char placa[10] {};

    multa.obtenerCodigoInfraccion(codigo);
    multa.obtenerFechaInfraccion(fechaInfraccion);
    multa.obtenerFechaPago(fechaPago);
    multa.obtenerPlaca(placa);
    multa.obtenerMulta(precio);
    listaDeMultas[numMultas].cargarPlaca(placa);
    listaDeMultas[numMultas].cargarFechaInfraccion(fechaInfraccion);
    listaDeMultas[numMultas].cargarFechaPago(fechaPago);
    listaDeMultas[numMultas].cargarCodigoInfraccion(codigo);
    listaDeMultas[numMultas].cargarMulta(precio);
    numMultas++;

}

void operator << (ofstream &arch, class Empresa &empresa) {

    int dni, numPlacas, numMultas;
    char nombre[50] {}, placa[10] {};

    empresa.obtenerDni(dni);
    empresa.obtenerNombre(nombre);

    arch << setw(10) << dni << setw(5) << " " << left << setw(50) << nombre << right;
    empresa.obtenerNumPlacas(numPlacas);
    for (int i = 0; i < numPlacas; i++) {
        empresa.obtenerPlaca(placa,i);
        arch << placa << "  ";
    }
    arch << endl;
    arch << setw(10) << "Placa" << setw(25) << "Fecha de infraccion" << setw(25) << "Codigo de infraccion"
         << setw(10) << "Multa" << setw(20) << "Fecha de pago" << endl
    ;
    empresa.obtenerNumMultas(numMultas);
    for (int i = 0; i < numMultas; i++) {
        empresa.imprimirListaDeMultas(arch,i);
    }

}

void Empresa::imprimirListaDeMultas(ofstream &arch, int i) {

    arch << listaDeMultas[i];

}
