
#ifndef CREARBIBLIOTECA_PARTE1_OPERADORESSOBRECARGADOS_H
#define CREARBIBLIOTECA_PARTE1_OPERADORESSOBRECARGADOS_H

using namespace std;

void cargarArchivos(ifstream &, ifstream &, ifstream &);
void crearArchivos(ofstream &, ofstream &);
istream & operator >> (ifstream &, struct Mascota &);
istream & operator >> (ifstream &, struct Veterinario &);
istream & operator >> (ifstream &, struct Atencion &);
char *leerCadenaCaracteres(ifstream &, char );
bool operator == (struct Atencion &, struct Atencion &);
bool operator <= (struct Mascota &, int );
double descomponerFecha(int , int , int , int);
ostream & operator << (ofstream &, struct Mascota &);
ofstream & operator << (ofstream &, struct Atencion &);

#endif //CREARBIBLIOTECA_PARTE1_OPERADORESSOBRECARGADOS_H
