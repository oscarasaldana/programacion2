
#ifndef CREARBIBLIOTECA_PARTE1_OPERADORESSOBRECARGADOS_H
#define CREARBIBLIOTECA_PARTE1_OPERADORESSOBRECARGADOS_H

using namespace std;

void cargarArchivo(const char *, ifstream &);
void crearArchivo(const char *, ofstream &);
void operator >> (ifstream &, struct Cursos &);
void operator >> (ifstream &, struct Alumnos &);
char *leerCadenaCaracteres(ifstream &, char );
bool operator > (struct Alumnos &, int );
bool operator > (struct Cursos &, char *);
void operator += (struct Cursos &, struct Alumnos &);
int operator <= (struct Alumnos *, struct Alumnos &);
int operator <= (struct Cursos *, struct Cursos &);
void operator ++ (struct Cursos &, int);
void operator << (ofstream &, struct Cursos &);

#endif //CREARBIBLIOTECA_PARTE1_OPERADORESSOBRECARGADOS_H
