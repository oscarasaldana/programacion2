
#ifndef CODIGO_VACUNA_H
#define CODIGO_VACUNA_H

class Vacuna {

private:
    char *nombre;
    int fecha;
    double dosis;
    char *colegiatura;

public:
    Vacuna();
    ~Vacuna();

    void cargarNombre(char *);
    void obtenerNombre(char *) const;
    void cargarFecha(int );
    void obtenerFecha(int &) const;
    void cargarDosis(double );
    void obtenerDosis(double &) const;
    void cargarColegiatura(char *);
    void obtenerColegiatura(char *) const;

};

void operator >> (ifstream &, class Vacuna &);
void operator << (ofstream &, const class Vacuna &);

#endif //CODIGO_VACUNA_H
