#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "vacuna.h"

Vacuna::Vacuna() {

    nombre = nullptr;
    fecha = 0;
    dosis = 0.0;
    colegiatura = nullptr;

}

Vacuna::~Vacuna() {

    delete [] nombre;
    delete [] colegiatura;

}

void Vacuna::cargarNombre(char *cadena) {

    delete [] nombre;
    nombre = new char[strlen(cadena) + 1];
    strcpy(this->nombre,cadena);

}

void Vacuna::obtenerNombre(char *cadena) const {

    if (!nombre) cadena[0] = 0;
    else strcpy(cadena,this->nombre);

}

void Vacuna::cargarFecha(int dato) {

    this->fecha = dato;

}

void Vacuna::obtenerFecha(int &dato) const {

    dato = this->fecha;

}

void Vacuna::cargarDosis(double dato) {

    this->dosis = dato;

}

void Vacuna::obtenerDosis(double &dato) const {

    dato = this->dosis;

}

void Vacuna::cargarColegiatura(char *cadena) {

    delete [] colegiatura;
    colegiatura = new char[strlen(cadena) + 1];
    strcpy(this->colegiatura,cadena);

}

void Vacuna::obtenerColegiatura(char *cadena) const {

    if (!colegiatura) cadena[0] = 0;
    else strcpy(cadena,this->colegiatura);

}

void operator >> (ifstream &arch, class Vacuna &vacuna) {

    int fechaCita;
    double cantidadDosis;
    char caracter;
    char nombreVacuna[50] {}, veterinario[50] {};

    arch >> caracter;
    if (arch.eof()) return;
    arch.getline(nombreVacuna,50,',');
    arch >> fechaCita >> caracter >> cantidadDosis >> caracter;
    arch.getline(veterinario,50,'\n');

    vacuna.cargarNombre(nombreVacuna);
    vacuna.cargarFecha(fechaCita);
    vacuna.cargarDosis(cantidadDosis);
    vacuna.cargarColegiatura(veterinario);

}

void operator << (ofstream &arch, const class Vacuna &vacuna) {

    int fechaCita;
    double cantidadDosis;
    char nombreVacuna[50] {}, veterinario[50] {};

    vacuna.obtenerNombre(nombreVacuna);
    vacuna.obtenerFecha(fechaCita);
    vacuna.obtenerDosis(cantidadDosis);
    vacuna.obtenerColegiatura(veterinario);

    arch << setw(3) << " " << " - " << nombreVacuna << " " << setfill('0') << setw(2)
         << fechaCita % 100 << "/" << setw(2) << (fechaCita / 100) % 100 << "/"
         << setw(2) << fechaCita / 10000 << setfill(' ') << " (" << cantidadDosis << "ml, "
         << veterinario << ")" << endl
    ;

}
