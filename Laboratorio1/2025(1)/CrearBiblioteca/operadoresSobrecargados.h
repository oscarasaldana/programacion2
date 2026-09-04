
#ifndef CREARBIBLIOTECA_PARTE1_OPERADORESSOBRECARGADOS_H
#define CREARBIBLIOTECA_PARTE1_OPERADORESSOBRECARGADOS_H

void operator ! (struct CadenaCaracteres &);
void operator <= (struct CadenaCaracteres &, const char *);
void operator <= (struct CadenaCaracteres &, int );
void operator <= (struct CadenaCaracteres &, struct CadenaCaracteres &);
void operator += (struct CadenaCaracteres &, const char *);
bool operator += (struct CadenaCaracteres &, struct CadenaCaracteres &);
int compare(struct CadenaCaracteres &, const char *);
bool operator == (struct CadenaCaracteres &, const char *);
bool operator < (struct CadenaCaracteres &, const char *);
bool operator > (struct CadenaCaracteres &, const char *);
int compare(struct CadenaCaracteres &, struct CadenaCaracteres &);
bool operator == (struct CadenaCaracteres &, struct CadenaCaracteres &);
bool operator < (struct CadenaCaracteres &, struct CadenaCaracteres &);
bool operator > (struct CadenaCaracteres &, struct CadenaCaracteres &);
int operator >> (ifstream &, struct CadenaCaracteres &);
char *leerCadenaCaracteres(ifstream &, char );
void operator && (struct CadenaCaracteres &, struct CadenaCaracteres &);
void operator << (ofstream &, struct CadenaCaracteres &);

#endif //CREARBIBLIOTECA_PARTE1_OPERADORESSOBRECARGADOS_H
