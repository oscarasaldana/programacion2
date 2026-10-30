#include <iostream>

using namespace std;

#include "biblioteca/restaurante/restaurante.h"

int main() {

    class Restaurante restaurante;

    restaurante < "CarpetaDeDatos/Clientes.csv";
    restaurante <= "CarpetaDeDatos/PlatosOfrecidos.csv";
    restaurante <<= "CarpetaDeDatos/Pedidos.csv";
    restaurante >> "CarpetaDeReportes/ReportesDeVentaDelDia.txt";

    return 0;
}
