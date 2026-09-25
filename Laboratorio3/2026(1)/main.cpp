#include <iostream>

using namespace std;

#include "biblioteca/funciones.h"

int main() {

    void *pacientes;

    cargarPacientes("CarpetaDeDatos/pacientes.csv",pacientes);
    cargarVisitas("CarpetaDeDatos/visitas.csv",pacientes);
    generarReportes("CarpetaDeReportes/reportes.txt",pacientes);

    return 0;
}
