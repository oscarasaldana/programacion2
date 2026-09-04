
#ifndef USARBIBLIOTECA_PARTE2_FUNCIONES_H
#define USARBIBLIOTECA_PARTE2_FUNCIONES_H

void cargarArchivo(const char *, ifstream &);
void crearArchivo(const char *, ofstream &);
void cargarInfracciones(ifstream &, int *, struct CadenaCaracteres *, struct CadenaCaracteres *, int &);
char *leerCadenaExacta(ifstream &, char );
char *leerCadenaCaracter(ifstream &, char );
void qsort(int *, struct CadenaCaracteres *, struct CadenaCaracteres *, int , int );
void cambiar(int *, struct CadenaCaracteres *, struct CadenaCaracteres *, int , int );
void reporte(ofstream &, int *, struct CadenaCaracteres *,struct CadenaCaracteres *, int );
int contarCaracteres(char *);

#endif //USARBIBLIOTECA_PARTE2_FUNCIONES_H
