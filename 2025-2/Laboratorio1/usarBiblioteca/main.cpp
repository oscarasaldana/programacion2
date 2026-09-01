#include <iostream>

#include "biblioteca/Estructuras.h"
#include "biblioteca/funciones.h"

using namespace std;

int main() {

    struct Alumnos arrAlumnos[100] {};
    struct Cursos arrCursos[50] {};

    cargarAlumnos("CarpetaDeDatos/Alumnos.csv",arrAlumnos);
    cargarCursos("CarpetaDeDatos/Cursos.csv",arrCursos);
    cargarMatriculas("CarpetaDeDatos/Matricula.csv",arrCursos,arrAlumnos);
    generarReporte("CarpetaDeReportes/ReporteCursos.txt",arrCursos);

    return 0;
}
