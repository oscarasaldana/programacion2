#include <iostream>

#include "biblioteca/operadoresSobrecargados.h"
#include "biblioteca/veterinaria.h"
#include "biblioteca/funciones.h"

using namespace std;

int main () {

    struct Sistema sistema {};

    cargarMascotas("CarpetaDeDatos/Mascotas.csv",sistema);
    cargarVeterinarios("CarpetaDeDatos/Veterinarios.csv",sistema);
    cargarAtenciones("CarpetaDeDatos/Atenciones.csv",sistema);
    listaMascotasAEsterelizar("CarpetaDeReportes/ListaMascotasAEsterelizar.txt",sistema);
    imprimirMascotasConAtenciones("CarpetaDeReportes/MascotasConAtenciones.txt",sistema);

    return 0;
}
