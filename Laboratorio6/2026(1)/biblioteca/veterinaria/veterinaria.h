
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

    int obtenerNumMascotas() const;
    int posicionEncontrada(const char *, int ) const;

    void operator <= (const char *);
    void operator <<= (const char *);
    void operator << (const char *) const;

};

#endif //CODIGO_VETERINARIA_H
