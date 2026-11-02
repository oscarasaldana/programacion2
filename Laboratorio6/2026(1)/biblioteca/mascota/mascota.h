
#ifndef CODIGO_MASCOTA_H
#define CODIGO_MASCOTA_H

#include "../vacuna/vacuna.h"

class Mascota {

private:
    int dni;
    char *nombre;
    char *especie;
    int edad;
    double peso;
    char *colegiatura;

    class Vacuna listaDeVacunas[20];
    int numVacunas;

public:
    Mascota();
    ~Mascota();

    void cargarDni(int );
    int obtenerDni() const;
    void cargarNombre(char *);
    void obtenerNombre(char *) const;
    void cargarEspecie(char *);
    void obtenerEspecie(char *) const;
    void cargarEdad(int );
    int obtenerEdad() const;
    void cargarPeso(double );
    double obtenerPeso() const;
    void cargarColegiatura(char *);
    void obtenerColegiatura(char *) const;

    void imprimirVacunas(ofstream &) const;

    void operator += (const class Vacuna &);
    bool operator ~ () const;

};

void operator >> (ifstream &, class Mascota &);
void operator << (ofstream &, const class Mascota &);

#endif //CODIGO_MASCOTA_H
