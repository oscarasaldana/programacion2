#include <iostream>

using namespace std;

#include "biblioteca/funciones.h"

int main() {

    char ***categorias {};
    cargarCategorias("CarpetaDeDatos/categorias.csv",categorias);

    char ***streamers {};
    int **fechasPromedios {};
    long long **tiempoRepSeguidores {};
    cargarStreamers("CarpetaDeDatos/streamers.csv",streamers,fechasPromedios,tiempoRepSeguidores);

    char ***comentarios {};
    char ***etiquetas {};
    cargarEtiquetasComentarios("CarpetaDeDatos/comentarios.csv",comentarios,etiquetas);

    imprimirReportes("CarpetaDeReportes/reporte.txt",categorias,streamers,fechasPromedios,tiempoRepSeguidores,
                     comentarios,etiquetas);

    return 0;
}
