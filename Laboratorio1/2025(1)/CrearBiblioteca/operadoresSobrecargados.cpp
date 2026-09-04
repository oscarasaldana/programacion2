#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

#include "operadoresSobrecargados.h"
#include "estructura.h"

void operator ! (struct CadenaCaracteres &cadena) {

    cadena.cadena = nullptr;
    cadena.capacidad = 0;
    cadena.longitud = 0;

}

void operator <= (struct CadenaCaracteres &cadena, const char *cadenaCaracter) {

    cadena.cadena = new char[strlen(cadenaCaracter) + 1];
    cadena.longitud = strlen(cadenaCaracter) + 1;
    cadena.capacidad = strlen(cadenaCaracter);
    strcpy(cadena.cadena,cadenaCaracter);

}

void operator <= (struct CadenaCaracteres &cadena, int espacioMemoria) {

    cadena.cadena = new char[espacioMemoria];
    cadena.longitud = espacioMemoria;
    cadena.capacidad = espacioMemoria - 1;
    espacioMemoria = 0;

}

void operator <= (struct CadenaCaracteres &cadena1, struct CadenaCaracteres &cadena2) {

    if (!cadena1.cadena) {
        cadena1.cadena = new char[strlen(cadena2.cadena) + 1];
        strcpy(cadena1.cadena,cadena2.cadena);
    }else {
        if (strlen(cadena1.cadena) >= strlen(cadena2.cadena)) {
            strcpy(cadena1.cadena,cadena2.cadena);
        }else {
            cadena1 <= strlen(cadena2.cadena);
            strcpy(cadena1.cadena,cadena2.cadena);
        }
    }
    cadena1.longitud = cadena2.longitud;
    cadena1.capacidad = cadena2.capacidad;

}

void operator += (struct CadenaCaracteres &cadena, const char *cadenaCaracter) {

    int espacioEstructura, espacioCadena, espacioTotal;
    char *ptrCadena;

    ptrCadena = new char[strlen(cadena.cadena) + 1];
    strcpy(ptrCadena,cadena.cadena);
    delete cadena.cadena;
    espacioEstructura = strlen(ptrCadena);
    espacioCadena = strlen(cadenaCaracter);
    espacioTotal = espacioEstructura + espacioCadena;
    cadena <= espacioTotal + 2;
    strcpy(cadena.cadena,ptrCadena);
    strcat(cadena.cadena,"_");
    strcat(cadena.cadena,cadenaCaracter);
    cadena.longitud = espacioTotal + 1;
    cadena.capacidad = espacioTotal;

}

bool operator += (struct CadenaCaracteres &cadena1, struct CadenaCaracteres &cadena2) {

    int espacioCadena1, espacioCadena2, espacioTotal;
    char *ptrCadena;

    if (!cadena1.cadena) return false;
    else {
        ptrCadena = new char[strlen(cadena1.cadena) + 1];
        strcpy(ptrCadena,cadena1.cadena);
        delete cadena1.cadena;
        espacioCadena1 = strlen(cadena1.cadena);
        espacioCadena2 = strlen(cadena2.cadena);
        espacioTotal = espacioCadena1 + espacioCadena2;
        cadena1 <= espacioTotal + 1;
        strcpy(cadena1.cadena,ptrCadena);
        strcat(cadena1.cadena," ");
        strcat(cadena1.cadena,cadena2.cadena);
        cadena1.longitud = espacioTotal + 1;
        cadena1.capacidad = espacioTotal;
    }
    return true;

}

int compare(struct CadenaCaracteres &cadena, const char *cadenaCaracter) {

    int numMemoria;

    numMemoria = strlen(cadena.cadena) + 1;
    for (int i = 0; i < numMemoria; i++) {
        if (cadena.cadena[i] >= 'A' and cadena.cadena[i] <= 'Z') cadena.cadena[i] += 'a' - 'A';
    }
    return strcmp(cadena.cadena,cadenaCaracter);

}

bool operator == (struct CadenaCaracteres &cadena, const char *cadenaCaracter) {

    int resultado;

    resultado = compare(cadena,cadenaCaracter);
    if (resultado == 0) return true;
    else return false;

}

bool operator < (struct CadenaCaracteres &cadena, const char *cadenaCaracter) {

    bool sonIguales =  true;

    sonIguales = cadena == cadenaCaracter;
    if (sonIguales) return true;
    else return false;

}

bool operator > (struct CadenaCaracteres &cadena, const char *cadenaCaracter) {

    int sonIguales = true;

    sonIguales = cadena < cadenaCaracter;
    if (sonIguales) return true;
    else return false;


}

int compare(struct CadenaCaracteres &cadena1, struct CadenaCaracteres &cadena2) {

    int numMemoria1, numMemoria2;

    numMemoria1 = strlen(cadena1.cadena) + 1;
    for (int i = 0; i < numMemoria1; i++) {
        if (cadena1.cadena[i] >= 'A' and cadena1.cadena[i] <= 'Z') cadena1.cadena[i] += 'a' - 'A';
    }
    numMemoria2 = strlen(cadena2.cadena) + 1;
    for (int i = 0; i < numMemoria2; i++) {
        if (cadena2.cadena[i] >= 'A' and cadena2.cadena[i] <= 'Z') cadena2.cadena[i] += 'a' - 'A';
    }
    return strcmp(cadena1.cadena,cadena2.cadena);

}

bool operator == (struct CadenaCaracteres &cadena1, struct CadenaCaracteres &cadena2) {

    int resultado;

    resultado = compare(cadena1,cadena2);
    if (resultado == 0) return true;
    else return false;

}

bool operator < (struct CadenaCaracteres &cadena1, struct CadenaCaracteres &cadena2) {

    bool sonIguales = true;

    sonIguales = cadena1 == cadena2;
    if (sonIguales == true) return true;
    else return false;

}

bool operator > (struct CadenaCaracteres &cadena1, struct CadenaCaracteres &cadena2) {

    bool sonIguales = true;

    sonIguales = cadena1 < cadena2;
    if (sonIguales == true) return true;
    else return false;

}

int operator >> (ifstream &arch, struct CadenaCaracteres &cadena) {

    cadena.cadena = leerCadenaCaracteres(arch,' ');
    if (!cadena.cadena) return 1;
    if (strcmp(cadena.cadena,"-") == 0) return -1;
    else return 0;

}

char *leerCadenaCaracteres(ifstream &arch, char delim) {

    char cadena[50], *ptrCadena, caracter;

    caracter = arch.peek();
    arch.getline(cadena,50,delim);
    if (arch.eof()) return nullptr;
    if ((caracter >= 'a' and caracter <= 'z') or (caracter >= 'A' and caracter <= 'Z')) {
        ptrCadena = new char[strlen(cadena) + 1];
        strcpy(ptrCadena,cadena);
    }else {
        ptrCadena = new char[2];
        strcpy(ptrCadena,"-");
    }

    return ptrCadena;

}

void operator && (struct CadenaCaracteres &cadena1, struct CadenaCaracteres &cadena2) {

    struct CadenaCaracteres cadenaAux {};

    cadenaAux = cadena1;
    cadena1 = cadena2;
    cadena2 = cadenaAux;

}

void operator << (ofstream &arch, struct CadenaCaracteres &cadena) {

    arch << cadena.cadena;

}
