#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "../vacuna/vacuna.h"
#include "../mascota/mascota.h"
#include "veterinaria.h"

Veterinaria::Veterinaria() {

    listaDeMascotas = nullptr;
    numMascotas = 0;

}

Veterinaria::~Veterinaria() {

    delete [] listaDeMascotas;

}

void Veterinaria::obtenerNumMascotas(int &dato) const {

    dato = this->numMascotas;

}

void Veterinaria::operator <= (const char *nombArch) {

    ifstream arch;

    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo mascotas.csv" << endl;
        exit(1);
    }

    class Mascota mascotas[50];

    int dniCliente, edadMascota;
    double pesoMascota;
    char nombreMascota[50] {}, especieMascota[50] {}, veterinario[50] {};

    while (true) {
        arch >> mascotas[numMascotas];
        if (arch.eof()) break;
        numMascotas++;
    }
    listaDeMascotas = new Mascota [numMascotas];
    for (int i = 0; i < numMascotas; i++) {
        mascotas[i].obtenerDni(dniCliente);
        mascotas[i].obtenerNombre(nombreMascota);
        mascotas[i].obtenerEspecie(especieMascota);
        mascotas[i].obtenerEdad(edadMascota);
        mascotas[i].obtenerPeso(pesoMascota);
        mascotas[i].obtenerColegiatura(veterinario);
        listaDeMascotas[i].cargarDni(dniCliente);
        listaDeMascotas[i].cargarNombre(nombreMascota);
        listaDeMascotas[i].cargarEspecie(especieMascota);
        listaDeMascotas[i].cargarEdad(edadMascota);
        listaDeMascotas[i].cargarPeso(pesoMascota);
        listaDeMascotas[i].cargarColegiatura(veterinario);
    }

}

void Veterinaria::operator <<= (const char *nombArch) {

    ifstream arch;

    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo vacunasAplicadas.csv" << endl;
        exit(1);
    }

    class Vacuna vacuna;

    int dni, posicion = -1;
    char nombreMascota[50] {};

    while (true) {
        arch.getline(nombreMascota,50,',');
        if (arch.eof()) break;
        arch >> dni;
        arch >> vacuna;
        posicion = posicionEncontrada(nombreMascota,dni);
        if (posicion != -1) {
            listaDeMascotas[posicion] += vacuna;
        }
    }

}

int Veterinaria::posicionEncontrada(char *nombre, int dni) const {

    int dniCliente;
    char nombreMascota[50] {};

    for (int i = 0; i < numMascotas; i++) {
        listaDeMascotas[i].obtenerDni(dniCliente);
        listaDeMascotas[i].obtenerNombre(nombreMascota);
        if (strcmp(nombreMascota,nombre) == 0 and dniCliente == dni) return i;
    }
    return -1;

}

void Veterinaria::operator << (const char *nombArch) {

    ofstream arch;

    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo crear el archivo reporteVeterinaria.txt" << endl;
        exit(2);
    }

    int dniCliente, dni = 0;

    arch << setfill('=') << setw(55) << "=" << setfill(' ') << endl;
    arch << "REPORTE DE CARTILLAS - VETERINARIA HUELLITAS Y PLUMITAS" << endl;
    arch << setfill('=') << setw(55) << "=" << setfill(' ') << endl;
    for (int i = 0; i < numMascotas; i++) {
        listaDeMascotas[i].obtenerDni(dniCliente);
        if (dniCliente != dni) {
            arch << "DNI: " << dniCliente << endl;
        }
        arch << listaDeMascotas[i];
        dni = dniCliente;
    }

}
