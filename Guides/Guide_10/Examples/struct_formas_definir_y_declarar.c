/** Formas de definir y declarar estructuras **/
/* https://www.embedded.com/electronics-blogs/programming-pointers/4024450/Tag-vs-Type-Names */

struct {             // Si NO uso el TAG debo definir la/las variables
    int x;           // junto con la declaracion
    int y;           // Es decir que esto DECLARA y DEFINE
} point1;            // Definición de estructura ANONIMA


struct PUNTO {       // Como la estructura tiene un TAG
    int x;           // la definición de las variables es
    int y;           // opcional (no como en el caso previo
};                   // que es obligatorio pues no tiene nombre
                     // Independiente de que defina o no las variables
                     // puedo usar el TAG para definir (crear) variables
                     // en cualquier otro lado de mi fuente.

struct PUNTO punto2; // Definición con TAG

typedef struct {     // Con typedef la lectura de las definiciones es mas clara
    int x;
    int y;
} DOT;

DOT punto3;         // Definición con TYPEDEF 


int main(void)
{
    point1.x=1;
    point1.y=2;

    punto2.x=3;
    punto2.y=4;

    punto3.x=5;
    punto3.y=6;

    punto3.x=7;
    punto3.y=8;

    return 0;
}


/********************************* Resumiendo *********************************

 Tenemos Basicamente tres formas:

 1 - sin TAG => Debemos efinir las variables en el mismo
     lugar de la definicion. Sin poder usar esta declaracion
     mas adelante

 2 - Con TAG => Nos permite elegir donde definir las variables

 3 - Usando typedef => Nos ayuda muchisimo a la documentacion del programa
 
 ********************************* Resumiendo *********************************/

