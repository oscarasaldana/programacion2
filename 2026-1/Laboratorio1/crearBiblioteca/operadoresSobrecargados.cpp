#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

#include "operadoresSobrecargados.h"
#include "veterinaria.h"

using namespace std;

void cargarArchivos(ifstream &archMascotas, ifstream &archVeterinarios, ifstream &archAtenciones) {

    archMascotas.open("CarpetaDeDatos/Mascotas.csv",ios::in);
    if (not archMascotas.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo Mascotas.csv" << endl;
        exit(1);
    }

    archVeterinarios.open("CarpetaDeDatos/Veterinarios.csv",ios::in);
    if (not archVeterinarios.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo Veterinarios.csv" << endl;
        exit(2);
    }

    archAtenciones.open("CarpetaDeDatos/Atenciones.csv",ios::in);
    if (not archAtenciones.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo Atenciones.csv" << endl;
        exit(3);
    }

}

void crearArchivos(ofstream &archReporte1, ofstream &archReporte2) {

    archReporte1.open("CarpetaDeReportes/ReporteDeMascotas.txt",ios::out);
    if (not archReporte1.is_open()) {
        cout << "ERROR: No se pudo crear el archivo ReporteDeMascotas.txt" << endl;
        exit(4);
    }

    archReporte2.open("CarpetaDeReportes/ReporteDeAtenciones.txt",ios::out);
    if (not archReporte2.is_open()) {
        cout << "ERROR: No se pudo crear el archivo ReporteDeAtenciones.txt" << endl;
        exit(5);
    }

}

istream & operator >> (ifstream &archMascotas, struct Mascota &mascota) {

    int dia, mes, año, fechaNacimiento;
    char caracter;

    archMascotas >> mascota.idMascota;
    archMascotas.get();
    mascota.nombre = leerCadenaCaracteres(archMascotas,',');
    mascota.raza = leerCadenaCaracteres(archMascotas,',');
    mascota.color = leerCadenaCaracteres(archMascotas,',');
    mascota.tipo = leerCadenaCaracteres(archMascotas,',');
    archMascotas >> dia >> caracter >> mes >> caracter >> año;
    fechaNacimiento = año * 10000 + mes * 100 + dia;
    mascota.fechaNacimiento = fechaNacimiento;

    return archMascotas;

}

istream & operator >> (ifstream &archVeterinarios, struct Veterinario &veterinario) {

    archVeterinarios >> veterinario.idVeterinario;
    archVeterinarios.get();
    veterinario.nombre = leerCadenaCaracteres(archVeterinarios,',');
    veterinario.especialidad = leerCadenaCaracteres(archVeterinarios,'\n');

    return archVeterinarios;

}

istream & operator >> (ifstream &archAtenciones, struct Atencion &atencion) {

    static int idAtenciones = 1001;
    int dia, mes, año, fechaAtencion;
    char caracter;

    atencion.idAtencion = idAtenciones;
    archAtenciones >> atencion.idMascota;
    archAtenciones.get();
    archAtenciones >> atencion.idVeterinario;
    archAtenciones.get();
    archAtenciones >> dia >> caracter >> mes >> caracter >> año >> caracter;
    fechaAtencion = año * 10000 + mes * 100 + dia;
    atencion.fecha = fechaAtencion;
    atencion.tipoAtencion = leerCadenaCaracteres(archAtenciones,',');
    archAtenciones >> atencion.hora >> caracter >> atencion.minutos >> caracter;
    atencion.estado = leerCadenaCaracteres(archAtenciones,'\n');
    idAtenciones++;

    return archAtenciones;

}

char *leerCadenaCaracteres(ifstream &arch, char delim) {
    char cadena[30], *ptrCadena;

    arch.getline(cadena,60,delim);
    if (arch.eof()) return nullptr;
    ptrCadena = new char[strlen(cadena) + 1];
    strcpy(ptrCadena,cadena);

    return ptrCadena;

}

bool operator == (struct Atencion &atencionA, struct Atencion &atencionB) {

    if ((atencionA.idVeterinario == atencionB.idVeterinario) and
        (atencionA.fecha == atencionB.fecha) and
        (atencionA.hora == atencionB.hora) and
        (atencionA.minutos == atencionB.minutos)) return true;
    else return false;

}

bool operator <= (struct Mascota &mascota, int fechaAtencion) {

    int diaN, mesN, añoN, diaA, mesA, añoA;
    double fechaN, fechaA;

    fechaN = descomponerFecha(mascota.fechaNacimiento,diaN,mesN,añoN);
    fechaA = descomponerFecha(fechaAtencion,diaA,mesA,añoA);
    if ((fechaA - fechaN) <= 6) return true;
    else return false;

}

double descomponerFecha(int fecha, int dia, int mes, int año) {

    double fechaMes;

    dia = fecha % 100;
    mes = (fecha / 100) % 100;
    año = fecha / 10000;
    fechaMes = año * 12 + mes + (double) dia / 12;

    return fechaMes;

}

ostream & operator << (ofstream &archReporte1, struct Mascota &mascota) {

    archReporte1 << setw(10) << "ID: " << mascota.idMascota << endl;
    archReporte1 << setw(16) <<"Nombre: " << mascota.nombre << endl;
    archReporte1 << setw(14) << "Raza: " << mascota.raza << endl;
    archReporte1 << setw(15) << "Color: " << mascota.color << endl;
    archReporte1 << setw(14) << "Tipo: " << mascota. tipo << endl << endl;

    return archReporte1;

}

ofstream & operator << (ofstream &archReporte2, struct Atencion &atencion) {

    archReporte2 << "Fecha: " << atencion.fecha << ", ID: " << atencion.idAtencion
                 << ", Veterinario: " << atencion.idVeterinario << ", Tipo: " << atencion.tipoAtencion
                 << ", Estado: " << atencion.estado << endl
    ;

    return archReporte2;

}
