#include <iostream>

using namespace std;

#include "biblioteca/funciones.h"

int main() {

    int **inventario, **pedidosClientes;
    char ***libros, ***pedidosLibros;
    bool **pedidosAtendidos;

    lecturaDeLibros("CarpetaDeDatos/Libros.csv",libros,inventario);
    pruebaDeLecturaDeLibros("CarpetaDeReportes/ReporteDeLibrosInicial.txt",libros,inventario);

    atencionDePedidos("CarpetaDeDatos/Pedidos.txt",libros,inventario,pedidosClientes,
                     pedidosLibros,pedidosAtendidos);

    reporteDeEntregaDePedidos("CarpetaDeReportes/ReporteDeEntregaDePedidos.txt",pedidosClientes,
                              pedidosLibros,pedidosAtendidos);

    return 0;
}
