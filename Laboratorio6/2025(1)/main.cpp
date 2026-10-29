#include <iostream>

using namespace std;

#include "biblioteca/ministerio/ministerio.h"

int main() {

    Ministerio ministerio;

    ministerio < "CarpetaDeDatos/TablaDeInfracciones.csv";
    ministerio <= "CarpetaDeDatos/EmpresasRegistradas.csv";
    ministerio <<= "CarpetaDeDatos/InfraccionesCometidas.csv";
    ministerio >> "CarpetaDeReportes/reporteParaElMinisterio.txt";

    return 0;
}
