
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
    int obtenerCodigo() const;
    void cargarCliente(int );
    int obtenerCliente() const;
    void cargarFecha(int );
    int obtenerFecha() const;
    void cargarCanal(char *);
    void obtenerCanal(char *) const;
    void cargarTipo(char *);
    void obtenerTipo(char *) const;

};

#endif //CODIGO_OPERACIONES_H
