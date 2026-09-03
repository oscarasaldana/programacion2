#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

#include "operadoresSobrecargados.h"
#include "Estructuras.h"

#define NO_ENCONTRADO (-1)

using namespace std;

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
        cout << "ERRO: No se pudo crear el archivo " << nombArch << endl;
        exit(2);
    }

}

void operator >> (ifstream &arch, struct Cursos &curso) {

    char codDocente[9];

    curso.codigo = leerCadenaCaracteres(arch,',');
    if (curso.codigo) {
        curso.nombre = leerCadenaCaracteres(arch,',');
        arch >> curso.creditos;
        arch.get();
        arch.getline(codDocente,9,',');
        curso.docente = leerCadenaCaracteres(arch,'\n');
        curso.numpresencial = 0;
        curso.numsemipresencial = 0;
        curso.numvirtual = 0;
    }

}

void operator >> (ifstream &arch, struct Alumnos &alumno) {

    arch >> alumno.codigo;
    arch.get();
    alumno.nombre = leerCadenaCaracteres(arch,',');
    arch >> alumno.tipo;

}

char *leerCadenaCaracteres(ifstream &arch, char delim) {

    char cadena[60], *ptrCadena;

    arch.getline(cadena,60,delim);
    if (arch.eof()) return nullptr;
    ptrCadena = new char[strlen(cadena) + 1];
    strcpy(ptrCadena,cadena);

    return ptrCadena;

}

bool operator > (struct Alumnos &alumno, int codigoAlumno) {

    if (alumno.codigo == codigoAlumno) return true;
    else return false;

}

bool operator > (struct Cursos &curso, char *codCurso) {

    char *ptrCodCurso;

    ptrCodCurso = new char[strlen(codCurso) + 1];
    strcpy(ptrCodCurso,codCurso);
    if (strcmp(ptrCodCurso,curso.codigo) == 0) return true;
    return false;

}

void operator += (struct Cursos &curso, struct Alumnos &alumno) {

    if (alumno.tipo == 'P') curso.presencial[curso.numpresencial++] = alumno;
    else if (alumno.tipo == 'S') curso.semipresencial[curso.numsemipresencial++]= alumno;
    else curso.vvirtual[curso.numvirtual++] = alumno;

}

int operator <= (struct Alumnos *arrAlumnos, struct Alumnos &alumno) {

    int i = 0;

    while (true) {
        if (arrAlumnos[i].codigo == 0) break;
        if (arrAlumnos[i].codigo == alumno.codigo) return i;
        i++;
    }
    return NO_ENCONTRADO;

}

int operator <= (struct Cursos *arrCursos, struct Cursos &curso) {

    int i = 0;

    while (true) {
        if (arrCursos[i].codigo == nullptr) break;
        if (strcmp(arrCursos[i].codigo,curso.codigo) == 0) return i;
        i++;
    }
    return NO_ENCONTRADO;

}

void operator ++ (struct Cursos &curso, int) {

    int estudiantesTotales;
    double porcentaje;
    char noticiaClase1[] = "La clase se dictara en aula.";
    char noticiaClase2[] = "La clase se dictara 100% virtual";
    char *ptrNoticiaClase1, *ptrNoticiaClase2;

    estudiantesTotales = curso.numpresencial + curso.numsemipresencial + curso.numvirtual;
    porcentaje = ((double) curso.numpresencial / estudiantesTotales) * 100;
    if (porcentaje >= 50) {
        ptrNoticiaClase1 = new char[strlen(noticiaClase1) + 1];
        strcpy(ptrNoticiaClase1,noticiaClase1);
        curso.tipofinal = ptrNoticiaClase1;
    }else {
        ptrNoticiaClase2 = new char[strlen(noticiaClase2) + 1];
        strcpy(ptrNoticiaClase2,noticiaClase2);
        curso.tipofinal = ptrNoticiaClase2;
    }

}

void operator << (ofstream &arch, struct Cursos &curso) {

    arch << setw(10) << curso.codigo << setw(5) << " " << curso.nombre << endl;
    arch << setw(4) << " " << curso.docente << endl;
    arch << setw(26) << "Alumnos presenciales: " << setw(7) << curso.numpresencial << endl;
    arch << setw(30) << "Alumnos semipresenciales: " << setw(3) << curso.numsemipresencial << endl;
    arch << setw(23) << "Alumnos virtuales: " << setw(10) << curso.numvirtual << endl;
    arch << setw(4) << " " << curso.tipofinal << endl;
    arch << endl;

}

