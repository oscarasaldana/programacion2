#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "funciones.h"

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

void lecturaDeLibros(const char *nombArch, char ***&libros, int **&inventario) {

    ifstream arch;

    int numDatos = 0;
    int *bInventario[280];
    char **bLibros[280];

    cargarArchivo(nombArch,arch);
    while (true) {
        bLibros[numDatos] = leerDatosLibros(arch);
        if (arch.eof()) break;
        bInventario[numDatos] = leerDatosInventario(arch);
        numDatos++;
    }
    libros = new char **[numDatos + 1] {};
    inventario = new int *[numDatos + 1] {};
    for (int i = 0; i < numDatos; i++) {
        libros[i] = bLibros[i];
        inventario[i] = bInventario[i];
    }

}

char **leerDatosLibros(ifstream &arch) {

    char *codigo, *nombre, *autor;
    char **datosLibro;

    codigo = leerCadenaCaracteres(arch,',');
    if (!codigo) return nullptr;
    nombre = leerCadenaCaracteres(arch,',');
    autor = leerCadenaCaracteres(arch,',');
    datosLibro = new char *[4] {};
    datosLibro[0] = codigo;
    datosLibro[1] = nombre;
    datosLibro[2] = autor;

    return datosLibro;

}

char *leerCadenaCaracteres(ifstream &arch, char delim) {

    char cadena[100], *ptrCadena;

    arch.getline(cadena,100,delim);
    if (arch.eof()) return nullptr;
    ptrCadena = new char [strlen(cadena) + 1];
    strcpy(ptrCadena,cadena);

    return ptrCadena;

}

int *leerDatosInventario(ifstream &arch) {

    int cantidad;
    double precio;
    char caracter;

    int *datosInventario;

    arch >> cantidad >> caracter >> precio;
    arch.get();
    datosInventario = new int [2] {};
    datosInventario[0] = cantidad;

    return datosInventario;

}

void pruebaDeLecturaDeLibros(const char *nombArch, char ***libros, int **inventario) {

    ofstream arch;

    crearArchivo(nombArch,arch);

    arch << setw(40) << "REPORTE DE PRUEBA" << endl;
    arch << setfill('=') << setw(90) << "=" << setfill(' ') << endl;
    for (int i = 0; libros[i] != nullptr; i++) {
        arch << libros[i][0] << " - " << libros[i][1] << " - " << libros[i][2] << " - "
             << inventario[i][0] << " - " << inventario[i][1] << endl
        ;
    }

}

void atencionDePedidos(const char *nombArch, char ***&libros, int **&inventario, int **&pedidosClientes,
                       char ***&pedidosLibros, bool **&pedidosAtendidos) {

    ifstream arch;

    int numClientes = 0, contador = 0;
    int idPedido, dni, posicionDni;
    char codigo[8], *ptrCodigo, caracter;

    int *bPedidosClientes[180] {};
    char **bPedidosLibros[180] {};

    cargarArchivo(nombArch,arch);
    while (true) {
        arch >> idPedido;
        if (arch.eof()) break;
        arch >> caracter >> dni;
        posicionDni = encontrarPosicion(bPedidosClientes,dni);
        if (posicionDni == NoEncontrado) {
            cargarPedidosClientes(bPedidosClientes[numClientes],dni,idPedido);
            numClientes++;
        }else {
            ingresarNuevoPedido(bPedidosClientes[posicionDni],idPedido);
        }
        bPedidosLibros[idPedido - 1] = new char *[2] {};
        while (arch.get() != '\n') {
            arch >> ws;
            arch.get(codigo,8);
            ptrCodigo = new char [strlen(codigo) + 1];
            strcpy(ptrCodigo,codigo);
            cargarPedidosLibros(bPedidosLibros[idPedido - 1],ptrCodigo);
        }
    }
    for (int i = 0; bPedidosLibros[i] != nullptr; i++) contador++;
    pedidosClientes = new int *[numClientes + 1] {};
    pedidosLibros = new char **[contador + 1] {};
    for (int i = 0; i < numClientes; i++) pedidosClientes[i] = bPedidosClientes[i];
    for (int i = 0; i < contador; i++) pedidosLibros[i] = bPedidosLibros[i];
    cargarPedidosAtenciones(pedidosAtendidos,contador,pedidosLibros,
                            inventario,libros);

}

int encontrarPosicion(int **bPedidosClientes, int dni) {

    for (int i = 0; bPedidosClientes[i] != nullptr; i++) {
        if (bPedidosClientes[i][0] == dni) return i;
    }
    return NoEncontrado;

}

void cargarPedidosClientes(int *&bPedidosClientes, int dni, int idPedido) {

    bPedidosClientes = new int [4] {};
    bPedidosClientes[0] = dni;
    bPedidosClientes[1] = 1;
    bPedidosClientes[2] = idPedido;

}

void ingresarNuevoPedido(int *&bPedidosClientes, int idPedido) {

    int contador = 0;
    int *pedidosCliente;

    for (int i = 0; bPedidosClientes[i] != 0; i++) contador ++;
    pedidosCliente = new int [contador + 2] {};
    pedidosCliente[0] = bPedidosClientes[0];
    pedidosCliente[1] = contador - 1;
    for (int i = 2; i < contador; i++) pedidosCliente[i] = bPedidosClientes[i];
    pedidosCliente[contador] = idPedido;
    pedidosCliente[contador + 1] = 0;
    delete [] bPedidosClientes;
    bPedidosClientes = pedidosCliente;

}

void cargarPedidosLibros(char **&bPedidosLibros, char *codigo) {

    int contador = 0;
    char **pedidoLibros;

    if (!bPedidosLibros) {
        bPedidosLibros[1] = codigo;
    }else {
        for (int i = 0; bPedidosLibros[i] != nullptr; i++) contador++;
        pedidoLibros = new char *[contador + 2] {};
        for (int i = 0; i < contador; i++) pedidoLibros[i] = bPedidosLibros[i];
        pedidoLibros[contador] = codigo;
        pedidoLibros[contador + 1] = nullptr;
        delete [] bPedidosLibros;
        bPedidosLibros = pedidoLibros;
    }

}

void cargarPedidosAtenciones(bool **&pedidosAtendidos, int contador, char ***&pedidosLibros, int **&inventario,
                             char ***&libros) {

    int posicion, cantLibros;

    pedidosAtendidos = new bool *[contador + 1] {};
    for (int i = 0; i < contador; i++) {
        cantLibros = 0;
        for (int a = 0; pedidosLibros[i][a] != nullptr; a++) cantLibros++;
        pedidosAtendidos[i] = new bool [cantLibros + 1] {};
        for (int a = 0; pedidosLibros[i][a] != nullptr; a++) {
            posicion = encontrarPosicion(libros,pedidosLibros[i][a]);
            verificarPedido(pedidosAtendidos[i],inventario,posicion,a);
        }
    }

}

int encontrarPosicion(char ***libros, char *codigoLibro) {

    for (int i = 0; libros[i] != nullptr; i++) {
        for (int a = 0; libros[i][a] != nullptr; a++) {
            if (strcmp(libros[i][a], codigoLibro) == 0) return i;
        }
    }
    return NoEncontrado;

}

void verificarPedido(bool *&pedidosAtendidos, int **&inventario, int posicion, int a) {

    int contador = 0;
    bool seAtiende;

    if (inventario[posicion][0] > 0) {
        seAtiende = true;
        inventario[posicion][0] -= 1;
    }else {
        seAtiende = false;
        inventario[posicion][1] += 1;
    }
    pedidosAtendidos[a] = seAtiende;

}

void reporteDeEntregaDePedidos(const char *nombArch, int **pedidosClientes, char ***pedidosLibros,
                               bool **pedidosAtendidos) {

    ofstream arch;

    crearArchivo(nombArch,arch);

    arch << setw(50) << "REPORTE DE ATENCION DE PEDIDOS" << endl;
    for (int i = 0; pedidosClientes[i] != nullptr; i++) {
        arch << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
        arch << "CLIENTE: " << setw(10) << pedidosClientes[i][0] << endl;
        arch << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
        for (int a = 2; pedidosClientes[i][a] != 0; a++) {
            arch << setw(18) << "Pedido No." << setw(25) << "Codigo del libro"
                 << setw(20) << "observacion" << endl
            ;
            arch << setfill('-') << setw(70) << "-" << setfill(' ') << endl;
            arch << setw(10) << " " << setfill('0') << setw(6) << pedidosClientes[i][a] << setfill(' ');
            arch << setw(14) << " ";
            for (int m = 0; pedidosLibros[pedidosClientes[i][a] - 1][m] != nullptr ; m++) {
                arch << pedidosLibros[pedidosClientes[i][a] - 1][m];
                if (pedidosAtendidos[pedidosClientes[i][a] - 1][m] == true) {
                    arch << setw(25) << "ATENDIDO" << endl;
                }else {
                    arch << setw(28) << "NO ATENDIDO" << endl;
                }
                if (pedidosLibros[pedidosClientes[i][a] - 1][m + 1] != nullptr) arch << setw(30) << " ";
            }
            arch << setfill('-') << setw(70) << "-" << setfill(' ') << endl;
        }
    }

}
