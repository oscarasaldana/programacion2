#include <iostream>

using namespace std;

#include "biblioteca/funciones.h"

int main() {

    void *inventario, *menu;

    cargarInventario("CarpetaDeDatos/inventario.csv",inventario);
    probarCargaInventario("CarpetaDeReportes/reporteInventario.txt",inventario);
    cargarMenu("CarpetaDeDatos/menu.csv",menu);
    probarCargaMenu("CarpetaDeReportes/reporteMenu.txt",menu);
    actualizarMenu("CarpetaDeDatos/insumosBebidas.csv",inventario,menu);
    reporteMenu("CarpetaDeReportes/reporteFinal.txt",menu);

    return 0;
}
