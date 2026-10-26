#include <iostream>
#include <cstring>

using namespace std;

#include "operaciones.h"

Operaciones::Operaciones() {

    codigo = 0;
    cliente = 0;
    fecha = 0;
    canal = nullptr;
    tipo = nullptr;

}

Operaciones::~Operaciones() {

    liberarEspacio();

}

void Operaciones::liberarEspacio() {

    if (canal) delete [] canal;
    if (tipo) delete [] tipo;
    canal = nullptr;
    tipo = nullptr;

}

void Operaciones::cargarCodigo(int dato) {

    this->codigo = dato;

}

int Operaciones::obtenerCodigo() const {

    return this->codigo;

}

void Operaciones::cargarCliente(int dato) {

    this->cliente = dato;

}

int Operaciones::obtenerCliente() const {

    return this->cliente;

}

void Operaciones::cargarFecha(int dato) {

    this->fecha = dato;

}

int Operaciones::obtenerFecha() const {

    return this->fecha;

}

void Operaciones::cargarCanal(char *cadena) {

    if (canal) delete [] canal;
    canal = new char [strlen(cadena) + 1];
    strcpy(this->canal,cadena);

}

void Operaciones::obtenerCanal(char *cadena) const {

    if (!canal) cadena[0] = 0;
    else strcpy(cadena,this->canal);

}

void Operaciones::cargarTipo(char *cadena) {

    if (tipo) delete [] tipo;
    tipo = new char [strlen(cadena) + 1];
    strcpy(this->tipo,cadena);

}

void Operaciones::obtenerTipo(char *cadena) const {

    if (!tipo) cadena[0] = 0;
    else strcpy(cadena,this->tipo);

}
