#include <stdio.h>

typedef struct {
    unsigned int legajo;
    char nombre[20];
    char apellido[20];
    float promedioAcademico;
} alumno_t;


void strcopy(char* s1, const char* s2);
void printalum(const alumno_t*);


int main (void) {
    alumno_t alumnos[10];
    alumno_t *pAlumno;
    pAlumno = alumnos;

    (*(pAlumno+3)).legajo = 60224;
    (*(pAlumno+3)).promedioAcademico = 6.5;

    pAlumno += 3;
    
    strcopy(pAlumno->nombre, "Daniel");
    strcopy(pAlumno->apellido, "Fernandez");

    printalum(pAlumno);

    return 0;
}


void strcopy(char* s1, const char* s2)
{
	do {
		*s1++ = *s2;
	} while (*s2++);
}


void printalum(const alumno_t* alu)
{
    printf("El legajo de %s %s es %d\n", alu->nombre, alu->apellido, alu->legajo);
}

