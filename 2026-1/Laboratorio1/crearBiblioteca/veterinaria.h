
#ifndef CREARBIBLIOTECA_PARTE1_VETERINARIA_H
#define CREARBIBLIOTECA_PARTE1_VETERINARIA_H

struct Mascota {
    int idMascota;
    char *nombre;
    char *raza;
    char *color;
    char *tipo;
    int fechaNacimiento;
};

struct Veterinario {
    int idVeterinario;
    char *nombre;
    char *especialidad;
};

struct Atencion {
    int idAtencion;
    int idMascota;
    int idVeterinario;
    int fecha;
    char *tipoAtencion;
    int hora;
    int minutos;
    char *estado;
};

struct Sistema {
    struct Mascota arrMascotas[50];
    struct Veterinario arrVeterinarios[50];
    struct Atencion arrAtenciones[50];
    int numMascotas;
    int numVeterinarios;
    int numAtenciones;
};

#endif //CREARBIBLIOTECA_PARTE1_VETERINARIA_H
