#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

#include "cliente.h"

Cliente::Cliente() {

    dni = 0;
    nombre = nullptr;
    distrito = nullptr;
    descuento = 0.0;
    totalPagado = 0.0;

}

Cliente::~Cliente() {

    delete [] nombre;
    delete [] distrito;

}

void Cliente::cargarDni(int dato) {

    this->dni = dato;

}

void Cliente::obtenerDni(int &dato) const {

    dato = this->dni;

}

void Cliente::cargarNombre(char *cadena) {

    delete [] nombre;
    nombre = new char [strlen(cadena) + 1];
    strcpy(this->nombre,cadena);

}

void Cliente::obtenerNombre(char *cadena) const {

    if (!nombre) cadena[0] = 0;
    else strcpy(cadena,this->nombre);

}

void Cliente::cargarDistrito(char *cadena) {

    delete [] distrito;
    distrito = new char [strlen(cadena) + 1];
    strcpy(this->distrito,cadena);

}

void Cliente::obtenerDistrito(char *cadena) const {

    if (!distrito) cadena[0] = 0;
    else strcpy(cadena,this->distrito);

}

void Cliente::cargarDescuento(double dato) {

    this->descuento = dato;

}

void Cliente::obtenerDescuento(double &dato) const {

    dato = this->descuento;

}

void Cliente::cargarTotalPagado(double dato) {

    this->totalPagado = dato;

}

void Cliente::obtenerTotalPagado(double &dato) const {

    dato = this->totalPagado;

}

void operator >> (ifstream &arch, class Cliente &cliente) {

    int dni;
    double descuento;
    char tieneDescuento, caracter;
    char nombre[50] {}, distrito[50] {};

    arch >> dni;
    if (arch.eof()) return;
    arch.get();
    arch.getline(nombre,50,',');
    arch.getline(distrito,50,',');
    arch >> tieneDescuento;
    if (tieneDescuento == 'S') {
        arch >> caracter >> descuento >> caracter;
    }

    cliente.cargarDni(dni);
    cliente.cargarNombre(nombre);
    cliente.cargarDistrito(distrito);
    cliente.cargarDescuento(descuento);
    cliente.cargarTotalPagado(0);

}

void operator << (ofstream &arch, const class Cliente &cliente) {

    static int i = 0;
    int dni;
    double descuento, totalPagado;
    char nombre[50] {}, distrito[50] {};

    cliente.obtenerDni(dni);
    cliente.obtenerNombre(nombre);
    cliente.obtenerDistrito(distrito);
    cliente.obtenerDescuento(descuento);
    cliente.obtenerTotalPagado(totalPagado);
    arch << setfill('0') << setw(3) << i + 1 << setfill(' ') << ")" << setw(7) << " " << left
         << setw(15) << dni << setw(40) << nombre << setw(32) << distrito << fixed << setprecision(2)
         << descuento << setw(10) << "%" << totalPagado * (1 - descuento / 100) << right << endl
    ;
    i++;

}
