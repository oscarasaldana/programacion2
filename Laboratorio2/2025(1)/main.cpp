#include <iostream>

using namespace std;

#include "biblioteca/funciones.h"
#include "estructuras/faltas.h"

int main() {

    struct Faltas faltas {};

    cargarFaltasConductores("CarpetaDeDatos/Conductores.csv","CarpetaDeDatos/Infracciones.csv",
                            "CarpetaDeDatos/Faltas.csv",faltas);
    imprimirFaltasConductores("CarpetaDeReportes/ReporteDeConductores.txt",faltas);

    return 0;
}
