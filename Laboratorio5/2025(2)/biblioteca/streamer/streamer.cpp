#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "../streamer/streamer.h"

Streamer::Streamer() {

    cuenta = nullptr;
    tiempoEnStream = 0;
    promEspectadores = 0;
    numSeguidores = 0;
    categoria = nullptr;

}

Streamer::Streamer(char *canal, long long duracionStreams, double promedioEspectadores, long long cantSeguidores,
                   char *categoriaCanal) {

    cuenta = nullptr;
    categoria = nullptr;

    cargarCuenta(canal);
    this->tiempoEnStream = duracionStreams;
    this->promEspectadores = promedioEspectadores;
    this->numSeguidores = cantSeguidores;
    cargarCategoria(categoriaCanal);

}

Streamer::~Streamer() {

    delete [] cuenta;
    delete [] categoria;

}

void Streamer::obtenerCuenta(char *cadena) const {

    if (!cuenta) cadena[0] = 0;
    else strcpy (cadena,this->cuenta);

}

void Streamer::cargarCuenta(char *cadena) {

    delete [] cuenta;
    cuenta = new char [strlen(cadena) + 1];
    strcpy (this->cuenta,cadena);

}

long long Streamer::obtenerTiempoStream() const {

    return tiempoEnStream;

}

void Streamer::cargarTiempoStream(long long dato) {

    this->tiempoEnStream = dato;

}

double Streamer::obtenerPromEspectadores() const {

    return promEspectadores;

}

void Streamer::cargarPromEspectadores(double dato) {

    this->promEspectadores = dato;

}

long long Streamer::obtenerNumSeguidores() const {

    return numSeguidores;

}

void Streamer::cargarNumSeguidores(long long dato) {

    this->numSeguidores = dato;

}

void Streamer::obtenerCategoria(char *cadena) const {

    if (!categoria) cadena[0] = 0;
    else strcpy (cadena,this->categoria);

}

void Streamer::cargarCategoria(char *cadena) {

    delete [] categoria;
    categoria = new char [strlen(cadena) + 1];
    strcpy (this->categoria,cadena);

}

void Streamer::leerStreamer(ifstream &arch) {

    double promedioEspec;
    long long duracion, numeroSeg;
    char caracter;
    char canal[50], categoriaCanal[50];

    arch.getline(canal,50,',');
    if (arch.eof()) return;
    arch >> duracion >> caracter >> promedioEspec >> caracter >> numeroSeg >> caracter;
    arch.getline(categoriaCanal,50,'\n');

    cargarCuenta(canal);
    cargarTiempoStream(duracion);
    cargarPromEspectadores(promedioEspec);
    cargarNumSeguidores(numeroSeg);
    cargarCategoria(categoriaCanal);

}

void Streamer::mostrarStreamer(ostream &salida) {

    salida << left << setw(15) << cuenta << right << setw(13) << tiempoEnStream << setw(20)
           << promEspectadores << setw(28) << numSeguidores << setw(20) << categoria << endl
    ;

}

void Streamer::copiar(class Streamer &streamerCopia) {

    cargarCuenta(streamerCopia.cuenta);
    cargarTiempoStream(streamerCopia.tiempoEnStream);
    cargarPromEspectadores(streamerCopia.promEspectadores);
    cargarNumSeguidores(streamerCopia.numSeguidores);
    cargarCategoria(streamerCopia.categoria);

}
