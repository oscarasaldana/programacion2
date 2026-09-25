#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "funciones.h"

#define Incremento (5)
#define NoEncontrado (-1)

void cargarArchivo(const char *nombArch, ifstream &arch) {

    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo " << nombArch << endl;
        exit(1);
    }

}

void crearArchivo(const char *nombArch, ofstream &arch) {

    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo crear el archivo " << nombArch << endl;
        exit(2);
    }

}

void cargarPacientes(const char *nombArch, void *&pacientes) {

    ifstream arch;

    int numPacientes = 0, capacidad = 1;
    int edad;
    long long idPaciente;
    char genero, caracter;

    char *nombre;
    void ***ptrPacientes = nullptr;

    cargarArchivo(nombArch,arch);
    while (true) {
        arch >> idPaciente;
        if (arch.eof()) break;
        arch.get();
        nombre = leerCadenaCaracteres(arch,',');
        arch >> edad >> caracter >> genero;
        if (numPacientes == capacidad - 1) incrementarCapacidad(ptrPacientes,numPacientes,capacidad);
        cargarDatosPacientes(ptrPacientes[numPacientes],idPaciente,nombre,edad,genero);
        numPacientes++;
    }
    pacientes = ptrPacientes;

}

char *leerCadenaCaracteres(ifstream &arch, char delim) {

    char cadena[100], *ptrCadena;

    arch.getline(cadena,100,delim);
    if (arch.eof()) return nullptr;
    ptrCadena = new char [strlen(cadena) + 1];
    strcpy(ptrCadena,cadena);

    return ptrCadena;


}

void incrementarCapacidad(void ***&ptrPacientes, int numPacientes, int &capacidad) {

    void ***pacientes;

    capacidad += Incremento;
    if (!ptrPacientes) {
        ptrPacientes = new void **[capacidad] {};
    }else {
        pacientes = new void **[capacidad] {};
        for (int i = 0; i < numPacientes; i++) pacientes[i] = ptrPacientes[i];
        delete [] ptrPacientes;
        ptrPacientes = pacientes;
    }

}

void cargarDatosPacientes(void **&pacientes, long long idPaciente, char *nombre, int edad, char genero) {

    int *ptrEdad;
    char *ptrGenero;
    long long *ptrIdPaciente;

    ptrEdad = new int;
    ptrGenero = new char;
    ptrIdPaciente = new long long;
    *ptrEdad = edad;
    *ptrGenero = genero;
    *ptrIdPaciente = idPaciente;

    pacientes = new void *[6] {};
    pacientes[0] = ptrIdPaciente;
    pacientes[1] = nombre;
    pacientes[2] = ptrEdad;
    pacientes[3] = ptrGenero;
    pacientes[4] = nullptr;
    pacientes[5] = nullptr;

}

void cargarVisitas(const char *nombArch, void *&pacientes) {

    ifstream arch;

    int posicion;
    int diaA, mesA, añoA, hora, min;
    double precio;
    long long idPaciente;
    char caracter;

    int numCitas[60] {}, capacidad[60] {};
    double precioTotal[60] {}, *ptrPrecioTotal[60] {};
    void ***ptrPacientes, **paciente, **citas[51] {};

    cargarArchivo(nombArch,arch);
    ptrPacientes = (void ***)pacientes;
    while (true) {
        arch >> diaA;
        if (arch.eof()) break;
        arch >> caracter >> mesA >> caracter >> añoA >> caracter >> hora >> caracter >> min
             >> caracter >> idPaciente >> caracter >> precio
        ;
        posicion = encontrarPosicion(ptrPacientes,idPaciente);
        if (posicion != NoEncontrado) {
            paciente = (void **)ptrPacientes[posicion];
            cargarDatosCita(citas[posicion],diaA,mesA,añoA,hora,min,precio,precioTotal[posicion],
                             numCitas[posicion],capacidad[posicion])
            ;
            paciente[4] = citas[posicion];
            ptrPrecioTotal[posicion] = new double;
            *ptrPrecioTotal[posicion] = precioTotal[posicion];
            paciente[5] = ptrPrecioTotal[posicion];
        }
    }

}

int encontrarPosicion(void ***ptrPacientes, long long idPaciente) {

    void **paciente;

    for (int i = 0; ptrPacientes[i]; i++) {
        paciente = (void **)ptrPacientes[i];
        if (*(long long *)paciente[0] == idPaciente) return i;
    }
    return NoEncontrado;

}

void cargarDatosCita(void **&citas, int dia, int mes, int año, int hora, int min, double precio,
                     double &precioTotal, int &numCitas, int &capacidad) {

    int *ptrFecha, *ptrHora;
    double *ptrPrecio;
    void **ptrCitas, **datosCita;

    if (!citas or numCitas == capacidad - 1) {
        capacidad += Incremento;
    }

    ptrFecha = new int;
    ptrHora = new int;
    ptrPrecio = new double;
    *ptrFecha = generarFecha(dia,mes,año);
    *ptrHora = generarHora(hora,min);
    *ptrPrecio = precio;

    datosCita = new void *[3] {};
    datosCita[0] = ptrFecha;
    datosCita[1] = ptrHora;
    datosCita[2] = ptrPrecio;

    if (!citas) {
        citas = new void *[capacidad] {};
        citas[numCitas] = datosCita;
    }else {
        ptrCitas = new void *[capacidad] {};
        for (int i = 0; i < numCitas; i++) ptrCitas[i] = citas[i];
        ptrCitas[numCitas] = datosCita;
        delete [] citas;
        citas = ptrCitas;
    }
    precioTotal += precio;
    numCitas++;

}

int generarFecha(int dia, int mes, int año) {

    return año *10000 + mes *100 + dia;

}

int generarHora(int hora, int min) {

    return hora * 60 + min;

}

void generarReportes(const char *nombArch, void *pacientes) {

    ofstream arch;

    void ***ptrPacientes, **paciente;

    crearArchivo(nombArch,arch);
    ptrPacientes = (void ***)pacientes;

    arch << setfill('=') << setw(100) << "=" << setfill(' ') << endl;
    arch << setw(65) << "REPORTE DEL SISTEMA DE URGENCIAS" << endl;
    arch << setfill('=') << setw(100) << "=" << setfill(' ') << endl;
    arch << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
    arch << "ID" << setw(22) << "Nombre" << setw(20) << "Edad" << setw(15) << "Genero"
         << setw(15) << "Visitas" << setw(20) << "Total(S/)" << endl
    ;
    arch << setfill('-') << setw(100) << "-" << setfill(' ') << endl;

    for (int i = 0; ptrPacientes[i]; i++) {
        paciente = (void **)ptrPacientes[i];
        imprimirPacientes(arch,paciente);
    }

}

void imprimirPacientes(ofstream &arch, void **paciente) {

    int contador;

    int *ptrEdad;
    double *ptrPrecioTotal;
    char *ptrNombre, *ptrGenero;
    long long *ptrIdPaciente;
    void **citas;

    ptrIdPaciente = (long long *)paciente[0];
    ptrNombre = (char *)paciente[1];
    ptrEdad = (int *)paciente[2];
    ptrGenero = (char *)paciente[3];
    citas = (void **)paciente[4];
    ptrPrecioTotal = (double *)paciente[5];

    arch << left << setw(15) << *ptrIdPaciente << left << setw(15) << ptrNombre << right
         << setw(13) << *ptrEdad << right << setw(13) << *ptrGenero;
    contador = 0;
    if (!citas) arch << right << setw(15) << "0";
    else {
        for (int i = 0; citas[i]; i++) contador++;
        arch << right << setw(15) << contador;
    }
    arch << right << setw(20) << *ptrPrecioTotal << endl;

}
