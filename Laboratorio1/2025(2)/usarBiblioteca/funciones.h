
#ifndef USARBIBLIOTECA_PARTE2_FUNCIONES_H
#define USARBIBLIOTECA_PARTE2_FUNCIONES_H

using namespace std;

void cargarAlumnos(const char *, struct Alumnos *);
void cargarCursos(const char *, struct Cursos *);
void cargarMatriculas(const char *, struct Cursos *, struct Alumnos *);
char *leerCadena(ifstream &, char );
bool encontrarCurso(struct Cursos *, char *);
void generarReporte(const char *, struct Cursos *);

#endif //USARBIBLIOTECA_PARTE2_FUNCIONES_H
