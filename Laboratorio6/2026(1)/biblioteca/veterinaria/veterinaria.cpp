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

int Veterinaria::obtenerNumMascotas() const {

    return this->numMascotas;

}

void Veterinaria::operator <= (const char *nombArch) {

    ifstream arch;

    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo mascotas.csv" << endl;
        exit(1);
    }

    class Mascota mascotas[50];

    char nombreMascota[50] {}, especieMascota[50] {}, veterinario[50] {};

    while (true) {
        arch >> mascotas[numMascotas];
        if (arch.eof()) break;
        numMascotas++;
    }
    listaDeMascotas = new Mascota [numMascotas];
    for (int i = 0; i < numMascotas; i++) {
        mascotas[i].obtenerNombre(nombreMascota);
        mascotas[i].obtenerEspecie(especieMascota);
        mascotas[i].obtenerColegiatura(veterinario);
        listaDeMascotas[i].cargarDni(mascotas[i].obtenerDni());
        listaDeMascotas[i].cargarNombre(nombreMascota);
        listaDeMascotas[i].cargarEspecie(especieMascota);
        listaDeMascotas[i].cargarEdad(mascotas[i].obtenerEdad());
        listaDeMascotas[i].cargarPeso(mascotas[i].obtenerPeso());
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

int Veterinaria::posicionEncontrada(const char *nombre, const int dni) const {

    char nombreMascota[50] {};

    for (int i = 0; i < numMascotas; i++) {
        listaDeMascotas[i].obtenerNombre(nombreMascota);
        if (strcmp(nombreMascota,nombre) == 0 and listaDeMascotas[i].obtenerDni() == dni) return i;
    }
    return -1;

}

void Veterinaria::operator << (const char *nombArch) const {

    ofstream arch;

    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo crear el archivo reporteVeterinaria.txt" << endl;
        exit(2);
    }

    int dni = 0;

    arch << setfill('=') << setw(55) << "=" << setfill(' ') << endl;
    arch << "REPORTE DE CARTILLAS - VETERINARIA HUELLITAS Y PLUMITAS" << endl;
    arch << setfill('=') << setw(55) << "=" << setfill(' ') << endl;
    for (int i = 0; i < numMascotas; i++) {
        if (listaDeMascotas[i].obtenerDni() != dni) {
            arch << "DNI: " << listaDeMascotas[i].obtenerDni() << endl;
        }
        arch << listaDeMascotas[i];
        dni = listaDeMascotas[i].obtenerDni();
    }

}
