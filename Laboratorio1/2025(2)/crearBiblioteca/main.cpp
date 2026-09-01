#include <fstream>

#include "biblioteca/operadoresSobrecargados.h"

using namespace std;

int main() {

    ifstream archMascotas, archVeterinarios, archAtenciones;
    ofstream archReporte1, archReporte2;

    cargarArchivos(archMascotas,archVeterinarios,archAtenciones);
    crearArchivos(archReporte1,archReporte2);

    return 0;
}
