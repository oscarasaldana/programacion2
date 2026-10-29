#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "infraccion.h"

Infraccion::Infraccion() {

    codigo = 0;
    descripcion = nullptr;
    gravedad = nullptr;
    multa = 0.0;

}

Infraccion::~Infraccion() {

    delete [] descripcion;
    delete [] gravedad;

}

void Infraccion::cargarCodigo(int dato) {

    this->codigo = dato;

}

void Infraccion::obtenerCodigo(int &dato) const {

    dato = this->codigo;

}

void Infraccion::cargarDescripcion(char *cadena) {

    delete [] descripcion;
    descripcion = new char[strlen(cadena) + 1];
    strcpy(this->descripcion,cadena);

}

void Infraccion::obtenerDescripcion(char *cadena) const {

    if (!descripcion) cadena[0] = 0;
    else strcpy(cadena,this->descripcion);

}

void Infraccion::cargarGravedad(char *cadena) {

    delete [] gravedad;
    gravedad = new char[strlen(cadena) + 1];
    strcpy(this->gravedad,cadena);

}

void Infraccion::obtenerGravedad(char *cadena) const {

    if (!gravedad) cadena[0] = 0;
    else strcpy(cadena,this->gravedad);

}

void Infraccion::cargarMulta(double dato) {

    this->multa = dato;

}

void Infraccion::obtenerMulta(double &dato) const {

    dato = this->multa;

}

void operator >> (ifstream &arch, class Infraccion &infraccion) {

    int codigo;
    double precio;
    char caracter;
    char gravedad[50] {}, descripcion[200] {};

    arch >> codigo;
    if (arch.eof()) return;
    arch >> caracter >> precio >> caracter;
    arch.getline(gravedad,50,',');
    arch.getline(descripcion,200,'\n');

    infraccion.cargarCodigo(codigo);
    infraccion.cargarMulta(precio);
    infraccion.cargarGravedad(gravedad);
    infraccion.cargarDescripcion(descripcion);

}

void operator << (ofstream &arch, class Infraccion &infraccion) {

    int codigo;
    double precio;
    char gravedad[50] {}, descripcion[200] {};

    infraccion.obtenerCodigo(codigo);
    infraccion.obtenerMulta(precio);
    infraccion.obtenerGravedad(gravedad);
    infraccion.obtenerDescripcion(descripcion);
    arch << setw(7) << codigo << setw(16) << precio << setw(12) << " "
         << left << setw(17) << gravedad << descripcion << right << endl
    ;

}
