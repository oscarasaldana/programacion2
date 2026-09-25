#ifndef CODIGO_FUNCIONES_H
#define CODIGO_FUNCIONES_H

void cargarArchivo(const char *, ifstream &);
void crearArchivo(const char *, ofstream &);
void cargarStreamers(void *&);
char *leerCadenaCaracteres(ifstream &, char );
void incrementarCapacidadStreamers(void ***&, int , int &);
void cargarDatosStreamer(void **&, char *, long long , char *);
void cargarComentarios(void *&);
void incrementarCapacidadComentarios(void ***&, int , int &);
void cargarDatosComentarios(void **&, char *, char *, char *, char *);
void actualizarComentarios(void *&, void *);
void cargarComentarioStreamer(char ***&, char *, char *, int &, int &);
void imprimirStreamers(void *);
void imprimirDatosStreamers(ofstream &, void **);

#endif //CODIGO_FUNCIONES_H
