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
        cout << "ERROR: No se puede acceder al archivo " << nombArch << endl;
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

void cargarClientes(void *&clientes) {

    ifstream arch;

    int numClientes = 0, capacidad = 1;
    int dni;
    char caracter;

    char *nombre;
    void ***ptrClientes = nullptr;

    cargarArchivo("CarpetaDeDatos/Clientes.csv",arch);
    while (true) {
        arch >> dni;
        if (arch.eof()) break;
        arch >> caracter;
        nombre = leerCadenaCaracteres(arch,'\n');
        if (numClientes == capacidad - 1) incrementarCapacidad(ptrClientes,numClientes,capacidad);
        cargarDatosClientes(ptrClientes[numClientes],dni,nombre);
        numClientes++;
    }
    clientes = ptrClientes;

}

char *leerCadenaCaracteres(ifstream &arch, char delimitador) {

    char cadena[150], *ptrCadena;

    arch.getline(cadena,150,delimitador);
    if (arch.eof()) return nullptr;
    ptrCadena = new char [strlen(cadena) + 1];
    strcpy(ptrCadena,cadena);

    return ptrCadena;

}

void incrementarCapacidad(void ***&ptrClientes, int numClientes, int &capacidad) {

    void ***clientes;

    capacidad += Incremento;
    if (!ptrClientes) {
        ptrClientes = new void **[capacidad] {};
    }else {
        clientes = new void **[capacidad] {};
        for (int i = 0; i < numClientes; i++) clientes[i] = ptrClientes[i];
        delete [] ptrClientes;
        ptrClientes = clientes;
    }

}

void cargarDatosClientes(void **&clientes, int dni, char *nombre) {

    int *ptrDni;

    ptrDni = new int;
    *ptrDni = dni;

    clientes = new void *[2] {};
    clientes[0] = ptrDni;
    clientes[1] = nombre;

}


void crearReserva(void *&reserva) {

    ifstream arch;

    int numLibros = 0;
    int cantidad;
    double precio;
    char caracter;

    char *codigo, *nombre, *autor;
    void ***ptrReserva, ***bLibros;

    cargarArchivo("CarpetaDeDatos/Libros.csv",arch);
    bLibros = new void **[270] {};
    while (true) {
        codigo = leerCadenaCaracteres(arch,',');
        if (arch.eof()) break;
        nombre = leerCadenaCaracteres(arch,',');
        autor = leerCadenaCaracteres(arch,',');
        arch >> cantidad >> caracter >> precio;
        arch.get();
        bLibros[numLibros] = cargarDatosLibros(codigo,nombre,autor,cantidad);
        numLibros++;
    }
    ptrReserva = new void **[numLibros + 1] {};
    for (int i = 0; i < numLibros; i++) ptrReserva[i] = bLibros[i];
    reserva = ptrReserva;
    delete [] bLibros;

}

void **cargarDatosLibros(char *codigo, char *nombre, char *autor, int cantidad) {

    int *ptrCantidad;
    void **datosLibro;

    ptrCantidad = new int;
    *ptrCantidad = cantidad;

    datosLibro = new void *[5] {};
    datosLibro[0] = codigo;
    datosLibro[1] = nombre;
    datosLibro[2] = autor;
    datosLibro[3] = nullptr;
    datosLibro[4] = ptrCantidad;

    return datosLibro;

}

void cargarReservas(void *clientes, void *&reserva) {

    ifstream arch;

    int numClientesLibro[270] {}, capacidad[270] {};
    int dni, posicion;
    char caracter;

    char *codigoLibro;
    void ***ptrReserva, **pedido;
    void ***pedidoCliente[270] {};

    cargarArchivo("CarpetaDeDatos/Pedidos2.csv",arch);
    while (true) {
        arch >> dni;
        if (arch.eof()) break;
        arch >> caracter;
        codigoLibro = leerCadenaCaracteres(arch,'\n');
        posicion = encontrarPosicionLibro((void ***)reserva,codigoLibro);
        if (posicion != NoEncontrado) {
            actualizarDatosReserva(pedidoCliente[posicion],numClientesLibro[posicion],capacidad[posicion],
                                   (void ***)clientes,dni)
            ;
            ptrReserva = (void ***)reserva;
            pedido = (void **)ptrReserva[posicion];
            pedido[3] = pedidoCliente[posicion];
        }
    }

}

int encontrarPosicionLibro(void ***ptrReserva, char *codigoLibro) {

    void **datosLibro;

    for (int i = 0; ptrReserva[i] != nullptr; i++) {
        datosLibro = (void **)ptrReserva[i];
        if (strcmp((char *)datosLibro[0],codigoLibro) == 0) return i;
    }
    return NoEncontrado;

}

void actualizarDatosReserva(void ***&pedidosClientes, int &numClientesLibro, int &capacidad,
                            void ***ptrClientes, int dni) {

    int posicion;

    void **cliente, ***listaClientes;

    if (!pedidosClientes or numClientesLibro == capacidad - 1) capacidad += Incremento;

    posicion = encontrarPosicionCliente(ptrClientes,dni);
    cliente = (void **)ptrClientes[posicion];

    if (!pedidosClientes) {
        pedidosClientes = new void **[capacidad] {};
        pedidosClientes[0] = cliente;
    }
    else {
        listaClientes = new void **[capacidad] {};
        for (int i = 0; i < numClientesLibro; i++) listaClientes[i] = pedidosClientes[i];
        listaClientes[numClientesLibro] = cliente;
        delete [] pedidosClientes;
        pedidosClientes = listaClientes;
    }
    numClientesLibro++;

}

int encontrarPosicionCliente(void ***ptrClientes, int dni) {

    void **cliente;

    for (int i = 0; ptrClientes[i]; i++) {
        cliente = (void **)ptrClientes[i];
        if (*(int *)cliente[0] == dni) return i;
    }
    return NoEncontrado;

}

void reporteFinal(void *reserva) {

    ofstream arch;

    void ***ptrReserva, **pedido;

    crearArchivo("CarpetaDeReportes/ReporteFinal.txt",arch);

    arch << "Reporte de Libros Reservados" << endl;
    arch << setfill('=') << setw(50) << "=" << setfill(' ') << endl;

    ptrReserva = (void ***)reserva;
    for (int i = 0 ; ptrReserva[i] != nullptr; i++) {
        pedido = (void **)ptrReserva[i];
        mostrarReservas(arch,pedido);
    }

}

void mostrarReservas(ofstream &arch, void **pedido) {

    char *codigo, *nombre, *autor;
    void ***clientes, **datosCliente;

    codigo = (char *)pedido[0];
    nombre = (char *)pedido[1];
    autor = (char *)pedido[2];
    clientes = (void ***)pedido[3];

    arch << "Libro: " << codigo << endl;
    arch << "Nombre del Libro: " << nombre << endl;
    arch << "Autor: " << autor << endl;
    arch << "DNI" << setw(30) << "Nombre del solicitante" << endl;
    arch << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
    if (!clientes) {
        arch << "No se encuentran clientes para este libro" << endl;
    }else {
        for (int i = 0; clientes[i]; i++) {
            datosCliente = (void **)clientes[i];
            mostrarDatosCliente(arch,datosCliente);
        }
    }
    arch << endl;

}

void mostrarDatosCliente(ofstream &arch, void **datosCliente) {

    int *dni;
    char *nombre;

    dni = (int *)datosCliente[0];
    nombre = (char *)datosCliente[1];

    arch << *dni << setw(3) << " " << nombre << endl;

}
