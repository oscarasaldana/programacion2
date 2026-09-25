
#ifndef CODIGO_FUNCIONES_H
#define CODIGO_FUNCIONES_H

void cargarArchivo(const char *, ifstream &);
void crearArchivo(const char *, ofstream &);
void cargarPacientes(const char *, void *&);
char *leerCadenaCaracteres(ifstream &, char );
void incrementarCapacidad(void ***&, int , int &);
void cargarDatosPacientes(void **&, long long , char *, int , char );
void cargarVisitas(const char *, void *&);
int encontrarPosicion(void ***, long long );
void cargarDatosCita(void **&, int , int , int , int , int , double , double &, int &, int &);
int generarFecha(int , int , int );
int generarHora(int , int );
void generarReportes(const char *, void *);
void imprimirPacientes(ofstream &, void **);

#endif //CODIGO_FUNCIONES_H
