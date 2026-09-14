
#ifndef CODIGO_FUNCIONES_H
#define CODIGO_FUNCIONES_H

void cargarArchivo(const char *, ifstream &);
void crearArchivo(const char *, ofstream &);
void operator += (struct Conductores &, const char *);
char *leerCadenaCaracteres(ifstream &, char );
void operator += (struct Infracciones &, const char *);
void cargarFaltasConductores(const char *, const char *, const char *, struct Faltas &);
int encontrarPosicionDni(const int *, int , int );
void cargarPlacas(struct Faltas &, char *, int );
bool placaRepetida(char **, char *);
void incrementarCapacidad(char **&, int &);
void imprimirFaltasConductores(const char *, struct Faltas &);

#endif //CODIGO_FUNCIONES_H
