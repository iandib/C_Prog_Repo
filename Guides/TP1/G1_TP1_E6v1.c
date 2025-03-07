#include <stdio.h>

/* 
Definimos las siguientes máscaras con el objetivo de analizar el estado de los bits indicados en el enunciado:
- MASK1 para verificar que los bits 1 y 5 estén encendidos (0x22 corresponde a 0010 0010b).
- MASK2 para verificar que los bits 2 y 6 estén apagados (0x44 corresponde a 0100 0100b).
*/

#define MASK1 0x22
#define MASK2 0x44

int main (void){
	
	// Inicializamos la variable que representa el puerto A del 68HC11
	int porta = 56;

   	/* 
	El programa sigue esta lógica:
	- Primero, verifica si los bits 1 y 5 están encendidos utilizando MASK1. Si esto es verdadero, se imprime 1.
	- Si los bits 1 y 5 no están encendidos, el programa verifica si los bits 2 y 6 están apagados utilizando MASK2.
	- Si los bits 2 y 6 están apagados, se imprime 1; si no, se imprime 0.

	Utilizamos el operador relacional `==` para verificar si los bits están encendidos (comparación directa con MASK1),
	y `!=` para verificar si los bits están apagados (comparación con MASK2).
	*/

	printf("%d\n",(((porta & MASK1) == MASK1) || (((porta & MASK2) != MASK2)))? 1 : 0);

	return 0;
}
