#include <iostream>

using namespace std;

#include "biblioteca/funciones.h"

int main() {

    void *streamers, *comentarios;

    cargarStreamers(streamers);
    cargarComentarios(comentarios);
    actualizarComentarios(streamers,comentarios);
    imprimirStreamers(streamers);

    return 0;
}
