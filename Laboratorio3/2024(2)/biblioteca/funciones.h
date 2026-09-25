
#ifndef CODIGO_FUNCIONES_H
#define CODIGO_FUNCIONES_H

void cargarArchivo(const char *, ifstream &);
void crearArchivo(const char *, ofstream &);
void cargarInventario(const char *, void *&);
char *leerCadenaCaracteres(ifstream &, char );
void cargarDatosInventario(void **&, char *, char *, double , double , char *);
void probarCargaInventario(const char *, void *&);
void mostrarInventario(ofstream &, void **&);
void incrementarCapacidadInventario(void ***&, int , int &);
void cargarMenu(const char *, void *&);
void incrementarCapacidadMenu(void ***&, int , int &);
void cargarDatosMenu(void **&, char *, char *, char *, char , bool , double , int );
void probarCargaMenu(const char *, void *&);
void mostrarMenu(ofstream &, void **&);
void actualizarMenu(const char *, void *&, void *&);
int encontrarPosicionBebida(void ***, char *);
void cargarDatosInsumosBebida(void **&, int &, int &, void *&, void *&,char *, int , char , int );
void **informacionInsumo(void ***, char *, int &);
void actualizarDatosInsumosYBebidas(void *&, void *&, int , int , int );
void reporteMenu(const char *, void *&);
void mostrarBebidas(ofstream &, void **&);
void mostrarTipoBebida(ofstream &, char *);

#endif //CODIGO_FUNCIONES_H
