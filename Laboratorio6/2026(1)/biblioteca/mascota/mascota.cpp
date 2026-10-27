#include <fstream>
#include <cstring>

using namespace std;

#include "mascota.h"

Mascota::Mascota() {

    dni = 0;
    nombre = nullptr;
    especie = nullptr;
    edad = 0;
    peso = 0.0;
    colegiatura = nullptr;
    numVacunas = 0;

}

Mascota::~Mascota() {

    delete [] nombre;
    delete [] especie;
    delete [] colegiatura;

}

void Mascota::cargarDni(int dato) {

    this->dni = dato;

}

void Mascota::obtenerDni(int &dato) const {

    dato = this->dni;

}

void Mascota::cargarNombre(char *cadena) {

    delete [] nombre;
    nombre = new char [strlen(cadena) + 1];
    strcpy(this->nombre,cadena);

}

void Mascota::obtenerNombre(char *cadena) const {

    if (!nombre) cadena[0] = 0;
    else strcpy(cadena,this->nombre);

}

void Mascota::cargarEspecie(char *cadena) {

    delete [] especie;
    especie = new char [strlen(cadena) + 1];
    strcpy(this->especie,cadena);

}

void Mascota::obtenerEspecie(char *cadena) const {

    if (!especie) cadena[0] = 0;
    else strcpy(cadena,this->especie);

}

void Mascota::cargarEdad(int dato) {

    this->edad = dato;

}

void Mascota::obtenerEdad(int &dato) const {

    dato = this->edad;

}

void Mascota::cargarPeso(double dato) {

    this->peso = dato;

}

void Mascota::obtenerPeso(double &dato) const {

    dato = this->peso;

}

void Mascota::cargarColegiatura(char *cadena) {

    delete [] colegiatura;
    colegiatura = new char [strlen(cadena) + 1];
    strcpy(this->colegiatura,cadena);

}

void Mascota::obtenerColegiatura(char *cadena) const {

    if (!colegiatura) cadena[0] = 0;
    else strcpy(cadena,this->colegiatura);

}

void operator >> (ifstream &arch, class Mascota &mascota) {

    int dniCliente, edadMascota;
    double pesoMascota;
    char caracter;
    char nombreMascota[50] {}, especieMascota[50] {}, veterinario[50] {};

    arch >> dniCliente;
    if (arch.eof()) return;
    arch.get();
    arch.getline(nombreMascota,50,',');
    arch.getline(especieMascota,50,',');
    arch >> edadMascota >> caracter >> pesoMascota >> caracter;
    arch.getline(veterinario,50,'\n');

    mascota.cargarDni(dniCliente);
    mascota.cargarNombre(nombreMascota);
    mascota.cargarEspecie(especieMascota);
    mascota.cargarEdad(edadMascota);
    mascota.cargarPeso(pesoMascota);
    mascota.cargarColegiatura(veterinario);

}

void Mascota::operator += (const class Vacuna &vacuna) {

    int fechaCita;
    double cantidadDosis;
    char nombreVacuna[50] {}, veterinario[50] {};

    vacuna.obtenerNombre(nombreVacuna);
    vacuna.obtenerFecha(fechaCita);
    vacuna.obtenerDosis(cantidadDosis);
    vacuna.obtenerColegiatura(veterinario);
    listaDeVacunas[numVacunas].cargarNombre(nombreVacuna);
    listaDeVacunas[numVacunas].cargarFecha(fechaCita);
    listaDeVacunas[numVacunas].cargarDosis(cantidadDosis);
    listaDeVacunas[numVacunas].cargarColegiatura(veterinario);
    numVacunas++;

}

bool Mascota::operator ~ () const{

    int fechaCita, fechaCitaSiguiente;
    double cantidadDosis, cantidadDosisSiguiente;
    char nombreVacuna[50] {}, nombreVacunaSiguiente[50] {};
    char veterinario[50] {}, veterinarioSiguiente[50]{};

    for (int i = 0; i < numVacunas; i++) {
        listaDeVacunas[i].obtenerNombre(nombreVacuna);
        listaDeVacunas[i].obtenerFecha(fechaCita);
        listaDeVacunas[i].obtenerDosis(cantidadDosis);
        listaDeVacunas[i].obtenerColegiatura(veterinario);
        listaDeVacunas[i + 1].obtenerNombre(nombreVacunaSiguiente);
        listaDeVacunas[i + 1].obtenerFecha(fechaCitaSiguiente);
        listaDeVacunas[i + 1].obtenerDosis(cantidadDosisSiguiente);
        listaDeVacunas[i + 1].obtenerColegiatura(veterinarioSiguiente);
        if (strcmp(nombreVacuna,nombreVacunaSiguiente) == 0 and fechaCita == fechaCitaSiguiente and
            strcmp(veterinario,veterinarioSiguiente) == 0 and cantidadDosis == cantidadDosisSiguiente) {
            return true;
        }
    }
    return false;

}

void operator << (ofstream &arch, class Mascota &mascota) {

    int edadMascota, numVacunas;
    double pesoMascota;
    char nombreMascota[50] {}, especieMascota[50] {};

    mascota.obtenerNombre(nombreMascota);
    mascota.obtenerEspecie(especieMascota);
    mascota.obtenerEdad(edadMascota);
    mascota.obtenerPeso(pesoMascota);

    arch << "Mascota: " << nombreMascota << " (" << especieMascota << ", "
         << edadMascota << " años, " << pesoMascota << "kg)" << endl
    ;
    if (~mascota) {
        arch << " ** ALERTA: Cartilla con registros duplicados ** " << endl << endl;
    }
    mascota.imprimirVacunas(arch);

}

void Mascota::imprimirVacunas(ofstream &arch) {

    for (int i = 0; i < numVacunas; i++) {
        arch << listaDeVacunas[i];
    }
    arch << endl;

}
