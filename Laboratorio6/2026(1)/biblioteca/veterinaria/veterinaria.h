
#ifndef CODIGO_VETERINARIA_H
#define CODIGO_VETERINARIA_H

#include "../mascota/mascota.h"

class Veterinaria {

private:
    class Mascota *listaDeMascotas;
    int numMascotas;

public:
    Veterinaria();
    ~Veterinaria();

    void obtenerNumMascotas(int &) const;
    int posicionEncontrada(char *, int ) const;

    void operator <= (const char *);
    void operator <<= (const char *);
    void operator << (const char *);

};

#endif //CODIGO_VETERINARIA_H
