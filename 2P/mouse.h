#ifndef MOUSE_H
#define MOUSE_H

// Macros para identificar los botones del mouse
#define BUTTON_LEFT 1
#define BUTTON_RIGHT 2

// Alias para el tipo de la función callback
typedef void (*MouseCallback)(int x, int y, int button);

// Inicializa el driver del mouse, devuelve 0 si tuvo éxito y -1 si falló
int mouse_init(void);

/* Lee el estado actual del mouse, almacena las coordenadas en 'x' y 'y', y el estado del botón en 'button'
y devuelve 0 si tuvo éxito, -1 si falló */
int mouse_readStatus(int *x, int *y, int *button);

/* Registra una función callback que se ejecutará en cada clic del mouse, la función callback recibe las 
coordenadas y el botón del clic */
void mouse_registerCallback(MouseCallback callback);

#endif // MOUSE_H
