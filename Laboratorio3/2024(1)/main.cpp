#include <iostream>

using namespace std;

#include "biblioteca/funciones.h"

int main() {

    void *clientes, *reserva;

    cargarClientes(clientes);
    crearReserva(reserva);
    cargarReservas(clientes,reserva);
    reporteFinal(reserva);

    return 0;
}
