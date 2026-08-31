#include <iostream>
#include <fstream>
#include <iomanip>

#include "funciones.h"
#include "operadoresSobrecargados.h"
#include "veterinaria.h"

using namespace std;

void cargarMascotas(const char *nombArch, struct Sistema &sistema) {

    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se puedo acceder al archivo " << nombArch << endl;
        exit(1);
    }

    struct Mascota mascota {};

    while (true) {
        arch >> mascota;
        if (arch.eof()) break;
        sistema.arrMascotas[sistema.numMascotas++] = mascota;
    }

}

void cargarVeterinarios(const char *nombArch, struct Sistema &sistema) {

    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se puedo acceder al archivo " << nombArch << endl;
        exit(2);
    }

    struct Veterinario veterinario {};

    while (true) {
        arch >> veterinario;
        if (arch.eof()) break;
        sistema.arrVeterinarios[sistema.numVeterinarios++] = veterinario;
    }

}

void cargarAtenciones(const char *nombArch, struct Sistema &sistema) {

    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se puedo acceder al archivo " << nombArch << endl;
        exit(3);
    }

    int CantCruces = 0;
    bool seCruza = true;

    struct Atencion atencion {};

    while (true) {
        arch >> atencion;
        if (arch.eof()) break;
        seCruza = existeCruce(sistema.arrAtenciones,atencion,sistema.numAtenciones,CantCruces);
        if (!seCruza) sistema.arrAtenciones[sistema.numAtenciones++] = atencion;
        else cout << CantCruces << " ATENCION(ES) SIN PROGRAMAR" << endl;
    }

}

bool existeCruce(struct Atencion *arrAtenciones, struct Atencion &atencion,
                 int numAtenciones, int &cantCruces) {

    bool hayCruce;

    for (int i = 0; i < numAtenciones; i++) {
        hayCruce = arrAtenciones[i] == atencion;
        if (hayCruce == true) {
            cantCruces++;
            return true;
        }
    }
    return false;

}

void listaMascotasAEsterelizar(const char *nombArch, struct Sistema &sistema) {

    ofstream arch(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo crear el archivo " << nombArch << endl;
        exit(4);
    }

    int fecha = 20251010;
    bool noEsApto;

    arch << "--------------------------------------------------------" << endl;
    arch << "********* MASCOTAS QUE DEBEN SER ESTERELIZADAS *********" << endl;
    arch << "--------------------------------------------------------" << endl;

    for (int i = 0; i < sistema.numAtenciones; i++) {
        noEsApto = sistema.arrMascotas[i] <= fecha;
        if (!noEsApto) arch << sistema.arrMascotas[i];
    }

}

void imprimirMascotasConAtenciones(const char *nombArch, struct Sistema &sistema) {

    ofstream arch(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo crear el archivo " << nombArch << endl;
        exit(5);
    }

    int cont = 0;

    arch << "--------------------------------------------------------" << endl;
    arch << "********* LISTADO DE MASCOTAS Y SUS ATENCIONES *********" << endl;
    arch << "--------------------------------------------------------" << endl;

    for (int i = 0; i < sistema.numMascotas; i++) {
        cont = 0;
        arch << "MASCOTA";
        arch << sistema.arrMascotas[i];
        for (int j = 0; j < sistema.numAtenciones; j++) {
            if (sistema.arrMascotas[i].idMascota == sistema.arrAtenciones[j].idMascota) {
                cont++;
                arch << sistema.arrAtenciones[j];
            }
        }
        if (cont == 0) arch << "No tiene atenciones registradas" << endl;
        arch << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
    }
    arch << "TOTAL: " << sistema.numMascotas << " mascotas, " << sistema.numAtenciones << " atenciones";

}
