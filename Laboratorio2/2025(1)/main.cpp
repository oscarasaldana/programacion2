#include <iostream>

using namespace std;

#include "biblioteca/funciones.h"
#include "biblioteca/conductores.h"
#include "biblioteca/infracciones.h"
#include "biblioteca/faltas.h"

int main() {

    struct Conductores conductor {};
    struct Infracciones infraccion {};
    struct Faltas falta {};

    cargarFaltasDeLosConductores("CarpetaDeDatos/Faltas.csv","CarpetaDeDatos/Conductores.csv",
                                 "CarpetaDeDatos/Infracciones.csv",falta);
    imprimirFaltasDeLosConductores("CarpetaDeReportes/Reporte.txt",falta);

    return 0;
}
