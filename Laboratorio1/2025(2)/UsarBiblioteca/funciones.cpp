#include <iostream>
#include <fstream>
#include <cstring>

#include "operadoresSobrecargados.h"
#include "Estructuras.h"
#include "funciones.h"

using namespace std;


void cargarAlumnos(const char *nombArch, struct Alumnos *arrAlumnos) {

    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo " << nombArch << endl;
        exit(1);
    }

    int i = 0;

    struct Alumnos alumno {};

    while (true) {
        arch >> alumno;
        if (arch.eof()) break;
        arrAlumnos[i++] = alumno;
    }
    arrAlumnos[i].codigo = 0;

}

void cargarCursos(const char *nombArch, struct Cursos *arrCursos) {

    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo " << nombArch << endl;
        exit(2);
    }

    int i = 0;

    struct Cursos curso {};

    while(true) {
        arch >> curso;
        if (arch.eof()) break;
        arrCursos[i++] = curso;
    }
    arrCursos[i].codigo = nullptr;

}

void cargarMatriculas(const char *nombArch, struct Cursos *arrCursos, struct Alumnos *arrAlumnos) {

    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo acceder al archivo " << nombArch << endl;
        exit(3);
    }

    char *ptrCodCurso;
    int codAlumno, posCurso, posAlumno;
    bool encontrado = true;

    struct Cursos curso {};
    struct Alumnos alumno {};

    while (true) {
        ptrCodCurso = leerCadena(arch,',');
        if (arch.eof()) break;
        curso.codigo = ptrCodCurso;
        encontrado = encontrarCurso(arrCursos,ptrCodCurso);
        if (encontrado) {
            posCurso = arrCursos <= curso;
            arch >> codAlumno;
            alumno.codigo = codAlumno;
            arch.get();
            posAlumno = arrAlumnos <= alumno;
            arrCursos[posCurso] += arrAlumnos[posAlumno];
        }else while (arch.get() != '\n');
    }

}

char *leerCadena(ifstream &arch, char delim) {

    char cadena[7], *ptrCadena;

    arch.getline(cadena,7,delim);
    if (arch.eof()) return nullptr;
    ptrCadena = new char[strlen(cadena) + 1];
    strcpy(ptrCadena,cadena);

    return ptrCadena;

}

bool encontrarCurso(struct Cursos *arrCursos, char *ptrCodCurso) {

    int i = 0;
    bool encontrado = true;

    while (true) {
        encontrado = arrCursos[i] > ptrCodCurso;
        if (arrCursos[i].codigo == nullptr) break;
        if (encontrado) return encontrado;
        i++;
    }
    return encontrado;

}

void generarReporte(const char *nombArch, struct Cursos *arrCursos) {

    ofstream arch(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo crear el archivo " << nombArch << endl;
        exit(4);
    }

    int i = 0;

    while (true) {
        arrCursos[i]++;
        arch << arrCursos[i];
        if (arrCursos[i].codigo == nullptr) break;
        i++;
    }

}

