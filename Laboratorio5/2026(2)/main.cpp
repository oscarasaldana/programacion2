#include <iostream>

using namespace std;

#include "biblioteca/procesa/procesa.h"

int main() {

    Procesa procesa;

    procesa.cargarOperaciones("CarpetaDeDatos/Movimientos.csv");
    procesa.descargaOperaciones(2,2026);
    procesa.imprimeOperaciones("CarpetaDeReportes/Reporte.txt");

    return 0;
}
