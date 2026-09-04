#include <iostream>
#include <fstream>

using namespace std;

#include "biblioteca/operadoresSobrecargados.h"
#include "biblioteca/estructura.h"
#include "biblioteca/funciones.h"

#define C 150

int main() {
    ifstream archInfraccion;
    ofstream archReporte;

    int arrDni[C], numConductores;
    struct CadenaCaracteres arrConductores[C] {};
    struct CadenaCaracteres arrPlacas[C] {};

    cargarInfracciones(archInfraccion,arrDni,arrConductores,arrPlacas,numConductores);
    qsort(arrDni,arrConductores,arrPlacas,0,numConductores-1);
    reporte(archReporte,arrDni,arrConductores,arrPlacas,numConductores);

    return 0;
}
