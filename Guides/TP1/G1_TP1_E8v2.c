#include <stdio.h>

// Versión alternativa con la librería math.h para usar las funciones nativas
#include <math.h>

int main (void){

	// Inicializamos la variable con el número al que aplicaremos las funciones
	double x = -143.5;

	// La función techo devuelve el mínimo número entero no inferior (mayor o igual) a x
	double ceiling = ceil(x); 
	printf("Techo de x: %f \n", ceiling);

	// La función piso devuelve el máximo número entero no superior (menor o igual) a x
	double floor_f = floor(x); 
	printf("Piso de x: %f \n", floor_f);

	// La función redondeo asigna a x el número entero más próximo, redondeando sus decimales
	double rounding = round(x); 
	printf("Redondeo de x: %f \n", rounding);

	// La función truncamiento devuelve la parte entera de x, truncando sus decimales
	double truncation = trunc(x); 
	printf("Truncamiento de x: %f \n", truncation);

	// La función módulo devuelve el valor absoluto de x 
	double module = fabs(x); 
	printf("Modulo de x: %f \n", module);

	return 0;
}

// Bibliografía: https://es.wikipedia.org/wiki/Funciones_de_parte_entera
