#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "port_read.h"

//funcion para leer los puertos
void port_read (void) 
{
	FILE * handle;
	switch(portA.b0)
	{
		case 1:
			if((handle = fopen("/sys/class/gpio/gpio17/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('1',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		case 0:
			if((handle = fopen("/sys/class/gpio/gpio17/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('0',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		default: break;
	}
	switch(portA.b1)
	{
		case 1:
			if((handle = fopen("/sys/class/gpio/gpio4/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('1',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		case 0:
			if((handle = fopen("/sys/class/gpio/gpio4/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('0',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		default: break;
	}
	switch(portA.b2)
	{
		case 1:
			if((handle = fopen("/sys/class/gpio/gpio18/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('1',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		case 0:
			if((handle = fopen("/sys/class/gpio/gpio18/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('0',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		default: break;
	}
	switch(portA.b3)
	{
		case 1:
			if((handle = fopen("/sys/class/gpio/gpio23/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('1',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		case 0:
			if((handle = fopen("/sys/class/gpio/gpio23/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('0',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		default: break;
	}
	switch(portA.b4)
	{
		case 1:
			if((handle = fopen("/sys/class/gpio/gpio24/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('1',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		case 0:
			if((handle = fopen("/sys/class/gpio/gpio24/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('0',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		default: break;
	}
	switch(portA.b5)
	{
		case 1:
			if((handle = fopen("/sys/class/gpio/gpio25/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('1',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		case 0:
			if((handle = fopen("/sys/class/gpio/gpio25/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('0',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		default: break;
	}
	switch(portA.b6)
	{
		case 1:
			if((handle = fopen("/sys/class/gpio/gpio22/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('1',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		case 0:
			if((handle = fopen("/sys/class/gpio/gpio22/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('0',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		default: break;
	}
	switch(portA.b7)
	{
		case 1:
			if((handle = fopen("/sys/class/gpio/gpio27/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('1',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		case 0:
			if((handle = fopen("/sys/class/gpio/gpio27/value","w")) == NULL)
			{
				printf("Error al abrir archivo\n");
				exit(1);
			}
			else
			{
				printf("Archivo abierto con exito\n");
			}
			if(fputc('0',handle)== -1)
			{
				printf("Error al prender/apagar pin\n");
				exit(1);
			}
			else
			{
				printf("Pin prendido/apagado\n");
			}
			fclose(handle);
		break;
		default: break;
	}
}

