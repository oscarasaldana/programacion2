
#ifndef CODIGO_FUNCIONES_H
#define CODIGO_FUNCIONES_H

void cargarArchivo(const char *, ifstream &);
void crearArchivo(const char *, ofstream &);
void cargarCategorias(const char *, char ***&);
char *leerCadenaCaracteres(ifstream &, char );
void aumentarCapacidadCategorias(char ***&, int , int &);
void cargarStreamers(const char *, char ***&, int **&, long long **&);
int construirFecha(int , int , int );
void aumentarCapacidadStreamers(char ***&, int **&, long long **&, int , int &);
void cargarEtiquetasComentarios(const char *, char ***&, char ***&);
void concatenarComentarios(char *&, char *);
void aumentarCapacidad(char ***&, int , int &);
void imprimirReportes(const char *, char ***, char ***, int **, long long **, char ***, char ***);

#endif //CODIGO_FUNCIONES_H
