#ifndef DISPLAY_RGB_H
#define DISPLAY_RGB_H

// Tipos estándar como uint8_t
#include <stdint.h> 

// Código de error general
#define ERROR -1

// Inicializa el display con el ancho y alto dados
int dispInit(uint16_t width, uint16_t height);

// Borra todo el contenido del buffer del display
void dispClear(void);

// Configura un píxel en las coordenadas dadas con un color RGB
int dispWrite(uint16_t x, uint16_t y, uint32_t color);

// Envía el buffer al display
void dispFlip(void);

#endif // DISPLAY_RGB_H