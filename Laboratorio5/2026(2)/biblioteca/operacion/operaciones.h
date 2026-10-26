
#ifndef CODIGO_OPERACIONES_H
#define CODIGO_OPERACIONES_H

class Operaciones {

private:
    int codigo;
    int cliente;
    int fecha;
    char *canal;
    char *tipo;

public:
    Operaciones();
    ~Operaciones();

    void liberarEspacio();
    void cargarCodigo(int );
    int obtenerCodigo();
    void cargarCliente(int );
    int obtenerCliente();
    void cargarFecha(int );
    int obtenerFecha();
    void cargarCanal(char *);
    void obtenerCanal(char *);
    void cargarTipo(char *);
    void obtenerTipo(char *);

};

#endif //CODIGO_OPERACIONES_H
