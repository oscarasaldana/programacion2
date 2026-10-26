#include <fstream>
#include <iomanip>

using namespace std;

#include "pila.h"

Pila::Pila() {

    cantidad = 0;

}

Pila::~Pila() {

    while (!esPilaVacia()) desapilar();

}

int Pila::obtenerCantidad() {

    return this->cantidad;

}

void Pila::apilar(class Operaciones &operacion) {

    char canal[50], tipo[50];

    arrPila[cantidad].cargarCodigo(operacion.obtenerCodigo());
    arrPila[cantidad].cargarCliente(operacion.obtenerCliente());
    arrPila[cantidad].cargarFecha(operacion.obtenerFecha());
    operacion.obtenerCanal(canal);
    operacion.obtenerTipo(tipo);
    arrPila[cantidad].cargarCanal(canal);
    arrPila[cantidad].cargarTipo(tipo);
    cantidad++;

}

void Pila::desapilar() {

    if (!esPilaVacia()) {
        arrPila[cantidad - 1].liberarEspacio();
        cantidad--;
    }

}

bool Pila::esPilaVacia() {

    if (cantidad == 0) return true;
    return false;

}

int Pila::cima() {

    if (!esPilaVacia()) {
        return arrPila[cantidad - 1].obtenerFecha();
    }

}

void Pila::mostrarDatos(ofstream &arch) {

    char canal[50] {}, tipo[50] {};
    int posicion = 0;

    arch << left << setw(15) << arrPila[cantidad - 1].obtenerCodigo()
         << setw(14) << arrPila[cantidad - 1].obtenerCliente() << right
    ;
    arch << setfill('0') << setw(2) << arrPila[cantidad - 1].obtenerFecha() % 100
         << "." << setw(2) << (arrPila[cantidad - 1].obtenerFecha() / 100) % 100
         << "." << arrPila[cantidad - 1].obtenerFecha() / 10000 << setfill(' ')
    ;
    arrPila[cantidad - 1].obtenerCanal(canal);
    arrPila[cantidad - 1].obtenerTipo(tipo);
    arch << setw(6) << " " << left << setw(15) << canal << tipo << endl;

}
