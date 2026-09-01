#include <fstream>

#include "biblioteca/operadoresSobrecargados.h"
#include "biblioteca/Estructuras.h"

using namespace std;

int main() {

    ifstream archAlumnos, archCursos, archMatriculas;
    ofstream archReporte;

    cargarArchivo("CarpetaDeDatos/Alumnos.csv",archAlumnos);
    cargarArchivo("CarpetaDeDatos/Cursos.csv",archCursos);
    cargarArchivo("CarpetaDeDatos/Matricula.csv",archMatriculas);
    crearArchivo("CarpetaDeReportes/Reporte.txt",archReporte);


    return 0;
}
