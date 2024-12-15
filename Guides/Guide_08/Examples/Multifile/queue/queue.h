/***************************************************************************//**
  @file     queue.h
  @brief    Modulo para manejo de filas, implementado con buffer circular
  @author   Nicolas Magliola
 ******************************************************************************/

#ifndef _QUEUE_H_
#define _QUEUE_H_

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define QUEUE_LENGTH	256

#define QUEUE_T			int

#define QUEUE_ISEMPTY()	(0 == queueCant())	
#define QUEUE_ISFULL()	(QUEUE_LENGTH == queueCant())


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Agrega un elemento al final de la fila
 * @param data elemento a agregar
*/
void queuePut (QUEUE_T data);


/**
 * @brief Toma el primer elemento de la fila
 * @return El primer elemento
*/
QUEUE_T queueGet (void);


/**
 * @brief Indica cuantos elementos hay presentes en la fila
 * @return Canntidad de elementos presentes
*/
int queueCant (void);


/*******************************************************************************
 ******************************************************************************/

#endif // _QUEUE_H_
