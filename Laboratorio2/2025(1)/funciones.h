
#ifndef SOLUCION_FUNCIONES_H
#define SOLUCION_FUNCIONES_H

void cargarArchivo(const char *, ifstream &);
void crearArchivo(const char *, ofstream &);
void operator += (struct Conductores &, const char *);
char *leerCadenaCaracteres(ifstream &, char );
void incrementarCapacidad(struct Conductores &, int &, int &);
void operator += (struct Infracciones &, const char *);
void aumentarCapacidad(struct Infracciones &, int &, int &);
void cargarFaltasDeLosConductores(const char *, const char *, const char *, struct Faltas &);
int encontrarPosicion(const int *, int , int );
void agregarPlaca(char ***&, int , char *);
void imprimirFaltasDeLosConductores(const char *, struct Faltas &);

#endif //SOLUCION_FUNCIONES_H
