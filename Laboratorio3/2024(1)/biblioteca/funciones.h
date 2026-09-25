
#ifndef CODIGO_FUNCIONES_H
#define CODIGO_FUNCIONES_H

void cargarArchivo(const char *, ifstream &);
void crearArchivo(const char *, ofstream &);
void cargarClientes(void *&);
char *leerCadenaCaracteres(ifstream &, char );
void incrementarCapacidad(void ***&, int , int &);
void cargarDatosClientes(void **&, int , char *);
void crearReserva(void *&);
void **cargarDatosLibros(char *, char *, char *, int );
void cargarReservas(void *, void *&);
int encontrarPosicionLibro(void ***, char *);
void actualizarDatosReserva(void ***&, int &, int &, void ***, int );
int encontrarPosicionCliente(void ***, int );
void reporteFinal(void *);
void mostrarReservas(ofstream &, void **);
void mostrarDatosCliente(ofstream &, void **);

#endif //CODIGO_FUNCIONES_H
