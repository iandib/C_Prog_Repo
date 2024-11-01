/***************************************************************************//**
  @file     +hardware.c+
  @brief    +Modulo hardware+
  @author   +Grupo 4+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "hardware.h"
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define GPIO  "/sys/class/gpio/"
#define MAXLEN 35

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void expPin(int pin);				//Exporta el pin indicado
static void expAll();						//Exporta todos los pines
static void dirPin(int pin, char * dir);	//Configura la direccion del pin indicado
static void dirOutAll();					//Configura la direccion de todos los pin es como salida
static void actPin(int pin, char * act);	//Configura el active_low del pin indicado
static void actHighAll();					//Configura todos los pines como activo alto
static void uexpPin(int pin);				//Unexporta el pin indicado

static void printError(char * err, int pin);//Imprime un mensaje de error

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void initPins()	//Inicializa todos los pines
{
	expAll();	//Exporto todos los pines
	dirOutAll();	//Configura la direccion de todos los pines como salida
	actHighAll();	//Configura todos los pines como activo alto
}

void endPins()	//Unexporta todos los pines
{
	uexpPin(17);
	uexpPin(4);
	uexpPin(18);
	uexpPin(23);
	uexpPin(24);
	uexpPin(25);
	uexpPin(22);
	uexpPin(27);
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void printError(char * err, int pin)	//Imprime mensaje de error
{
	printf("Error al %s el pin %d\n", err, pin);	//Imprimo el error
}

static void expPin(int pin)	//Exporta pines
{
	char str[MAXLEN] = {0};
	strcat(str, GPIO);
	FILE * fp;
	strcat(str,"export");	//Creo el string completo del archivo donde voy a escribir
	if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
	{
		printError("al exportar", pin);	//Indico el error
	}
	else	//Si puedo abrir el archivo
	{
		switch (pin)	//Exporto el pin indicado
		{
			case 17:
				fputs("17", fp);
				break;
			case 4:
				fputs("4", fp);
				break;
			case 18:
				fputs("18", fp);
				break;
			case 23:
				fputs("23", fp);
				break;
			case 24:
				fputs("24", fp);
				break;
			case 25:
				fputs("25", fp);
				break;
			case 22:
				fputs("22", fp);
				break;
			case 27:
				fputs("27", fp);
				break;
			default:
				break;			
		}
		fclose(fp);
	}
}

static void expAll()	//Exporta todos los pines
{
	expPin(17);
	expPin(4);
	expPin(18);
	expPin(23);
	expPin(24);
	expPin(25);
	expPin(22);
	expPin(27);
}

static void dirPin(int pin, char * dir)	//Configura la direccion del pin indicado
{
	char str[MAXLEN] = {0};
	strcat(str, GPIO);
	FILE * fp;
	
	switch (pin)
	{
		case 17:		
			strcat(str,"gpio17/direction");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar la direccion de", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(dir, fp);	//Lo configuro como salida
			}
			break;
		case 4:		
			strcat(str,"gpio4/direction");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar la direccion de", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(dir, fp);	//Lo configuro como salida
			}
			break;
		case 18:		
			strcat(str,"gpio18/direction");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar la direccion de", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(dir, fp);	//Lo configuro como salida
			}
			break;
		case 23:		
			strcat(str,"gpio23/direction");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar la direccion de", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(dir, fp);	//Lo configuro como salida
			}
			break;
		case 24:		
			strcat(str,"gpio24/direction");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar la direccion de", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(dir, fp);	//Lo configuro como salida
			}
			break;
		case 25:		
			strcat(str,"gpio25/direction");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar la direccion de", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(dir, fp);	//Lo configuro como salida
			}
			break;
		case 22:		
			strcat(str,"gpio22/direction");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar la direccion de", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(dir, fp);	//Lo configuro como salida
			}
			break;
		case 27:		
			strcat(str,"gpio27/direction");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar la direccion de", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(dir, fp);	//Lo configuro como salida
			}
			break;
		default:
			break;
	}
	fclose(fp);	//Cierro el archivo
}

static void dirOutAll()	//Configura todos los pines como salida
{
	dirPin(17, "out");
	dirPin(4, "out");
	dirPin(18, "out");
	dirPin(23, "out");
	dirPin(24, "out");
	dirPin(25, "out");
	dirPin(22, "out");
	dirPin(27, "out");
}

static void actPin(int pin, char * act)	//Configura el pin indicado como activo alto o bajo
{
	char str[MAXLEN] = {0};
	strcat(str, GPIO);
	FILE * fp;
	
	switch (pin)
	{
		case 17:		
			strcat(str,"gpio17/active_low");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar el active low en", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(act, fp);	//Lo configuro como activo alto
			}
			break;
		case 4:		
			strcat(str,"gpio4/active_low");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar el active low en", pin);	//Indico el error
			}
			else
			{
				fputs(act, fp);
			}
			break;
		case 18:		
			strcat(str,"gpio18/active_low");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar el active low en", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(act, fp);	//Lo configuro como activo alto
			}
			break;
		case 23:		
			strcat(str,"gpio23/active_low");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar el active low en", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(act, fp);	//Lo configuro como activo alto
			}
			break;
		case 24:		
			strcat(str,"gpio24/active_low");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar el active low en", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(act, fp);	//Lo configuro como activo alto
			}
			break;
		case 25:		
			strcat(str,"gpio25/active_low");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar el active low en", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(act, fp);	//Lo configuro como activo alto
			}
			break;
		case 22:		
			strcat(str,"gpio22/active_low");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar el active low en", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(act, fp);	//Lo configuro como activo alto
			}
			break;
		case 27:		
			strcat(str,"gpio27/active_low");	//Creo el string completo del archivo donde voy a escribir
			if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
			{
				printError("al modificar el active low en", pin);	//Indico el error
			}
			else	//Si puedo
			{
				fputs(act, fp);	//Lo configuro como activo alto
			}
			break;
		default:
			break;
	}
	fclose(fp);	//Cierro el archivo
}

static void actHighAll()	//Configura todos los pines como activo alto
{
	actPin(17, "0");
	actPin(4, "0");
	actPin(18, "0");
	actPin(23, "0");
	actPin(24, "0");
	actPin(25, "0");
	actPin(22, "0");
	actPin(27, "0");
}

static void uexpPin(int pin)	//Unexporta el pin indicado
{
	char str[MAXLEN] = {0};
	strcat(str, GPIO);
	FILE * fp;
	strcat(str,"unexport");	//Creo el string completo del archivo donde voy a escribir
	if((fp = fopen(str,"w")) == NULL)	//Si no puedo abrir el archivo
	{
		printError("al unexportar", pin);	//Indico el error
	}
	else	//Si puedo abrir el archivo
	{
		switch (pin)	//Unexporto el pin indicado
		{
			case 17:
				fputs("17", fp);
				break;
			case 4:
				fputs("4", fp);
				break;
			case 18:
				fputs("18", fp);
				break;
			case 23:
				fputs("23", fp);
				break;
			case 24:
				fputs("24", fp);
				break;
			case 25:
				fputs("25", fp);
				break;
			case 22:
				fputs("22", fp);
				break;
			case 27:
				fputs("27", fp);
				break;
			default:
				break;			
		}
		fclose(fp);	//Cierro el archivo
	}
}



