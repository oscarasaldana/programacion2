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

void cargarInventario(const char *nombArch, void *&inventario) {

    ifstream arch;

    int numInsumos = 0, capacidad = 1;
    double cantDisponible, cantRequerida = 0;
    char caracter;

    char *codigo, *nombre, *unidad;
    void ***ptrInventario = nullptr;

    cargarArchivo(nombArch,arch);
    while (true) {
        codigo = leerCadenaCaracteres(arch,',');
        if (arch.eof()) break;
        nombre = leerCadenaCaracteres(arch,',');
        arch >> cantDisponible >> caracter;
        unidad = leerCadenaCaracteres(arch,'\n');
        if (numInsumos == capacidad - 1) incrementarCapacidadInventario(ptrInventario,numInsumos,capacidad);
        cargarDatosInventario(ptrInventario[numInsumos],codigo,nombre,cantDisponible,cantRequerida,unidad);
        numInsumos++;

    }
    inventario = ptrInventario;

}

char *leerCadenaCaracteres(ifstream &arch, char delimitador) {

    char cadena[150], *ptrCadena;

    arch.getline(cadena,150,delimitador);
    if (arch.eof()) return nullptr;
    ptrCadena = new char [strlen(cadena) + 1];
    strcpy(ptrCadena,cadena);

    return ptrCadena;

}

void incrementarCapacidadInventario(void ***&ptrInventario, int numInsumos, int &capacidad) {

    void ***insumos;

    capacidad += Incremento;
    if (!ptrInventario) {
        ptrInventario = new void **[capacidad] {};
    }else {
        insumos = new void **[capacidad] {};
        for (int i = 0; i < numInsumos; i++) insumos[i] = ptrInventario[i];
        delete [] ptrInventario;
        ptrInventario = insumos;
    }

}

void cargarDatosInventario(void **&insumo, char *codigo, char *nombre, double cantDisponible,
                           double cantRequerida, char *unidad) {

    double *ptrCantDisponible, *ptrCantRequerida;

    ptrCantDisponible = new double;
    ptrCantRequerida = new double;
    *ptrCantDisponible = cantDisponible;
    *ptrCantRequerida = cantRequerida;

    insumo = new void *[5] {};
    insumo[0] = codigo;
    insumo[1] = nombre;
    insumo[2] = ptrCantDisponible;
    insumo[3] = ptrCantRequerida;
    insumo[4] = unidad;

}

void probarCargaInventario(const char *nombArch, void *&inventario) {

    ofstream arch;

    void ***ptrInventario, **insumo;

    crearArchivo(nombArch,arch);
    ptrInventario = (void ***)inventario;
    for (int i = 0; ptrInventario[i]; i++) {
        insumo = (void **)ptrInventario[i];
        mostrarInventario(arch,insumo);
    }

}

void mostrarInventario(ofstream &arch, void **&insumo) {

    double *cantDisponible, *cantRequerida;
    char *codigo, *nombre, *unidad;

    codigo = (char *)insumo[0];
    nombre = (char *)insumo[1];
    cantDisponible = (double *)insumo[2];
    cantRequerida = (double *)insumo[3];
    unidad = (char *)insumo[4];

    arch << codigo << " " << nombre << " " << *cantDisponible
         << " " << *cantRequerida << " " << unidad << endl;

}

void cargarMenu(const char *nombArch, void *&menu) {

    ifstream arch;

    int numBebidas = 0, capacidad = 1;
    int cantVentasEstimadas;
    double precio;
    char tipoBebida, caracter;
    bool disponibilidad = true;

    char *codigo, *nombre, *descripcion;
    void ***ptrMenu = nullptr;

    cargarArchivo(nombArch,arch);
    while (true) {
        codigo = leerCadenaCaracteres(arch,',');
        if (arch.eof()) break;
        nombre = leerCadenaCaracteres(arch,',');
        descripcion = leerCadenaCaracteres(arch,',');
        arch >> tipoBebida >> caracter >> precio >> caracter >> cantVentasEstimadas;
        arch.get();
        if (numBebidas == capacidad - 1) incrementarCapacidadMenu(ptrMenu,numBebidas,capacidad);
        cargarDatosMenu(ptrMenu[numBebidas],codigo,nombre,descripcion,tipoBebida,disponibilidad,
                        precio,cantVentasEstimadas)
        ;
        numBebidas++;
    }
    menu = ptrMenu;

}

void incrementarCapacidadMenu(void ***&ptrMenu, int numBebidas, int &capacidad) {

    void ***bebidas;

    capacidad += Incremento;
    if (!ptrMenu) {
        ptrMenu = new void **[capacidad] {};
    }else {
        bebidas = new void **[capacidad] {};
        for (int i = 0; i < numBebidas; i++) bebidas[i] = ptrMenu[i];
        delete [] ptrMenu;
        ptrMenu = bebidas;
    }

}

void cargarDatosMenu(void **&bebida, char *codigo, char *nombre, char *descripcion, char tipoBebida,
                     bool disponibilidad, double precio, int cantVentasEstimadas) {

    int *ptrCantVentasEstimadas;
    double *ptrPrecio;
    char *ptrTipoBebida;
    bool *ptrDisponibilidad;

    ptrCantVentasEstimadas = new int;
    ptrPrecio = new double;
    ptrTipoBebida = new char;
    ptrDisponibilidad = new bool;
    *ptrCantVentasEstimadas = cantVentasEstimadas;
    *ptrPrecio = precio;
    *ptrTipoBebida = tipoBebida;
    *ptrDisponibilidad = disponibilidad;

    bebida = new void *[8] {};
    bebida[0] = codigo;
    bebida[1] = nombre;
    bebida[2] = descripcion;
    bebida[3] = ptrTipoBebida;
    bebida[4] = ptrDisponibilidad;
    bebida[5] = ptrPrecio;
    bebida[6] = ptrCantVentasEstimadas;
    bebida[7] = nullptr;

}

void probarCargaMenu(const char *nombArch, void *&menu) {

    ofstream arch;

    void ***ptrMenu, **bebida;

    crearArchivo(nombArch,arch);
    ptrMenu = (void ***)menu;
    for (int i = 0; ptrMenu[i]; i++) {
        bebida = ptrMenu[i];
        mostrarMenu(arch,bebida);
    }

}

void mostrarMenu(ofstream &arch, void **&bebida) {

    int *cantVentasEstimadas;
    double *precio;
    char *codigo, *nombre, *descripcion, *tipoBebida;
    bool *disponibilidad;

    codigo = (char *)bebida[0];
    nombre = (char *)bebida[1];
    descripcion = (char *)bebida[2];
    tipoBebida = (char *)bebida[3];
    disponibilidad = (bool *)bebida[4];
    precio = (double *)bebida[5];
    cantVentasEstimadas = (int *)bebida[6];

    arch << codigo << " " << nombre << " " << descripcion << " " << *tipoBebida << " "
         << *disponibilidad << " " << *precio << " " << *cantVentasEstimadas << endl;

}

void actualizarMenu(const char *nombArch, void *&inventario, void *&menu) {

    ifstream arch;

    int cantidadRequerida, posicion;
    char unidad, caracter;

    int numInsumosBebida[25] {}, capacidad[25] {};

    char *codigoBebida, *codigoInsumo;
    void **insumosBebida[25] {};
    void ***ptrMenu, **bebida;

    cargarArchivo(nombArch,arch);
    while (true) {
        codigoBebida = leerCadenaCaracteres(arch,',');
        if (arch.eof()) break;
        codigoInsumo = leerCadenaCaracteres(arch,',');
        arch >> cantidadRequerida >> caracter >> unidad;
        arch.get();
        posicion = encontrarPosicionBebida((void ***)menu,codigoBebida);
        if (posicion != NoEncontrado) {
            cargarDatosInsumosBebida(insumosBebida[posicion],numInsumosBebida[posicion],capacidad[posicion],
                                     inventario,menu,codigoInsumo,cantidadRequerida,unidad,posicion)
            ;
            ptrMenu = (void ***)menu;
            bebida = (void **)ptrMenu[posicion];
            bebida[7] = insumosBebida[posicion];
        }
    }

}

int encontrarPosicionBebida(void ***ptrMenu, char *codigoBebida) {

    void **bebida;

    for (int i = 0; ptrMenu[i]; i++) {
        bebida = (void **)ptrMenu[i];
        if (strcmp((char *)bebida[0],codigoBebida) == 0) return i;
    }
    return NoEncontrado;

}

void cargarDatosInsumosBebida(void **&insumosBebida, int &numInsumosBebida, int &capacidad, void *&inventario,
                              void *&menu,char *codigoInsumo, int cantidadRequerida, char unidad, int posicion) {

    int posicionInsumo;

    int *ptrCantidadRequerida;
    char *ptrUnidad;
    void **datosInsumo, **ptrInsumosBebida;

    if (!insumosBebida or numInsumosBebida == capacidad - 1) capacidad += Incremento;

    ptrCantidadRequerida = new int;
    ptrUnidad = new char;
    *ptrCantidadRequerida = cantidadRequerida;
    *ptrUnidad = unidad;

    datosInsumo = new void *[3] {};
    datosInsumo[0] = informacionInsumo((void ***)inventario,codigoInsumo,posicionInsumo);
    datosInsumo[1] = ptrCantidadRequerida;
    datosInsumo[2] = ptrUnidad;

    if (!insumosBebida) {
        insumosBebida = new void *[capacidad] {};
        insumosBebida[numInsumosBebida] = datosInsumo;
    }else {
        ptrInsumosBebida = new void *[capacidad] {};
        for (int i = 0; i < numInsumosBebida; i++) ptrInsumosBebida[i] = insumosBebida[i];
        ptrInsumosBebida[numInsumosBebida] = datosInsumo;
        delete [] insumosBebida;
        insumosBebida = ptrInsumosBebida;
    }
    numInsumosBebida++;
    actualizarDatosInsumosYBebidas(menu,inventario,cantidadRequerida,posicionInsumo,posicion);

}

void **informacionInsumo(void ***inventario, char *codigoInsumo, int &posicionInsumo) {

    void **insumo;

    for (int i = 0; inventario[i]; i++) {
        insumo = (void **)inventario[i];
        if (strcmp((char *)insumo[0],codigoInsumo) == 0) {
            posicionInsumo = i;
            return insumo;
        }
    }
    return nullptr;

}

void actualizarDatosInsumosYBebidas(void *&menu, void *&inventario, int cantidadRequerida, int posicionInsumo,
                                    int posicion) {

    int *cantVentasEstimadas;
    double *cantidadAUsar, *cantDisponible, *cantRequerida;
    bool *disponible;

    void ***ptrMenu, ***ptrInventario, **bebida, **insumo;

    cantidadAUsar = new double;

    ptrMenu = (void ***)menu;
    bebida = (void **)ptrMenu[posicion];

    ptrInventario = (void ***)inventario;
    insumo = (void **)ptrInventario[posicionInsumo];

    cantVentasEstimadas = (int *)bebida[6];
    disponible = (bool *)bebida[4];
    cantDisponible = (double *)insumo[2];
    cantRequerida = (double *)insumo[3];

    *cantidadAUsar = ((double)cantidadRequerida / 1000.0) *  (*cantVentasEstimadas);
    *cantRequerida += *cantidadAUsar;

    if (*cantRequerida > *cantDisponible) {
        *disponible = false;
    }

}

void reporteMenu(const char *nombArch, void *&menu) {

    ofstream arch;

    void ***ptrMenu, **bebida;

    crearArchivo(nombArch,arch);

    arch << setfill('=') << setw(47) << "=" << "Menu del dia" << setw(46) << "=" << setfill(' ') << endl;

    ptrMenu = (void ***)menu;
    for (int i = 0; ptrMenu[i]; i++) {
        bebida = (void **)ptrMenu[i];
        mostrarBebidas(arch,bebida);
    }

}

void mostrarBebidas(ofstream &arch, void **&bebida) {


    double *precio;
    char *nombre, *descripcion, *tipoBebida;
    bool *disponibilidad;

    nombre = (char *)bebida[1];
    descripcion = (char *)bebida[2];
    tipoBebida = (char *)bebida[3];
    disponibilidad = (bool *)bebida[4];
    precio = (double *)bebida[5];

    mostrarTipoBebida(arch,tipoBebida);

    arch << nombre << endl;
    arch << descripcion << endl;
    arch << "Precio: " << *precio << " s/" << endl;
    if (*disponibilidad) arch << "Disponible: Si" << endl;
    else arch << "Disponible: No" << endl;
    arch << setfill('-') << setw(105) << "-" << setfill(' ') << endl;

}

void mostrarTipoBebida(ofstream &arch, char *tipoBebida) {

    if (*tipoBebida == 'C') arch << "Cafe: ";
    if (*tipoBebida == 'T') arch << "Te: ";
    if (*tipoBebida == 'I') arch << "Infusion: ";
    if (*tipoBebida == 'H') arch << "Chocolate: ";

}
