
#ifndef USARBIBLIOTECA_PARTE2_FUNCIONES_H
#define USARBIBLIOTECA_PARTE2_FUNCIONES_H

void cargarMascotas(const char *, struct Sistema &);
void cargarVeterinarios(const char *, struct Sistema &);
void cargarAtenciones(const char *, struct Sistema &);
bool existeCruce(struct Atencion *, struct Atencion &, int , int &);
void listaMascotasAEsterelizar(const char *, struct Sistema &);
void imprimirMascotasConAtenciones(const char *, struct Sistema &);

#endif //USARBIBLIOTECA_PARTE2_FUNCIONES_H
