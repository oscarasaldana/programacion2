#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "../cliente/cliente.h"
#include "../plato/plato.h"
#include "restaurante.h"

Restaurante::Restaurante() {

    listaDeClientes = nullptr;
    listaDePlatos = nullptr;
    numClientes = 0;
    numPlatos = 0;
    capacidadPlatos = 0;

}

Restaurante::~Restaurante() {

    delete [] listaDeClientes;
    delete [] listaDePlatos;

}

void Restaurante::obtenerCantidadDeClientes(int &dato) const {

    dato = this->numClientes;

}

void Restaurante::obtenerCantidadDePlatos(int &dato) const {

    dato = this->numPlatos;

}

void Restaurante::obtenerCapacidadDePlatos(int &dato) const {

    dato = this->capacidadPlatos;

}

void Restaurante::operator < (const char *nombArch) {

    ifstream arch;

    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo Clientes.csv" << endl;
        exit(1);
    }

    class Cliente clientes[150];

    int dni;
    double descuento, totalPagado;
    char nombre[50] {}, distrito[50] {};

    while (true) {
        arch >> clientes[numClientes];
        if (arch.eof()) break;
        numClientes++;
    }
    listaDeClientes = new Cliente [numClientes];
    for (int i = 0; i < numClientes; i++) {
        clientes[i].obtenerDni(dni);
        clientes[i].obtenerNombre(nombre);
        clientes[i].obtenerDistrito(distrito);
        clientes[i].obtenerDescuento(descuento);
        clientes[i].obtenerTotalPagado(totalPagado);
        listaDeClientes[i].cargarDni(dni);
        listaDeClientes[i].cargarNombre(nombre);
        listaDeClientes[i].cargarDistrito(distrito);
        listaDeClientes[i].cargarDescuento(descuento);
        listaDeClientes[i].cargarTotalPagado(totalPagado);
    }

}

void Restaurante::operator <= (const char *nombArch) {

    ifstream arch;

    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo PlatosOfrecidos.csv" << endl;
        exit(1);
    }

    class Plato platos[150];

    int numPlatosPreparados;
    double precio, descuento, gananciaEsperada;
    char codigo[30] {}, nombre[50] {}, categoria[30] {};

    while (true) {
        arch >> platos[numPlatos];
        if (arch.eof()) break;
        numPlatos++;
    }
    listaDePlatos = new Plato [numPlatos];
    for (int i = 0; i < numPlatos; i++) {
        platos[i].obtenerCodigo(codigo);
        platos[i].obtenerNombre(nombre);
        platos[i].obtenerPrecio(precio);
        platos[i].obtenerCategoria(categoria);
        platos[i].obtenerPreparados(numPlatosPreparados);
        platos[i].obtenerDescuento(descuento);
        platos[i].obtenerTotalEsperado(gananciaEsperada);
        listaDePlatos[i].cargarCodigo(codigo);
        listaDePlatos[i].cargarNombre(nombre);
        listaDePlatos[i].cargarPrecio(precio);
        listaDePlatos[i].cargarCategoria(categoria);
        listaDePlatos[i].cargarPreparados(numPlatosPreparados);
        listaDePlatos[i].cargarDescuento(descuento);
        listaDePlatos[i].cargarAtendidos(0);
        listaDePlatos[i].cargarNoAtendidos(0);
        listaDePlatos[i].cargarTotalEsperado(gananciaEsperada);
        listaDePlatos[i].cargarTotalBruto(0);
        listaDePlatos[i].cargarTotalNeto(0);
    }

}

void Restaurante::operator <<= (const char *nombArch) {

    ifstream arch;

    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo Pedidos.csv" << endl;
        exit(1);
    }

    int numPedido, dni, numPlatosPedidos, posicionCliente = -1, posicionPlato = -1,
        numPlatosPreparados, numPlatosAtendidos, numPlatosNoAtendidos;
    ;
    double precio, gananciaBruta, gananciaNeta, descuento, totalPagadoCliente;
    char caracter;
    char codigoPlato[20] {};

    while (true) {
        arch >> numPedido;
        if (arch.eof()) break;
        arch >> caracter >> dni;
        posicionCliente = encontrarPosicionCliente(dni);
        if (posicionCliente != -1) {
            while (arch.get() != '\n') {
                arch.getline(codigoPlato,20,',');
                arch >> numPlatosPedidos;
                posicionPlato = encontrarPosicionPlato(codigoPlato);
                if (posicionPlato != -1) {
                    listaDePlatos[posicionPlato].obtenerPreparados(numPlatosPreparados);
                    listaDePlatos[posicionPlato].obtenerAtendidos(numPlatosAtendidos);
                    if (numPlatosPreparados > numPlatosAtendidos + numPlatosPedidos) {
                        numPlatosAtendidos += numPlatosPedidos;
                        listaDeClientes[posicionCliente].obtenerTotalPagado(totalPagadoCliente);
                        listaDePlatos[posicionPlato].cargarAtendidos(numPlatosAtendidos);
                        listaDePlatos[posicionPlato].obtenerTotalBruto(gananciaBruta);
                        listaDePlatos[posicionPlato].obtenerTotalNeto(gananciaNeta);
                        listaDePlatos[posicionPlato].obtenerDescuento(descuento);
                        listaDePlatos[posicionPlato].obtenerPrecio(precio);
                        gananciaBruta += numPlatosPedidos * precio;
                        gananciaNeta += numPlatosPedidos * (1 - (descuento / 100)) * precio;
                        listaDePlatos[posicionPlato].cargarTotalBruto(gananciaBruta);
                        listaDePlatos[posicionPlato].cargarTotalNeto(gananciaNeta);
                        totalPagadoCliente += numPlatosPedidos * precio;
                        listaDeClientes[posicionCliente].cargarTotalPagado(totalPagadoCliente);
                    }
                    else {
                        listaDePlatos[posicionPlato].obtenerNoAtendidos(numPlatosNoAtendidos);
                        numPlatosNoAtendidos += numPlatosPedidos;
                        listaDePlatos[posicionPlato].cargarNoAtendidos(numPlatosNoAtendidos);
                    }
                }
            }
        }
        else while (arch.get() != '\n');
    }


}

int Restaurante::encontrarPosicionCliente(const int dni) {

    int dniCliente;

    for (int i = 0; i < numClientes; i++) {
        listaDeClientes[i].obtenerDni(dniCliente);
        if (dniCliente == dni) return i;
    }
    return -1;

}

int Restaurante::encontrarPosicionPlato(const char *codigoPlato) {

    char codigo[30] {};

    for (int i = 0; i < numPlatos; i++) {
        listaDePlatos[i].obtenerCodigo(codigo);
        if (strcmp(codigo,codigoPlato) == 0) return i;
    }
    return -1;

}

void Restaurante::operator >> (const char *nombArch) {

    ofstream arch;

    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo crear el archivo ReportesDeVentaDelDia.txt" << endl;
        exit(2);
    }

    encabezadoDePlatos(arch);
    for (int i = 0; i < numPlatos; i++) {
        arch << listaDePlatos[i];
    }
    arch << setfill('=') << setw(200) << "=" << setfill(' ') << endl;
    encabezadoDeClientes(arch);
    for (int i = 0; i < numClientes; i++) {
        arch << listaDeClientes[i];
    }
    arch << setfill('=') << setw(200) << "=" << setfill(' ') << endl;

}

void Restaurante::encabezadoDePlatos(ofstream &arch) {

    arch << setw(91) << " " << "RESTAURANTE 1INF25" << endl;
    arch << setw(93) << " " << "VENTAS DEL DIA" << endl;
    arch << setfill('=') << setw(200) << "=" << setfill(' ') << endl;
    arch << setw(85) << " " << "RELACION DE LOS PLATOS VENDIDOS" << endl;
    arch << setfill('-') << setw(200) << "-" << setfill(' ') << endl;
    arch << setw(132) << "PLATOS" << setw(46) << "TOTAL" << endl;
    arch << "Nro." << setw(10) << "CODIGO" << setw(14) << "NOMBRE"
         << setw(45) << "PRECIO" << setw(15) << "CATEGORIA" << setw(15) << "DESCUENTO"
         << setw(15) << "PREPARADOS" << setw(15) << "ATENDIDOS" << setw(15) << "NO ATENDIDOS"
         << setw(15) << "ESPERADO" << setw(15) << "BRUTO" << setw(15) << "NETO" << endl
    ;
    arch << setfill('-') << setw(200) << "-" << setfill(' ') << endl;

}

void Restaurante::encabezadoDeClientes(ofstream &arch) {

    arch << setw(86) << " " << "RELACION DE CLIENTES VENDIDOS" << endl;
    arch << setfill('-') << setw(200) << "-" << setfill(' ') << endl;
    arch << "Nro." << setw(10) << "DNI" << setw(18) << "NOMBRE" << setw(42)
         << "DISTRITO" << setw(32) << "DESCUENTO" << setw(16) << "TOTAL PAGADO" << endl
    ;
    arch << setfill('-') << setw(200) << "-" << setfill(' ') << endl;

}
