#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "multa.h"

Multa::Multa() {

    placa = nullptr;
    fechaInfraccion = 0;
    fechaPago = 0;
    codigoInfraccion = 0;
    multa = 0.0;

}
Multa::~Multa() {

    delete [] placa;

}

void Multa::cargarPlaca(char *cadena) {

    delete [] placa;
    placa = new char[strlen(cadena) + 1];
    strcpy(this->placa,cadena);

}
void Multa::obtenerPlaca(char *cadena) const {

    if (!placa) cadena[0] = 0;
    strcpy(cadena,this->placa);

}

void Multa::cargarFechaInfraccion(int dato) {

    this->fechaInfraccion = dato;

}

void Multa::obtenerFechaInfraccion(int &dato) const {

    dato = this->fechaInfraccion;

}
void Multa::cargarFechaPago(int dato) {

    this->fechaPago = dato;

}

void Multa::obtenerFechaPago(int &dato) const {

    dato = this->fechaPago;

}

void Multa::cargarCodigoInfraccion(int dato) {

    this->codigoInfraccion = dato;

}

void Multa::obtenerCodigoInfraccion(int &dato) const {

    dato = this->codigoInfraccion;

}

void Multa::cargarMulta(double dato) {

    this->multa = dato;

}

void Multa::obtenerMulta(double &dato) const {

    dato = this->multa;

}

void operator >> (ifstream &arch, class Multa &multa) {

    int diaMulta, mesMulta, añoMulta, diaPago, mesPago, añoPago, codigo;
    char caracter;
    char placa[10] {};

    arch >> diaMulta;
    if (arch.eof()) return;
    arch >> caracter >> mesMulta >> caracter >> añoMulta >> caracter;
    arch.getline(placa,10,',');
    arch >> codigo;
    if (arch.get() != '\n') {
        arch >> caracter >> caracter >> diaPago >> caracter >> mesPago
             >> caracter >> añoPago
        ;
    }
    else {
        diaPago = 0;
        mesPago = 0;
        añoPago = 0;
    }

    multa.cargarPlaca(placa);
    multa.cargarFechaInfraccion(añoMulta * 10000 + mesMulta * 100 + diaMulta);
    multa.cargarFechaPago(añoPago * 10000 + mesPago * 100 + diaPago);
    multa.cargarCodigoInfraccion(codigo);
    multa.cargarMulta(0);

}

void operator << (ofstream &arch, class Multa &multa) {

    int fechaInfraccion, codigo, fechaPago;
    double precio;
    char placa[10] {};

    multa.obtenerPlaca(placa);
    multa.obtenerFechaInfraccion(fechaInfraccion);
    multa.obtenerFechaPago(fechaPago);
    multa.obtenerCodigoInfraccion(codigo);
    multa.obtenerMulta(precio);

    arch << setw(13) << placa << setw(7) << " " << setfill('0')
         << setw(2) << fechaInfraccion % 100 << "/" << setw(2) << (fechaInfraccion / 100) % 100
         << "/" << fechaInfraccion / 10000 << setfill(' ') << setw(20) << codigo << setw(21)
         << precio << setw(9) << " "
    ;
    if (fechaPago != 0) {
        arch << setfill('0') << setw(2) << fechaPago % 100 << "/" << setw(2)
             << (fechaPago / 100) % 100 << "/" << fechaPago / 10000 << setfill(' ') << endl
        ;
    }
    else {
        arch << endl;
    }

}
