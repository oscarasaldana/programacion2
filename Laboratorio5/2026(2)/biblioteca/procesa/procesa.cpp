#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "../operacion/operaciones.h"
#include "procesa.h"

Procesa::Procesa() {}

Procesa::~Procesa() {}

void Procesa::cargarOperaciones(const char *nombArch) {

    ifstream arch;

    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo Movimientos.csv" << endl;
        exit(1);
    }

    Operaciones operacion;

    int codOperacion, codCliente, dia, mes, año, fecha = 0;
    char caracter;
    char canal[50], tipo[50];

    while (true) {
        arch >> codOperacion;
        if (arch.eof()) break;
        arch >> caracter >> codCliente >> caracter >> dia >> caracter >> mes >> caracter >> año;
        fecha = año * 10000 + mes * 100 + dia;
        arch.get();
        arch.getline(canal,15,',');
        arch.getline(tipo,20,'\n');

        operacion.cargarCodigo(codOperacion);
        operacion.cargarCliente(codCliente);
        operacion.cargarFecha(fecha);
        operacion.cargarCanal(canal);
        operacion.cargarTipo(tipo);
        pilaOperaciones.apilar(operacion);
    }

}

void Procesa::descargaOperaciones(int mes, int año) {

    int fechaLimite = 0;

    fechaLimite = año * 10000 + mes * 100 + 01;
    while (!pilaOperaciones.esPilaVacia()) {
        if (pilaOperaciones.cima() > fechaLimite) {
            pilaOperaciones.desapilar();
        }
        else break;
    }

}

void Procesa::imprimeOperaciones(const char *nombArch) {

    ofstream arch;

    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo Reporte.txt" << endl;
        exit(2);
    }

    arch << "Operaciones almacenadas: " << endl << endl;
    arch << "Codigo" << setw(15) << "Cliente" << setw(15) << "Fecha" << setw(15)
         << "Canal" << setw(15) << "Tipo" << endl
    ;
    arch << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
    while (!pilaOperaciones.esPilaVacia()) {
        pilaOperaciones.mostrarDatos(arch);
        pilaOperaciones.desapilar();
    }

}
