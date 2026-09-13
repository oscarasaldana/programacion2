
#ifndef CODIGO_FUNCIONES_H
#define CODIGO_FUNCIONES_H

void cargarArchivo(const char *, ifstream &);
void crearArchivo(const char *, ofstream &);
void lecturaDeLibros(const char *, char ***&, int **&);
char **leerDatosLibros(ifstream &);
char *leerCadenaCaracteres(ifstream &, char );
int *leerDatosInventario(ifstream &);
void pruebaDeLecturaDeLibros(const char *, char ***, int **);
void atencionDePedidos(const char *, char ***&, int **&, int **&, char ***&, bool **&);
int encontrarPosicion(int **, int );
void cargarPedidosClientes(int *&, int dni, int );
void ingresarNuevoPedido(int *&, int );
void cargarPedidosLibros(char **&, char *);

void cargarPedidosAtenciones(bool **&, int , char ***&, int **&, char ***&);
int encontrarPosicion(char ***, char *);
void verificarPedido(bool *&, int **&, int , int );
void reporteDeEntregaDePedidos(const char *, int **, char ***, bool **);

#endif //CODIGO_FUNCIONES_H
