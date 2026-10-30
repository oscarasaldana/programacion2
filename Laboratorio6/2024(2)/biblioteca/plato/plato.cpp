#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "plato.h"

Plato::Plato() {

    codigo = nullptr;
    nombre = nullptr;
    precio = 0.0;
    categoria = nullptr;
    preparados = 0;
    descuento = 0.0;
    atendidos = 0;
    noAtendidos = 0;
    totalBruto = 0.0;
    totalEsperado = 0.0;
    totalNeto = 0.0;

}

Plato::~Plato() {

    delete [] codigo;
    delete [] nombre;
    delete [] categoria;

}

void Plato::cargarCodigo(char *cadena) {

    delete [] codigo;
    codigo = new char[strlen(cadena) + 1];
    strcpy(this->codigo,cadena);

}

void Plato::obtenerCodigo(char *cadena) const {

    if (!codigo) cadena[0] = 0;
    else strcpy(cadena,this->codigo);

}

void Plato::cargarNombre(char *cadena) {

    delete [] nombre;
    nombre = new char[strlen(cadena) + 1];
    strcpy(this->nombre,cadena);

}

void Plato::obtenerNombre(char *cadena) const {

    if (!nombre) cadena[0] = 0;
    else strcpy(cadena,this->nombre);

}

void Plato::cargarPrecio(double dato) {

    this->precio = dato;

}

void Plato::obtenerPrecio(double &dato) const {

    dato = this->precio;

}

void Plato::cargarCategoria(char *cadena) {

    delete [] categoria;
    categoria = new char[strlen(cadena) + 1];
    strcpy(this->categoria,cadena);

}

void Plato::obtenerCategoria(char *cadena) const {

    if (!categoria) cadena[0] = 0;
    else strcpy(cadena,this->categoria);


}

void Plato::cargarPreparados(int dato) {

    this->preparados = dato;

}

void Plato::obtenerPreparados(int &dato) const {

    dato = this->preparados;

}

void Plato::cargarDescuento(double dato) {

    this->descuento = dato;

}

void Plato::obtenerDescuento(double &dato) const {

    dato = this->descuento;

}

void Plato::cargarAtendidos(int dato) {

    this->atendidos = dato;

}

void Plato::obtenerAtendidos(int &dato) const {

    dato = this->atendidos;

}

void Plato::cargarNoAtendidos(int dato) {

    this->noAtendidos = dato;

}

void Plato::obtenerNoAtendidos(int &dato) const {

    dato = this->noAtendidos;

}

void Plato::cargarTotalEsperado(double dato) {

    this->totalEsperado = dato;

}

void Plato::obtenerTotalEsperado(double &dato) const {

    dato = this->totalEsperado;

}

void Plato::cargarTotalBruto(double dato) {

    this->totalBruto = dato;

}

void Plato::obtenerTotalBruto(double &dato) const {

    dato = this->totalBruto;

}

void Plato::cargarTotalNeto(double dato) {

    this ->totalNeto = dato;

}

void Plato::obtenerTotalNeto(double &dato) const {

    dato = this->totalNeto;

}

void operator >> (ifstream &arch, class Plato &plato) {

    int numPlatosPreparados;
    double precio, descuento;
    char caracter;
    char codigo[30] {}, nombre[50] {}, categoria[30] {};

    arch.getline(codigo,30,',');
    if (arch.eof()) return;
    arch.getline(nombre,50,',');
    arch >> precio >> caracter;
    arch.getline(categoria,30,',');
    arch >> numPlatosPreparados;
    if (arch.get() != '\n') {
        arch >> caracter >> descuento >> caracter;
        plato.cargarDescuento(descuento);
    }
    else {
        plato.cargarDescuento(0);
    }
    arch.get();

    plato.cargarCodigo(codigo);
    plato.cargarNombre(nombre);
    plato.cargarPrecio(precio);
    plato.cargarCategoria(categoria);
    plato.cargarPreparados(numPlatosPreparados);
    plato.cargarAtendidos(0);
    plato.cargarNoAtendidos(0);
    plato.cargarTotalEsperado(numPlatosPreparados * precio);
    plato.cargarTotalBruto(0);
    plato.cargarTotalNeto(0);

}

void operator << (ofstream &arch, const class Plato &plato) {

    static int i = 0;
    int numPlatosPreparados, numPlatosAtendidos, numPlatosNoAtendidos;
    double precio, descuento, gananciaEsperada, gananciaBruta, gananciaNeta;
    char codigoPlato[20] {}, nombrePlato[50] {}, categoria[30] {};

    plato.obtenerCodigo(codigoPlato);
    plato.obtenerNombre(nombrePlato);
    plato.obtenerPrecio(precio);
    plato.obtenerCategoria(categoria);
    plato.obtenerDescuento(descuento);
    plato.obtenerPreparados(numPlatosPreparados);
    plato.obtenerAtendidos(numPlatosAtendidos);
    plato.obtenerNoAtendidos(numPlatosNoAtendidos);
    plato.obtenerTotalEsperado(gananciaEsperada);
    plato.obtenerTotalBruto(gananciaBruta);
    plato.obtenerTotalNeto(gananciaNeta);
    arch << setfill('0') << setw(3) << i + 1 << setfill(' ') << ")" << setw(4)
         << " " << left << setw(14) << codigoPlato << setw(46) << nombrePlato
         << setw(11) << precio << setw(17) << categoria << fixed << setprecision(2)
         << descuento << setw(11) << "%" << setw(15) << numPlatosPreparados
         << setw(15) << numPlatosAtendidos << setw(14) << numPlatosNoAtendidos
         << setw(17) << gananciaEsperada << setw(15) << gananciaBruta
         << gananciaNeta << right << endl
    ;
    i++;

}
